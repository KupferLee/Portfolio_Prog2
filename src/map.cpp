#include "map.h"

map::map()
{
    //tileset Description File
    std::ifstream tilesetDescriptionFile("assets/map/tileset.json");

    //begin of parsing
    //level map file
    std::ifstream levelMapFile("assets/map/testmap.json"); //json file that says which tile number goes were
    this->Level_Map = nlohmann::json::parse(levelMapFile);
    levelMapFile.close();
    this->map_data.map_width = Level_Map["width"]; //schreibe in map_data die weite des Levels
    this->map_data.map_height = Level_Map["height"];

    this->Tileatlas_Texture = LoadTexture("assets/map/tileset.png");

}

void map::Parse()
{
    // go through all contents of "layers"
    // put numbers in vector accordingly to json file
    for (auto const& layer : Level_Map["layers"]) {
        //this asks for the name of each layer
        //then inserts its data into the vectors of the mapdata

        if (layer["name"] == "Ground") {
            for (auto const &tileID: layer["data"]) {
                map_data.layer_ground.push_back(((int) tileID) - 1);

            }
        }

        if (layer["name"] == "Path") {
            for (auto const &tileID: layer["data"]) {
                map_data.layer_path.push_back(((int) tileID) - 1);

            }
        }

        if (layer["name"] == "Items") {
            for (auto const &tileID: layer["data"]) {
                map_data.layer_items.push_back(((int) tileID) - 1);

            }
        }

    }
}

// generates a random map
// if there is already a grass tile the chance is higher that down or right will be another grass tile spawned
//
// NOTE: this is not failsafe yet!
void map::Randomize()
{
    //go through all contents of "layers"
    for (auto const& layer : Level_Map["layers"]) {
        //this asks for the name of each layer
        //then inserts its data into the vectors of the mapdata

        if (layer["name"] == "Ground") {
            for (auto const &tileID: layer["data"]) {
                map_data.layer_ground.push_back(((int) tileID) - 1);

            }
        }

        // NOTE: tiles begin with 0
        if (layer["name"] == "Path")
        {
            for (auto const &tileID: layer["data"]) {

                // as soon as first row down start here
                if (draw_tick > 30) {

                    // if above tile was grass then chance for grass is higher
                    if (map_data.layer_path.at(draw_tick - 30) == 0) {
                        // draw grass
                        if (rand() % 10 <= 6) {
                            map_data.layer_path.push_back(this->tile_grass);
                            map_data.layer_collision.push_back(false);
                        }
                        // draw nothing
                        else {
                            map_data.layer_path.push_back(this->tile_empty);
                            map_data.layer_collision.push_back(true);
                        }
                    }
                    // if tile before was grass then chance for grass is higher
                    else if (map_data.layer_path.at(draw_tick - 1) == 0) {
                        // draw grass
                        if (rand() % 10 <= 6) {
                            map_data.layer_path.push_back(this->tile_grass);
                            map_data.layer_collision.push_back(false);
                        }
                        //draw nothing
                        else {
                            map_data.layer_path.push_back(this->tile_empty);
                            map_data.layer_collision.push_back(true);
                        }
                    }

                    // if last tile wasnt grass then go on and draw no grass
                    else
                    {
                        map_data.layer_path.push_back(this->tile_empty);
                        map_data.layer_collision.push_back(true);
                    }

                }
                // first row of tiles all grass
                else {
                    map_data.layer_path.push_back(this->tile_grass);
                }

                this->draw_tick++;

            }
        }
    }

    // create hitboxes
    for (int i = 0; i < map_data.layer_collision.size(); i++) {
        if (map_data.layer_collision[i]) {
            Rectangle createdRectangle = {i % this->map_data.map_width * 32.0f + 32, (i / this->map_data.map_width * 32.0f) + 32, 32, 32 };
            hitboxes.push_back(createdRectangle);
        }
    }
}

void map::Draw_Collision()
{
    for (int i = 0; i < hitboxes.size(); i++) {
        DrawRectangleRec(hitboxes[i], BLACK);
    }
}

Rectangle map::Get_Rectangle(int i) { return hitboxes.at(i); }

int map::Get_Size_Collsion() { return map_data.layer_collision.size(); }

//set start and fin on grass tiles random
void map::RandomStartFin()
{
    for (auto const& layer : Level_Map["layers"]) {
        //this asks for the name of the layer
        //then inserts its data into the vectors of the mapdata

        if (layer["name"] == "Checkpoints") {
            for (auto const &tileID: layer["data"]) {
                this->checkpoint_tick++;

                // 30% chance to draw start tile
                // only if there is grass underneath
                if (rand() % 10 <= 3 && this->is_start_drawn == false && map_data.layer_path.at(checkpoint_tick) == 0) {
                    map_data.layer_checkpoints.push_back(this->tile_start);
                    this->is_start_drawn = true;
                }
                // if last 60 tiles then 90% chance to draw fin
                // only if there is grass underneath and next to it
                else if (rand() % 10 <= 9 && this->is_fin_drawn == false && map_data.layer_path.at(checkpoint_tick) == this->tile_grass && map_data.layer_path.at(checkpoint_tick - 1) == tile_grass && map_data.layer_path.at(checkpoint_tick + 1) == tile_grass && this->checkpoint_tick >= map_data.layer_ground.size() - 60) {
                    map_data.layer_checkpoints.push_back(this->tile_finish);
                    this->is_fin_drawn = true;
                }

                else {
                    map_data.layer_checkpoints.push_back(this->tile_empty);
                }
            }

        }
    }
}

