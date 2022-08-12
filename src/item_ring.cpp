#include "item_ring.h"

item_ring::item_ring()
{
    this->name = "Ring";
    this->description = "+5 Strength";
    this->value = 7;
    this->weight = 1;
    this->texture_id = 9;

    // if worn gives a player +5 strength
    this->plus_strength = 5;
}