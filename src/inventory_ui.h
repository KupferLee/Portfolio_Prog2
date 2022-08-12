//
// Created by Lee on 06.08.2022.
//

#ifndef RAYLIBSTARTER_INVENTORY_UI_H
#define RAYLIBSTARTER_INVENTORY_UI_H

#include "raylib.h"
#include <iostream>
#include "inventory_template.h"
#include "item_dagger.h"
#include "item_chest.h"

class inventory_ui {
public:
    inventory_ui();
    void update();
    void draw();
    bool isBackpackOpen();
    bool isInfoOpen();

protected:

    // container for item objects
    item_dagger* dagger = new item_dagger;
    item_chest* chest = new item_chest;
    Inventory_Template<item_base*, 16> container;

    int container_current_slot = 0;

    void item_pickUp(item_base* item);
    void item_drop();


    // GUI
    Texture2D backpack;
    Texture2D inventory_base;
    Texture2D inventory_selection;
    Texture2D inventory_infos;
    Texture2D tileset;

    void set_slots();
    void slots_up();
    void slots_down();

    void draw_items();
    void draw_current_slot(int i);
    void draw_info();

    // variables have gui in front of them so i can see if they are for the object container or for gui textures
    bool gui_isOpen = false;
    bool gui_isInfo = false;
    float gui_scale_factor = 6;
    int gui_current_slot = 0;
    int gui_special_slot_weapons = 13;
    int gui_special_slot_rings = 14;
    int gui_special_slot_x = 15;
    int gui_max_slots = 16;
    Vector2 ui_infos_position;
    Vector2 ui_slots[16]; // to determine x and y value for the ui_slots

};


#endif //RAYLIBSTARTER_INVENTORY_UI_H
