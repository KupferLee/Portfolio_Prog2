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
        if (layer["name"] == "Path")
        {
            for (auto const &tileID: layer["data"]) {

                // as soon as first row down start here
                if (drawTick > 30) {

                    // if above tile was grass then chance for grass is higher
                    if (mapData.layerPath.at(drawTick - 30) == 0) {
                        // draw grass
                        if (rand() % 10 <= 6) {
                            mapData.layerPath.push_back(this->tile_grass);
                        }
                        // draw nothing
                        else {
                            mapData.layerPath.push_back(this->tile_empty);
                        }
                    }
                    // if tile before was grass then chance for grass is higher
                    else if (mapData.layerPath.at(drawTick - 1) == 0) {
                        // draw grass
                        if (rand() % 10 <= 6) {
                            mapData.layerPath.push_back(this->tile_grass);
                        }
                        //draw nothing
                        else {
                            mapData.layerPath.push_back(this->tile_empty);
                        }
                    }

                    // if last tile wasnt grass then go on and draw no grass
                    else
                    {
                        mapData.layerPath.push_back(this->tile_empty);
                    }

                }
                // first row of tiles all grass
                else {
                    mapData.layerPath.push_back(this->tile_grass);
                }

                this->drawTick++;

            }
        }
    }
}

//set start and fin on grass tiles random
void map::randomStartFin()
{
    for (auto const& layer : levelMap["layers"]) {
        //this asks for the name of the layer
        //then inserts its data into the vectors of the mapdata

        if (layer["name"] == "Checkpoints") {
            for (auto const &tileID: layer["data"]) {
                this->checkpointTick++;

                // 30% chance to draw start tile
                // only if there is grass underneath
                if (rand() % 10 <= 3 && this->isStartDrawn == false && mapData.layerPath.at(checkpointTick) == 0) {
                    mapData.layerCheckpoints.push_back(this->tile_start);
                    this->isStartDrawn = true;
                }
                // if last 60 tiles then 90% chance to draw fin
                // only if there is grass underneath and next to it
                else if (rand() % 10 <= 9 && this->isFinDrawn == false && mapData.layerPath.at(checkpointTick) == this->tile_grass && mapData.layerPath.at(checkpointTick - 1) == tile_grass && mapData.layerPath.at(checkpointTick + 1) == tile_grass && this->checkpointTick >= mapData.layerGround.size() - 60) {
                    mapData.layerCheckpoints.push_back(this->tile_finish);
                    this->isFinDrawn = true;
                }

                else {
                    mapData.layerCheckpoints.push_back(this->tile_empty);
                }
            }

        }
    }
}

void map::randomItems() {
    for (auto const& layer : levelMap["layers"]) {


        //this asks for the name of the layer
        //then inserts its data into the vectors of the mapdata
        if (layer["name"] == "Items") {

            for (auto const &tileID: layer["data"]) {
                this->itemTick++;

                // wenn grass dann 5% chance dass ein item spawned
                if (rand() % 20 <= 1 && mapData.layerPath.at(itemTick-1) == this->tile_grass && mapData.layerCheckpoints.at(itemTick-1) != this->tile_start && mapData.layerCheckpoints.at(itemTick-1) != this->tile_finish && this->itemCurrent < this->itemsMax)
                {
                    int number = rand() % 20;

                    switch (number)
                    {
                        // dagger
                        case 1:
                            mapData.layerItems.push_back(this->tile_dagger);
                            this->itemCurrent++;
                            break;
                        // chest
                        case 2:
                            mapData.layerItems.push_back(this->tile_chest);
                            this->itemCurrent++;
                            break;
                        // potion
                        case 3:
                            mapData.layerItems.push_back(this->tile_potion);
                            this->itemCurrent++;
                            break;
                        // golden apple
                        case 4:
                            mapData.layerItems.push_back(this->tile_apple);
                            this->itemCurrent++;
                            break;
                        // crystal
                        case 5:
                            mapData.layerItems.push_back(this->tile_crystal);
                            this->itemCurrent++;
                            break;
                        // ring
                        case 6:
                            mapData.layerItems.push_back(this->tile_ring);
                            this->itemCurrent++;
                            break;

                        default:
                            mapData.layerItems.push_back(this->tile_empty);
                            break;

                    }
                    /*
                    // 20% chance auf chest
                    // 0 - 2
                    if (rand() % 10 <= 1)
                    {
                        mapData.layerItems.push_back(this->tile_chest);
                        this->itemCurrent++;
                    }
                    // 30% dagger
                    // 7 - 9
                    else if (rand() % 10 >= 7)
                    {
                        mapData.layerItems.push_back(this->tile_dagger);
                        this->itemCurrent++;
                    }
                    else
                    {
                        mapData.layerItems.push_back(this->tile_empty);
                    }
                     */

                }
                // sonst empty
                else
                {
                    mapData.layerItems.push_back(this->tile_empty);
                }
            }
        }
    }

}

