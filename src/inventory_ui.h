#ifndef RAYLIBSTARTER_INVENTORY_UI_H
#define RAYLIBSTARTER_INVENTORY_UI_H

#include "raylib.h"
#include <iostream>
#include <memory>
#include "character_player.h"


class inventory_ui {
public:
    inventory_ui();
    void Update();
    void Draw();
    bool Is_Backpack_Open();
    bool Is_Info_Open();
    character_player* Player = new character_player;

protected:

    // GUI
    Texture2D backpack;
    Texture2D inventory_base;
    Texture2D inventory_selection;
    Texture2D inventory_infos;
    Texture2D tileset;

    void Set_Slots();
    void navigate_inventory();

    void draw_items();
    void draw_current_slot(int i);
    void draw_info();

    bool is_open = false;
    bool gui_is_info = false;
    float gui_scale_factor = 6;
    int gui_current_slot = 0;
    int special_slot_weapons = 10;
    int special_slot_rings = 11;
    int special_slot_armor = 12;

    int slot_offset = 19 * gui_scale_factor;

    // determines if backpack is drawn on left or right side
    int backpack_slot = 0;

    Vector2 ui_weight_position[2];
    Vector2 ui_infos_position;
    Rectangle ui_slots[16]; // to determine x and y value for the ui_slots
    Rectangle inventory_position;
    Rectangle backpack_position[2];

    // tutorial
    Texture2D tutorial_base;

    bool is_tutorial = true;

    void draw_tutorial();

};


#endif //RAYLIBSTARTER_INVENTORY_UI_H
