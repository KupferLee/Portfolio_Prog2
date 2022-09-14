#include "character_base.h"

int character_base::Get_Position_X()
{
    current_tile.x = (position.x / 32) - 1;

    return current_tile.x;
}

int character_base::Get_Position_Y()
{
    current_tile.y = position.y / 32;

    return current_tile.y;
}

int character_base::Get_Position_Z()
{
    current_tile.z = 30 * (current_tile.y - 1) + current_tile.x;
    return current_tile.z;
}

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

    DrawText(std::to_string(Get_Position_X()).c_str(), 30, 30, 30, BLACK);
    DrawText(" / ", 60, 30, 30, BLACK);
    DrawText(std::to_string(Get_Position_Y()).c_str(), 110, 30, 30, BLACK);

    DrawText(std::to_string(Get_Position_Z()).c_str(), 30, 70, 30, BLACK);

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