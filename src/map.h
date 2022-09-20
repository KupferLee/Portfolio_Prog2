#ifndef RAYLIBSTARTER_MAP_H
#define RAYLIBSTARTER_MAP_H

#include "raylib.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include "raymath.h"


class map {
public:
    map();
    void Parse();
    void Parse_Items();
    void Draw();
    void Randomize();
    void Random_Start_Fin();
    void Random_Items();

    int Get_Tile(int i);
    int Get_Item(int i);
    void Set_Item_Zero(int i);

    // get tile positions in x/y in tiles
    Vector2 Get_Start_Pos();
    Vector2 Get_Fin_Pos();

    void Draw_Path();

    void Draw_Collision();
    Rectangle Get_Rectangle(int i);
    int Get_Size_Collsion();

protected:
    nlohmann::json Level_Map;
    Texture2D Tileatlas_Texture;
    nlohmann::json Tileset_Description;

    // ticks for checking which position inside of methods
    int draw_tick = 0;
    int checkpoint_tick = 0;
    int item_tick = 0;
    int items_max = 10; // how many items there can be spawned at one map
    int item_current = 0; // how many items are currently spawned on the map

    bool is_dagger = false;
    bool is_ring = false;
    bool is_chestplate = false;

    bool is_start_drawn = false;
    bool is_fin_drawn = false;

    // tiles as numbers
    const int tile_empty = -1;
    const int tile_grass = 0;
    const int tile_finish = 2;
    const int tile_start = 3;
    const int tile_dagger = 4;
    const int tile_chest = 5;
    const int tile_potion = 6;
    const int tile_apple = 7;
    const int tile_crystal = 8;
    const int tile_ring = 9;
    const int tile_armor = 10;

    Vector2 start_position = {0, 0};
    Vector2 finish_position = {0, 0};


public:
    //structs for tilemaps
    struct {
        Texture2D tilemap;
        int tile_widht;
        int tile_map_width;
        int row_length;
    } tilemap_data;

    struct {
        std::vector<int> layer_ground;
        std::vector<int> layer_path;
        std::vector<int> layer_items;
        std::vector<int> layer_checkpoints;
        std::vector<bool> layer_collision;
        int map_width;
        int map_height;
    } map_data{};

    std::vector<Rectangle> hitboxes;


};


#endif //RAYLIBSTARTER_MAP_H
