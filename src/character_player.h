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

    Inventory_Template<item_base*, 13> inventory;

};


#endif //RAYLIBSTARTER_CHARACTER_PLAYER_H
