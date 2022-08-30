#include "item_apple.h"

item_apple::item_apple()
{
    this->name = "Golden Apple";
    this->description = "A golden fruit.";
    this->value = 8;
    this->weight = 1;
    this->texture_id = 7;
    this->texture = LoadTexture("assets/graphics/gui/item_apple.png");
}