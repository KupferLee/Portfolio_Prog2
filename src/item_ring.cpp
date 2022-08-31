#include "item_ring.h"

item_ring::item_ring()
{
    this->name = "Ring";
    this->description = "+5 Strength";
    this->value = 7;
    this->weight = 1;
    this->texture_id = 9;
    this->texture = LoadTexture("assets/graphics/gui/item_ring.png");

    // if worn gives a player +5 strength
    this->plus_strength = 5;
}

int item_ring::get_strength() { return this-> plus_strength; }