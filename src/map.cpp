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

}

void map::parse()
{
    // go through all contents of "layers"
    // put numbers in vector accordingly to json file
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

void map::randomizeTiles() {
    // draw grass
    if (rand() % 10 <= 4) {
        mapData.layerPath.push_back(0);
    }
    // draw start
    else if (rand() % 10 <= 5 && this->isStartDrawn == false) {
        mapData.layerPath.push_back(3);
        this->isStartDrawn = true;
    }
    // draw finished
    else if (rand() % 10 <= 1 && this->isFinDrawn == false &&
               this->drawTick >= mapData.layerGround.size() - 60) {
        mapData.layerPath.push_back(2);
        this->isFinDrawn = true;
    }
    // draw nothing
    else {
        mapData.layerPath.push_back(-1);
    }
}

// generates a random map
// if there is already a grass tile the chance is higher that down or right will be another grass tile spawned
//
// NOTE: this is not failsafe yet!
void map::random()
{
    //go through all contents of "layers"
    for (auto const& layer : levelMap["layers"]) {
        //this asks for the name of each layer
        //then inserts its data into the vectors of the mapdata

        if (layer["name"] == "Ground") {
            for (auto const &tileID: layer["data"]) {
                mapData.layerGround.push_back(((int) tileID) - 1);

            }
        }

        // NOTE: tiles begin with 0
        if (layer["name"] == "Path") {
            for (auto const &tileID: layer["data"]) {

                // as soon as first row down start here
                if (drawTick > 30) {

                    // if above tile was grass then chance for grass is higher
                    if (mapData.layerPath.at(drawTick - 30) == 0) {
                        // draw grass
                        if (rand() % 10 <= 6) {
                            mapData.layerPath.push_back(0);
                        }
                        //draw start
                        else if (rand() % 10 <= 5 && this->isStartDrawn == false) {
                            mapData.layerPath.push_back(3);
                            this->isStartDrawn = true;
                        }
                        // draw fin
                        else if (rand() % 10 <= 1 && this->isFinDrawn == false &&
                                 this->drawTick >= mapData.layerGround.size() - 60) {
                            mapData.layerPath.push_back(2);
                            this->isFinDrawn = true;
                        }
                        // draw nothing
                        else {
                            mapData.layerPath.push_back(-1);
                        }
                    }

                    // if tile before was grass then chance for grass is higher
                    else if (mapData.layerPath.at(drawTick - 1) == 0) {
                        // draw grass
                        if (rand() % 10 <= 6) {
                            mapData.layerPath.push_back(0);
                        }

                        //draw start
                        else if (rand() % 10 <= 5 && this->isStartDrawn == false) {
                            mapData.layerPath.push_back(3);
                            this->isStartDrawn = true;
                        }
                        // draw fin
                        else if (rand() % 10 <= 1 && this->isFinDrawn == false &&
                                 this->drawTick >= mapData.layerGround.size() - 60) {
                            mapData.layerPath.push_back(2);
                            this->isFinDrawn = true;
                        }
                         
                        //draw nothing
                        else {
                            mapData.layerPath.push_back(-1);
                        }
                    }

                    // if last tile wasnt grass then go on
                    else
                    {
                        mapData.layerPath.push_back(-1);
                        //this->randomizeTiles();
                    }

                }
                // randomize first row of tiles
                else if (rand() % 10 <= 4) {
                    mapData.layerPath.push_back(0);
                }
                else {
                    mapData.layerPath.push_back(0);
                }

            this->drawTick++;

        }
    }


        if (layer["name"] == "Items") {
            for (auto const &tileID: layer["data"]) {
                mapData.layerItems.push_back(((int) tileID) - 1);

            }
        }

    }
}

//set start and fin on grass tiles random
void map::randomStartFin()
{

}

// draws map after a set json file
void map::draw()
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