// draws map after a set json file
void map::draw()
{
    // draw Ground
    for (int y{}; y < mapData.mapHeight; y++) {
        for (int x{}; x < mapData.mapWidth; x++) {
            if (mapData.layerGround[x + y * mapData.mapWidth] != -1)
                DrawTexturePro(tileAtlasTexture,
                               { (float)(mapData.layerGround[x + y * mapData.mapWidth] % this->tilemapData.tileMapWidth) * 16,(float)(mapData.layerGround[x + y * mapData.mapWidth] / this->tilemapData.tileMapWidth) * 16,16,16 },
                               { (float)(x * 16 * 2),(float)(y * 16 * 2),16 * 2,16 * 2},
                               {}, 0, WHITE);
        }
    }

    // Draw Path
    for (int y{}; y < mapData.mapHeight; y++) {
        for (int x{}; x < mapData.mapWidth; x++) {
            if (mapData.layerPath[x + y * mapData.mapWidth] != -1)
                DrawTexturePro(tileAtlasTexture,
                               { (float)(mapData.layerPath[x + y * mapData.mapWidth] % this->tilemapData.tileMapWidth) * 16,(float)(mapData.layerPath[x + y * mapData.mapWidth] / this->tilemapData.tileMapWidth) * 16 ,16,16 },
                               { (float)(x * 16 * 2),(float)(y * 16 * 2),16 * 2,16 * 2},
                               {}, 0, WHITE);
        }
    }

    // draw Start / Finish
    for (int y{}; y < mapData.mapHeight; y++) {
        for (int x{}; x < mapData.mapWidth; x++) {
            if (mapData.layerCheckpoints[x + y * mapData.mapWidth] != -1)
                DrawTexturePro(tileAtlasTexture,
                               { (float)(mapData.layerCheckpoints[x + y * mapData.mapWidth] % this->tilemapData.tileMapWidth) * 16,(float)(mapData.layerCheckpoints[x + y * mapData.mapWidth] / this->tilemapData.tileMapWidth) * 16 ,16,16 },
                               { (float)(x * 16 * 2),(float)(y * 16 * 2),16 * 2,16 * 2},
                               {}, 0, WHITE);
        }
    }

    // Draw Items
    for (int y{}; y < mapData.mapHeight; y++) {
        for (int x{}; x < mapData.mapWidth; x++) {
            if (mapData.layerItems[x + y * mapData.mapWidth] != -1)
                DrawTexturePro(tileAtlasTexture,
                               { (float)(mapData.layerItems[x + y * mapData.mapWidth] % this->tilemapData.tileMapWidth) * 16,(float)(mapData.layerItems[x + y * mapData.mapWidth] / this->tilemapData.tileMapWidth) * 16,16,16 },
                               { (float)(x * 16 * 2),(float)(y * 16 * 2),16 * 2,16 * 2},
                               {}, 0, WHITE);
        }
    }
}
