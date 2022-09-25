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

    character_player* Player = new character_player;

protected:

    // GUI
    Texture2D backpack;
    Texture2D inventory_base;
    Texture2D inventory_selection;
    Texture2D inventory_infos;

    void Set_Slots();
    void Navigate_Inventory();

    void Draw_Items();
    void Draw_Current_Slot(int i);
    void Draw_Info();

    bool is_open = false;
    bool is_info = false;
    float scale_factor = 6;
    int current_slot = 0;
    int special_slot_weapons = 10;
    int special_slot_rings = 11;
    int special_slot_armor = 12;

    int slot_offset = 19 * scale_factor;

    int backpack_slot = 0; // determines if backpack is drawn on left or right side

    // to determine x and y value for the slot_position
    Vector2 weight_position[2];
    Vector2 infos_position;
    Rectangle slot_position[16];
    Rectangle inventory_position;
    Rectangle backpack_position[2];

    // tutorial
    Texture2D tutorial_base;

    bool is_tutorial = true;

    void Draw_Tutorial();

};


#endif //RAYLIBSTARTER_INVENTORY_UI_H
