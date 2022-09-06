//
// Created by Lee on 13.08.2022.
//

#ifndef RAYLIBSTARTER_CHARACTER_PLAYER_H
#define RAYLIBSTARTER_CHARACTER_PLAYER_H

#include "character_base.h"
#include "item_base.h"
#include "inventory_template.h"
#include "item_dagger.h"
#include "item_chest.h"
#include "item_potion.h"
#include "item_apple.h"
#include "item_crystal.h"
#include "item_ring.h"
#include "item_armor.h"


class character_player : public character_base {
public:
    character_player();
    void update();

protected:

    void movement();
    void calculate_weight();

    bool can_move = true;
    int base_strength = 20; // determines how much weight can be put in inventory
    int strength = 0;
    int total_weight = 0;

    // item objects
    item_dagger* dagger = new item_dagger;
    item_chest* chest = new item_chest;
    item_potion* potion = new item_potion;
    item_apple* golden_apple = new item_apple;
    item_crystal* crystal = new item_crystal;
    item_ring* ring = new item_ring;
    item_armor* armor = new item_armor;

    // container for item objects
    Inventory_Template<item_base*, 14> container;
    int container_current_slot = 0;
    void item_pickUp(item_base* item);
    //void item_drop();

    bool is_weapons_occupied;
    bool is_rings_occupied;
    bool is_armor_occupied;

    // sort algorithm
    void sort_by_weight();
    void sort_by_value();

    Texture2D sort_buttons;
    Texture2D sort_select;
    Rectangle sort_base_position;
    Rectangle sort_select_position[2];

    int current_button = 0;
    bool is_sort_open = false;

    void draw_sort_buttons();
    void update_sort_buttons();

public:
    int get_current_slot();
    Texture2D get_texture(int slot);
    std::string get_item_name(int slot);
    int get_item_weight(int slot);
    int get_item_value(int slot);
    std::string get_item_description(int slot);

    bool get_weapons_occupied();
    bool get_rings_occupied();
    bool get_armor_occupied();

    int get_total_weight();
    int get_total_strength();

    void set_move(bool move);

    void render_gui();
    bool get_sort_open();

};


#endif //RAYLIBSTARTER_CHARACTER_PLAYER_H
