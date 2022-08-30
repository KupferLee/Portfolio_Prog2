#include "item_potion.h"

item_potion::item_potion()
{
    this->name = "Potion";
    this->description = "It's an unknown liquid.";
    this->value = 5;
    this->weight = 2;
    this->texture_id = 6;
    this->texture = LoadTexture("assets/graphics/gui/item_potion.png");
}