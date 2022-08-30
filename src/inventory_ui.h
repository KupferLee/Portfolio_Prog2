#ifndef RAYLIBSTARTER_INVENTORY_UI_H
#define RAYLIBSTARTER_INVENTORY_UI_H

#include "raylib.h"
#include <iostream>
#include "inventory_template.h"
#include "item_dagger.h"
#include "item_chest.h"
#include "item_potion.h"
#include "item_apple.h"
#include "item_crystal.h"
#include "item_ring.h"

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
    item_potion* potion = new item_potion;
    item_apple* golden_apple = new item_apple;
    item_crystal* crystal = new item_crystal;
    item_ring* ring = new item_ring;

    Inventory_Template<item_base*, 13> container;

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
    void navigate_inventory();
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
    int gui_special_slot_weapons = 10;
    int gui_special_slot_rings = 11;
    int gui_special_slot_x = 12;
    int gui_max_slots = 13;
    int slot_offset = 19 * gui_scale_factor;

    Rectangle ui_infos_position;
    Rectangle ui_slots[16]; // to determine x and y value for the ui_slots
    Rectangle inventory_position;

};


#endif //RAYLIBSTARTER_INVENTORY_UI_H
