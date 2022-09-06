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
    if (IsKeyPressed(KEY_M))
    {
        item_pickUp(crystal);
        item_pickUp(golden_apple);
        item_pickUp(potion);
        item_pickUp(chest);
        item_pickUp(golden_apple);
        item_pickUp(crystal);
        item_pickUp(golden_apple);
        item_pickUp(chest);
        item_pickUp(potion);
        item_pickUp(crystal);

        item_pickUp(dagger);
        item_pickUp(ring);
        item_pickUp(armor);

        calculate_weight();
    }
    else if (IsKeyPressed(KEY_N))
    {
        sort_by_weight();
    }
    else if (IsKeyPressed(KEY_B))
    {
        sort_by_value();
    }

    if(container.getItem(11) == ring)
    {
        this->strength = base_strength + ring->get_strength();
    }
    else
    {
        this->strength = base_strength;
    }

    // disable movement when total weight is more than player strength
    if (total_weight < strength)
    {
        movement();
    }
}


void character_player::movement()
{
    //W A S D
    if (this->can_move == true)
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
    if (this->container_current_slot < 10 && item != dagger && item != ring && item != armor)
    {
        container.setItem(item, this->container_current_slot);

        this->container_current_slot++;
    }
    // if pick up weapon and special slot weapon empty fill in special slot
    else if (item == dagger && container.getItem(10) == NULL)
    {
        container.setItem(item, 10);
        is_weapons_occupied = true;
    }
    // if pick up ring and special slot ring empty fill in special slot
    else if (item == ring  && container.getItem(11) == NULL)
    {
        container.setItem(item, 11);
        is_rings_occupied = true;
    }
    else if (item == armor && container.getItem(12) == NULL)
    {
        container.setItem(item, 12);
        is_armor_occupied = true;
    }
    else
    {
        std::cout << "ERROR: No item assigned." << std::endl;
    }

}

void character_player::calculate_weight()
{
    // first reset total weight
    this->total_weight = 0;

    // count through normal items and add weight
    for (int i = 0; i < container_current_slot; i++)
    {
        this->total_weight = total_weight + container.getItem(i)->getWeight();
    }
    // count weapons and rings and armor special if they are assigned
    if (container.getItem(10) == dagger)
    {
        this->total_weight = total_weight + container.getItem(10)->getWeight();
    }
    if (container.getItem(11) == ring)
    {
        this->total_weight = total_weight + container.getItem(11)->getWeight();
    }
    if (container.getItem(12) == armor)
    {
        this->total_weight = total_weight + container.getItem(12)->getWeight();
    }
}

// sort algorithm
void character_player::sort_by_weight()
{
    // go through all set item slots
    for (int i = 0; i < container_current_slot; i++)
    {
        // actual sort algorithm
        for (int i = 0; i < container_current_slot - 1; i++)
        {
            if (container.getItem(i)->getWeight() > container.getItem(i + 1)->getWeight())
            {
                // set item from i in extra slot
                container.setItem(container.getItem(i), 13);
                // set item from i + 1 in i
                container.setItem(container.getItem(i+ 1), i);
                // set item from extra slot in i + 1
                container.setItem(container.getItem(13), i + 1);
            }
        }
    }

}

void character_player::sort_by_value()
{
    // go through all set item slots
    for (int i = 0; i < container_current_slot; i++)
    {
        // actual sort algorithm
        for (int i = 0; i < container_current_slot - 1; i++)
        {
            if (container.getItem(i)->getValue() < container.getItem(i + 1)->getValue())
            {
                // set item from i in extra slot
                container.setItem(container.getItem(i), 13);
                // set item from i + 1 in i
                container.setItem(container.getItem(i + 1), i);
                // set item from extra slot in i + 1
                container.setItem(container.getItem(13), i + 1);
            }
        }
    }
}

// return item attributes
int character_player::get_current_slot() { return this->container_current_slot; }

Texture2D character_player::get_texture(int slot) { return container.getItem(slot)->getTexture(); }

std::string character_player::get_item_name(int slot) { return container.getItem(slot)->getName(); }

int character_player::get_item_weight(int slot) { return container.getItem(slot)->getWeight(); }

int character_player::get_item_value(int slot) { return container.getItem(slot)->getValue(); }

std::string character_player::get_item_description(int slot) { return container.getItem(slot)->getDescription(); }

bool character_player::get_weapons_occupied() { return is_weapons_occupied; }

bool character_player::get_rings_occupied() { return is_rings_occupied; }

bool character_player::get_armor_occupied() { return is_armor_occupied; }

int character_player::get_total_weight() { return total_weight; }

int character_player::get_total_strength() { return this->strength; }

void character_player::set_move(bool move) { can_move = move; }

