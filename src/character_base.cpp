#include "character_base.h"

Vector2 character_base::getPosition() { return this->position; }

void character_base::draw()
{
    DrawTexturePro(this->texture,
                   {(float)facing_direction*32, (float)facing_direction*32, 32, 32},
                   {this->position.x, this->position.y, 32, 32},
                   {32, 32}, 0, WHITE);
}