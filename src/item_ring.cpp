#include "item_ring.h"

item_ring::item_ring()
{
    this->name = "Ring";
    this->description = "A magic Ring. +10 Strength";
    this->value = 8;
    this->weight = 0;
    this->texture_id = 9;
    this->texture = LoadTexture("assets/graphics/gui/item_ring.png");

    // if worn gives a Player + strength
    this->plus_strength = 10;
}

int item_ring::Get_Strength() { return this-> plus_strength; }