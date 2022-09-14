#include <cstdlib>
#include <iostream>

#include "raylib.h"

#include "config.h"

#include "map.h"
#include "inventory_ui.h"
#include "character_player.h"
#include <iostream>

int main() {
    // Raylib initialization
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
    // ScreenWidth = 30 * 16 * 2 = 960;
    // ScreenHeight = 20 * 16 * 2 = 640;
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetTargetFPS(60);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    // Your own initialization code here
    Texture2D infoTexture = LoadTexture("assets/graphics/infografik.png");
    map* Map = new map;
    inventory_ui* Inventory = new inventory_ui();
    character_player* Player = new character_player;
    Player->Map = Map;
    Inventory->Player = Player;

    // loading the current json data into vectors so they only need to be parsed once
    Map->Randomize();
    Map->Random_Start_Fin();
    Map->Random_Items();


    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Updates that are made by frame are coded here

        Inventory->Update();



        Player->Update();



        switch (Inventory->is_backpack_open())
        {
            case true:
            {
                Player->Set_Can_Move(false);
                break;
            }

            case false:
            {
                /*
                for (int i = 0; i < Map->Get_Size_Collsion(); i ++)
                {
                    // Fehler ist da wo ich nach Hitboxen frage
                    if (Player->Check_Collision(Map->Get_Rectangle(i)))
                    {
                        Player->Set_Can_Move(false);
                        std::cout << "DEBUG: Hitbox found." << std::endl;
                    }
                    else
                    {
                        Player->Set_Can_Move(true);
                    }
                }
                 */

                break;
            }
        }



        BeginDrawing();
            // You can draw on the screen between BeginDrawing() and EndDrawing()
            // ...
            // ...
            ClearBackground(BLUE);
            DrawText("If you see this, this is not working!", 10, 10, 30, DARKBLUE);

            // draw what is currently loaded within the map vectors
        Map->Draw();

            // draw Player
        Player->Draw();


            if (IsKeyDown(KEY_Q))
            {
                DrawTexture(infoTexture, 0, 0, WHITE);
            }
            else if (!IsKeyDown(KEY_E))
            {
                // little backpack shall be only drawn when there is no other info screen currently open
                DrawText("Press Q for more information.", Game::ScreenWidth - 750, Game::ScreenHeight - 100, 30, BLACK);
                DrawText("Press E to erase GUI.", Game::ScreenWidth - 750, Game::ScreenHeight - 50, 30, BLACK);
                Inventory->Draw();
            }

            // Draw Collision
            if ( IsKeyDown(KEY_H))
            {
                Map->Draw_Collision();
            }


        EndDrawing();
    } // Main game loop end

    // De-initialization here
    // ...
    // ...

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
