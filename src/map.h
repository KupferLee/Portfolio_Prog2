//
// Created by Lee on 01.08.2022.
//

#ifndef RAYLIBSTARTER_MAP_H
#define RAYLIBSTARTER_MAP_H

#include <nlohmann/json.hpp>
#include <fstream>
#include "raylib.h"

class map {
public:
    map();
    ~map();
    void parse();
    void draw();
    void random();
    void randomStartFin();
    void randomItems();

protected:
    nlohmann::json levelMap;
    Texture2D tileAtlasTexture;
    nlohmann::json tilesetDescription;

    // ticks for checking which position inside of methods
    int drawTick = 0;
    int checkpointTick = 0;
    int itemTick = 0;
    int itemsMax = 7; // how many items there can be spawned at one map
    int itemCurrent = 0; // how many items are currently spawned on the map

    bool isStartDrawn = false;
    bool isFinDrawn = false;

    // tiles as numbers
    const int tile_empty = -1;
    const int tile_grass = 0;
    const int tile_water = 1;
    const int tile_finish = 2;
    const int tile_start = 3;
    const int tile_dagger = 4;
    const int tile_chest = 5;
    const int tile_potion = 6;
    const int tile_apple = 7;
    const int tile_crystal = 8;



    //structs for tilemaps
    struct {
        Texture2D tilemap;
        int tileWidht;
        int tileMapWidth;
        int rowLength;
    } tilemapData;

    struct {
        std::vector<int> layerGround;
        std::vector<int> layerPath;
        std::vector<int> layerItems;
        std::vector<int> layerCheckpoints;
        int mapWidth;
        int mapHeight;
    } mapData;
};


#endif //RAYLIBSTARTER_MAP_H
