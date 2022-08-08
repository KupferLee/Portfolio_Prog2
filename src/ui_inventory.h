//
// Created by Lee on 06.08.2022.
//

#ifndef RAYLIBSTARTER_UI_INVENTORY_H
#define RAYLIBSTARTER_UI_INVENTORY_H

#include "raylib.h"

class ui_inventory {
public:
    ui_inventory();
    void update();
    void draw();
    bool isBackpackOpen();
    bool isInfoOpen();

protected:
    Texture2D backpack;
    Texture2D inventory_base;
    Texture2D inventory_selection;
    Texture2D inventory_infos;

    void set_slots();
    void slots_up();
    void slots_down();

    bool isOpen = false;
    bool isInfo = false;
    float scale_factor = 6;
    int current_slot = 0;
    int special_slot_weapons = 3;
    int special_slot_rings = 9;
    int special_slot_x = 15;
    Vector2 infos_position;
    Vector2 slots[16]; // to determine x and y value for the slots


};


#endif //RAYLIBSTARTER_UI_INVENTORY_H
