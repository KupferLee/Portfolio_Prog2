#include "character_base.h"

Vector2 character_base::get_position() { return this->position; }

void character_base::draw()
{
    if (IsKeyDown(KEY_H))
    {
        DrawRectangle(hitbox.x, hitbox.y, hitbox.width, hitbox.height, WHITE);
    }

    DrawTexturePro(this->texture,
                   {(float)facing_direction*32, (float)facing_direction*32, 32, 32},
                   {this->position.x, this->position.y, 32, 32},
                   {32, 32}, 0, WHITE);

}