void map::RandomItems() {
    for (auto const& layer : Level_Map["layers"]) {


        //this asks for the name of the layer
        //then inserts its data into the vectors of the mapdata
        if (layer["name"] == "Items") {

            for (auto const &tileID: layer["data"]) {
                this->item_tick++;

                // wenn grass dann 5% chance dass ein item spawned
                if (rand() % 20 <= 1 && map_data.layer_path.at(item_tick - 1) == this->tile_grass && map_data.layer_checkpoints.at(item_tick - 1) != this->tile_start && map_data.layer_checkpoints.at(item_tick - 1) != this->tile_finish && this->item_current < this->items_max)
                {
                    int number = rand() % 20;

                    switch (number)
                    {
                        // dagger
                        case 1:
                            map_data.layer_items.push_back(this->tile_dagger);
                            this->item_current++;
                            break;
                        // chest
                        case 2:
                            map_data.layer_items.push_back(this->tile_chest);
                            this->item_current++;
                            break;
                        // potion
                        case 3:
                            map_data.layer_items.push_back(this->tile_potion);
                            this->item_current++;
                            break;
                        // golden apple
                        case 4:
                            map_data.layer_items.push_back(this->tile_apple);
                            this->item_current++;
                            break;
                        // crystal
                        case 5:
                            map_data.layer_items.push_back(this->tile_crystal);
                            this->item_current++;
                            break;
                        // ring
                        case 6:
                            map_data.layer_items.push_back(this->tile_ring);
                            this->item_current++;
                            break;
                        // chestplate
                        case 7:
                            map_data.layer_items.push_back(this->tile_armor);
                            this->item_current++;
                            break;

                        default:
                            map_data.layer_items.push_back(this->tile_empty);
                            break;

                    }

                }
                // sonst empty
                else
                {
                    map_data.layer_items.push_back(this->tile_empty);
                }
            }
        }
    }

}

// draws map after a set json file
void map::Draw()
{
    // draw Ground
    for (int y{}; y < map_data.map_height; y++) {
        for (int x{}; x < map_data.map_width; x++) {
            if (map_data.layer_ground[x + y * map_data.map_width] != -1)
                DrawTexturePro(Tileatlas_Texture,
                               {(float)(map_data.layer_ground[x + y * map_data.map_width] % this->tilemap_data.tile_map_width) * 16, (float)(map_data.layer_ground[x + y * map_data.map_width] / this->tilemap_data.tile_map_width) * 16, 16, 16 },
                               { (float)(x * 16 * 2),(float)(y * 16 * 2),16 * 2,16 * 2},
                               {}, 0, WHITE);
        }
    }

    // Draw Path
    for (int y{}; y < map_data.map_height; y++) {
        for (int x{}; x < map_data.map_width; x++) {
            if (map_data.layer_path[x + y * map_data.map_width] != -1)
                DrawTexturePro(Tileatlas_Texture,
                               {(float)(map_data.layer_path[x + y * map_data.map_width] % this->tilemap_data.tile_map_width) * 16, (float)(map_data.layer_path[x + y * map_data.map_width] / this->tilemap_data.tile_map_width) * 16 , 16, 16 },
                               { (float)(x * 16 * 2),(float)(y * 16 * 2),16 * 2,16 * 2},
                               {}, 0, WHITE);
        }
    }

    // draw Start / Finish
    for (int y{}; y < map_data.map_height; y++) {
        for (int x{}; x < map_data.map_width; x++) {
            if (map_data.layer_checkpoints[x + y * map_data.map_width] != -1)
                DrawTexturePro(Tileatlas_Texture,
                               {(float)(map_data.layer_checkpoints[x + y * map_data.map_width] % this->tilemap_data.tile_map_width) * 16, (float)(map_data.layer_checkpoints[x + y * map_data.map_width] / this->tilemap_data.tile_map_width) * 16 , 16, 16 },
                               { (float)(x * 16 * 2),(float)(y * 16 * 2),16 * 2,16 * 2 },
                               {}, 0, WHITE);
        }
    }

    // Draw Items
    for (int y{}; y < map_data.map_height; y++) {
        for (int x{}; x < map_data.map_width; x++) {
            if (map_data.layer_items[x + y * map_data.map_width] != -1)
                DrawTexturePro(Tileatlas_Texture,
                               {(float)(map_data.layer_items[x + y * map_data.map_width] % this->tilemap_data.tile_map_width) * 16, (float)(map_data.layer_items[x + y * map_data.map_width] / this->tilemap_data.tile_map_width) * 16, 16, 16 },
                               { (float)(x * 16 * 2),(float)(y * 16 * 2),16 * 2,16 * 2},
                               {}, 0, WHITE);
        }
    }
}
