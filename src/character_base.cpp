#include "character_base.h"

Vector2 character_base::get_position() { return this->position; }

void character_base::Draw()
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

bool character_base::Check_Collision(Rectangle obstacle)
{
    if (CheckCollisionRecs(hitbox, obstacle))
    {
        return true;
    }
    else
    {
        return false;
    }
}

Rectangle character_base::Get_Hitbox() {return this->hitbox; }