#include "item_chest.h"

item_chest::item_chest()
{
    this->value = 7;
    this->name = "Treasure Chest";
    this->description = "There is something inside.";
    this->weight = 5;
    this->texture_id = 5;
    this->texture = LoadTexture("assets/graphics/gui/item_chest.png");
}