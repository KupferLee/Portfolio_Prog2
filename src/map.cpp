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

    }
}

void map::drawMap()
{
    /*
    for (int y{}; y < mapData.mapHeight; y++) {
        for (int x{}; x < mapData.mapWidth; x++) {
            DrawTexturePro(tileAtlasTexture,
                           {
                                   (float)(mapData.layerGround[x + y * mapData.mapWidth] % this->tilemapData.tileMapWidth) * 16,
                                   (float)(mapData.layerGround[x + y * mapData.mapWidth] / this->tilemapData.tileMapWidth) * 16,
                                   16,16
                           },
                           {
                                   (float)(x * 16 * 4),
                                   (float)(y * 16 * 4),
                                   16 * 4,16 * 4
                           },
                           {}, 0, WHITE);
        }	//this draws the tiles on screen. This uses a loop for each dimension to make the readability a *bit* easier. Those lines are fairly long, but its not too complex once you get into it
    }   //also maybe these should be a function but that's for future me -o
    //I'm future me and still dont want to -o
     */

    for (int y{}; y < mapData.mapHeight; y++) {
        for (int x{}; x < mapData.mapWidth; x++) {
            if (mapData.layerGround[x + y * mapData.mapWidth] != -1)
                DrawTexturePro(tileAtlasTexture, { (float)(mapData.layerGround[x + y * mapData.mapWidth] % this->tilemapData.tileMapWidth) * 32,(float)(mapData.layerGround[x + y * mapData.mapWidth] / this->tilemapData.tileMapWidth) * 32 ,32,32 }, { (float)(x * 32 * 4),(float)(y * 32 * 4),32 * 4,32 * 4 }, {}, 0, WHITE);
        }
    }

    for (int y{}; y < mapData.mapHeight; y++) {
        for (int x{}; x < mapData.mapWidth; x++) {
            if (mapData.layerPath[x + y * mapData.mapWidth] != -1)
                DrawTexturePro(tileAtlasTexture, { (float)(mapData.layerPath[x + y * mapData.mapWidth] % this->tilemapData.tileMapWidth) * 32,(float)(mapData.layerPath[x + y * mapData.mapWidth] / this->tilemapData.tileMapWidth) * 32 ,32,32 }, { (float)(x * 32 * 4),(float)(y * 32 * 4),32 * 4,32 * 4 }, {}, 0, WHITE);
        }
    }
}
