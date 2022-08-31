//
// Created by Lee on 13.08.2022.
//

#ifndef RAYLIBSTARTER_CHARACTER_PLAYER_H
#define RAYLIBSTARTER_CHARACTER_PLAYER_H

#include "character_base.h"


class character_player : public character_base {
public:
    character_player();
    void update();

protected:

    void movement();

    bool canMove = true;
    int strength = 15; // determines how many items can be put in inventory

    // item objects
    item_dagger* dagger = new item_dagger;
    item_chest* chest = new item_chest;
    item_potion* potion = new item_potion;
    item_apple* golden_apple = new item_apple;
    item_crystal* crystal = new item_crystal;
    item_ring* ring = new item_ring;

    // container for item objects
    Inventory_Template<item_base*, 13> container;
    int container_current_slot = 0;
    void item_pickUp(item_base* item);
    //void item_drop();

    bool is_weapons_occupied;
    bool is_rings_occupied;

public:
    int get_current_slot();
    Texture2D get_texture(int slot);
    std::string get_item_name(int slot);
    int get_item_weight(int slot);
    int get_item_value(int slot);
    std::string get_item_description(int slot);

    bool get_weapons_occupied();
    bool get_rings_occupied();

};


#endif //RAYLIBSTARTER_CHARACTER_PLAYER_H
