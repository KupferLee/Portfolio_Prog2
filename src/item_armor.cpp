//
// Created by Lee on 31.08.2022.
//

#include "item_armor.h"

item_armor::item_armor()
{
    this->value = 5;
    this->name = "Armor";
    this->description = "A heavy armor.";
    this->weight = 8;
    this->texture_id = 10;
    this->texture = LoadTexture("assets/graphics/gui/item_armor.png");
}
