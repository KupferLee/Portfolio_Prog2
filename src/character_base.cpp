#include "character_base.h"

int character_base::Get_Position_X()
{
    this->current_tile.x = (this->position.x / 32) - 1;

    return current_tile.x;
}

int character_base::Get_Position_Y()
{
    this->current_tile.y = this->position.y / 32;

    return current_tile.y;
}

int character_base::Get_Position_Z()
{
    this->current_tile.z = 30 * (this->current_tile.y - 1) + this->current_tile.x;
    return current_tile.z;
}

void character_base::Draw()
{

    DrawTexturePro(this->texture,
                   {(float)facing_direction*32, (float)facing_direction*32, 32, 32},
                   {this->position.x, this->position.y, 32, 32},
                   {32, 32}, 0, WHITE);



}

