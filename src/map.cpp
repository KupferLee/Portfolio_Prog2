//
// Created by Lee on 01.08.2022.
//

#include "map.h"

map::map()
{
    //tileset Description File
    std::ifstream tilesetDescriptionFile("assets/map/tileset.json");

    //begin of parsing
    //level map file
    std::ifstream levelMapFile("assets/map/testmap.json"); //json file that says which tile number goes were
    this->levelMap = nlohmann::json::parse(levelMapFile);
    levelMapFile.close();
    this->mapData.mapWidth = levelMap["width"]; //schreibe in mapData die weite des Levels
    this->mapData.mapHeight = levelMap["height"];

    this->tileAtlasTexture = LoadTexture("assets/map/tileset.png");

    //go through all contents of "layers"
    for (auto const& layer : levelMap["layers"]) {
        //this asks for the name of each layer
        //then inserts its data into the vectors of the mapdata

        if (layer["name"] == "Ground") {
            for (auto const &tileID: layer["data"]) {
                mapData.layerGround.push_back(((int) tileID) - 1);

            }
        }

        if (layer["name"] == "Path") {
            for (auto const &tileID: layer["data"]) {
                mapData.layerPath.push_back(((int) tileID) - 1);

            }
        }

        if (layer["name"] == "Items") {
            for (auto const &tileID: layer["data"]) {
                mapData.layerItems.push_back(((int) tileID) - 1);

            }
        }

    }
}

void map::drawMap()
{
    for (int y{}; y < mapData.mapHeight; y++) {
        for (int x{}; x < mapData.mapWidth; x++) {
            if (mapData.layerGround[x + y * mapData.mapWidth] != -1)
                DrawTexturePro(tileAtlasTexture,
                               { (float)(mapData.layerGround[x + y * mapData.mapWidth] % this->tilemapData.tileMapWidth) * 16,(float)(mapData.layerGround[x + y * mapData.mapWidth] / this->tilemapData.tileMapWidth) * 16,16,16 },
                               { (float)(x * 16 * 2),(float)(y * 16 * 2),16 * 2,16 * 2},
                               {}, 0, WHITE);
        }
    }

    for (int y{}; y < mapData.mapHeight; y++) {
        for (int x{}; x < mapData.mapWidth; x++) {
            if (mapData.layerPath[x + y * mapData.mapWidth] != -1)
                DrawTexturePro(tileAtlasTexture,
                               { (float)(mapData.layerPath[x + y * mapData.mapWidth] % this->tilemapData.tileMapWidth) * 16,(float)(mapData.layerPath[x + y * mapData.mapWidth] / this->tilemapData.tileMapWidth) * 16 ,16,16 },
                               { (float)(x * 16 * 2),(float)(y * 16 * 2),16 * 2,16 * 2},
                               {}, 0, WHITE);
        }
    }

    for (int y{}; y < mapData.mapHeight; y++) {
        for (int x{}; x < mapData.mapWidth; x++) {
            if (mapData.layerItems[x + y * mapData.mapWidth] != -1)
                DrawTexturePro(tileAtlasTexture,
                               { (float)(mapData.layerItems[x + y * mapData.mapWidth] % this->tilemapData.tileMapWidth) * 16,(float)(mapData.layerPath[x + y * mapData.mapWidth] / this->tilemapData.tileMapWidth) * 16 ,16,16 },
                               { (float)(x * 16 * 2),(float)(y * 16 * 2),16 * 2,16 * 2},
                               {}, 0, WHITE);
        }
    }
}
