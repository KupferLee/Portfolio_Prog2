#include <cstdlib>
#include <iostream>

#include "raylib.h"

#include "config.h"

#include "map.h"
#include "item_chest.h"
#include "item_dagger.h"
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
    map* current_map = new map;
    item_chest* treasure_chest = new item_chest;
    item_dagger* weapon_dagger = new item_dagger;


    // loading the current json data into vectors so they only need to be parsed once
    current_map->random();
    current_map->randomStartFin();
    current_map->randomItems();

    // to check if assigning the treasure chest worked
    std::cout << "DEBUG: OUTPUT TREASURE CHEST" << std::endl;
    std::cout << treasure_chest->getName() << " | " << "Value: " << treasure_chest->getValue() << " | " << treasure_chest->getDescription() << " | " << "Weight: " << treasure_chest->getWeight() << std::endl;
    std::cout << "DEBUG: OUTPUT END TREASURE CHEST" << std::endl;

    // to check if assigning the dagger worked
    std::cout << "DEBUG: OUTPUT DAGGER" << std::endl;
    std::cout << weapon_dagger->getName() << " | " << "Value: " << weapon_dagger->getValue() << " | " << weapon_dagger->getDescription() << " | " << "Weight: " << weapon_dagger->getWeight() << std::endl;
    std::cout << "DEBUG: OUTPUT END DAGGER" << std::endl;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Updates that are made by frame are coded here


        BeginDrawing();
            // You can draw on the screen between BeginDrawing() and EndDrawing()
            // ...
            // ...
            ClearBackground(BLUE);
            DrawText("If you see this, this is not working!", 10, 10, 30, DARKBLUE);

            // draw what is currently loaded within the map vectors
            current_map->draw();

            if (IsKeyDown(KEY_ENTER))
            {
                DrawTexture(infoTexture, 0, 0, WHITE);
            }
            else
            {
                DrawText("Press Enter for more information.", Game::ScreenWidth - 550, Game::ScreenHeight - 50, 30, BLACK);
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
