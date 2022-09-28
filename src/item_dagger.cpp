#include "item_dagger.h"

item_dagger::item_dagger()
{
    this->name = "Dagger";
    this->description = "Its a pointy weapon.";
    this->value = 5;
    this->weight = 2;
    this->texture_id = 4;
    this->texture = LoadTexture("assets/graphics/gui/item_dagger.png");
}