//
// Created by Lee on 13.08.2022.
//

#include "character_player.h"

character_player::character_player()
{
    this->texture = LoadTexture("assets/graphics/characters/player_32.png");

    this->position = {32, 32};
    this->movement_speed = 3;
}

void character_player::update()
{
    this->movement();
}

// TODO: put inventory from inventory_ui in here


void character_player::movement()
{
    //W A S D
    if (this->canMove == true)
    {
        // up
        if (IsKeyDown(KEY_W))
        {
            this->position.y = this->position.y - this->movement_speed;
            this->facing_direction = up;
        }
            // left
        else if (IsKeyDown(KEY_A))
        {
            this->position.x = this->position.x - this->movement_speed;
            this->facing_direction = down;
        }
            // down
        else if (IsKeyDown(KEY_S))
        {
            this->position.y = this->position.y + this->movement_speed;
            this->facing_direction = down;
        }
            //right
        else if (IsKeyDown(KEY_D))
        {
            this->position.x = this->position.x + this->movement_speed;
            this->facing_direction = down;
        }
    }
}