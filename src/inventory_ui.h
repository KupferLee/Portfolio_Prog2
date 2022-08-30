#ifndef RAYLIBSTARTER_INVENTORY_UI_H
#define RAYLIBSTARTER_INVENTORY_UI_H

#include "raylib.h"
#include <iostream>
#include <memory>
#include "character_player.h"


class inventory_ui {
public:
    inventory_ui();
    void update();
    void draw();
    bool isBackpackOpen();
    bool isInfoOpen();

protected:

    // player
    std::shared_ptr<character_player> player = std::make_shared<character_player>();
    // character_player* player = new character_player;

    // GUI
    Texture2D backpack;
    Texture2D inventory_base;
    Texture2D inventory_selection;
    Texture2D inventory_infos;
    Texture2D tileset;

    void set_slots();
    void navigate_inventory();

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

    // to give it current player slot
    int current_item_slot = 0;

    Rectangle ui_infos_position;
    Rectangle ui_slots[16]; // to determine x and y value for the ui_slots
    Rectangle inventory_position;

};


#endif //RAYLIBSTARTER_INVENTORY_UI_H
