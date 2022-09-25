#include <cstdlib>
#include <iostream>

#include "raylib.h"

#include "config.h"

#include "map.h"
#include "inventory_ui.h"
#include "character_player.h"
#include "character_robot.h"

int main() {
    // Raylib initialization
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetTargetFPS(60);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    // initialization
    map* Map = new map;
    inventory_ui* Inventory = new inventory_ui();
    character_player* Player = new character_player;
    character_robot* Robot = new character_robot;

    Inventory->Player = Player;

    // loading the current json data into vectors, so they only need to be parsed once
    Map->Parse();
    Map->Random_Start_Fin();
    Map->Parse_Items();

    Player->Map = Map;
    Robot->Map = Map;

    Player->Set_Starting_Pos();
    Robot->Set_Starting_Pos();


    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // update GUI
        Inventory->Update();

        // Update Actors
        Player->Update(Inventory->Is_Backpack_Open(), Robot->Is_Message_Open());
        Robot->Update(Inventory->Is_Backpack_Open());

        // check if robot found any items
        // TODO: only add if total weight + item weight < strength
        if (Robot->Item_Found() != -1) // && Player->Get_Total_Weight() < Player->Get_Total_Strength()
        {
            Player->Robot_Item(Robot->Item_Found());
            Robot->Item_Pick_Up();
        }


        // Render
        BeginDrawing();
            // If map doesnt get draw this is an error message on the screen
            ClearBackground(BLUE);
            DrawText("If you see this, this is not working!", 10, 10, 30, DARKBLUE);

            // draw what is currently loaded within the map vectors
            Map->Draw();
            Robot->Draw_Path();

            // draw characters
            Robot->Draw();
            Player->Draw();

            // Draw GUI
            Inventory->Draw();
            Robot->Draw_GUI();

        EndDrawing();
    }

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
