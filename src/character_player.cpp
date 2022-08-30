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
    if (IsKeyPressed(KEY_K))
    {
        this->item_pickUp(crystal);
    }

    this->movement();
}


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


void character_player::item_pickUp(item_base* item)
{
    // only fill in the first 10 slots, not the 3 special ones
    if (this->container_current_slot < 10 && item != dagger && item != ring)
    {
        container.setItem(item, this->container_current_slot);

        this->container_current_slot++;
    }
        // if pick up weapon and special slot weapon empty fill in special slot
    else if (item == dagger && container.getItem(11) == NULL)
    {
        container.setItem(item, 11);
    }
        // if pick up ring and special slot ring empty fill in special slot
    else if (item == ring  && container.getItem(12) == NULL)
    {
        container.setItem(item, 12);
    }
    else
    {
        std::cout << "ERROR: No item assigned." << std::endl;
    }

}

int character_player::get_current_slot() { return this->container_current_slot; }

int character_player::get_item_id(int slot) { return container.getItem(slot)->getID()*16; }

std::string character_player::get_item_name(int slot) { return container.getItem(slot)->getName(); }

int character_player::get_item_weight(int slot) { return container.getItem(slot)->getWeight(); }

int character_player::get_item_value(int slot) { return container.getItem(slot)->getValue(); }

std::string character_player::get_item_description(int slot) { return container.getItem(slot)->getDescription(); }
