#include "item_crystal.h"

item_crystal::item_crystal()
{
    this->name = "Crystal";
    this->description = "Its a shimmering stone.";
    this->value = 6;
    this->weight = 3;
    this->texture_id = 8;
    this->texture = LoadTexture("assets/graphics/gui/item_crystal.png");

}