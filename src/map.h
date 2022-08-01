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
    void drawMap();

protected:
    nlohmann::json levelMap;
    Texture2D tileAtlasTexture;
    nlohmann::json tilesetDescription;

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
        int mapWidth;
        int mapHeight;
    } mapData;
};


#endif //RAYLIBSTARTER_MAP_H
