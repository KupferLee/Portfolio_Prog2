//
// Created by Lee on 13.08.2022.
//

#include "character_player.h"

character_player::character_player()
{
    // player
    this->texture = LoadTexture("assets/graphics/characters/player_32.png");
    this->position = {32, 32};
    this->movement_speed = 3;

    // sort gui
    this->sort_buttons = LoadTexture("assets/graphics/gui/sort_buttons.png");
    this->sort_select = LoadTexture("assets/graphics/gui/sort_button_select.png");

    // slots get assigned here because the position depends on the texture measurements
    this->sort_base_position = {(float)GetScreenWidth()/2 - sort_buttons.width/2*6, (float)GetScreenHeight()/2 - sort_buttons.height/2*6, (float)sort_buttons.width*6, (float)sort_buttons.height*6};
    this->sort_select_position[0] = {(float)sort_base_position.x + 9 * 6, (float)sort_base_position.y + 4 * 6, (float)sort_select.width * 6, (float)sort_select.height * 6};
    this->sort_select_position[1] = {(float)sort_select_position[0].x, (float)sort_select_position[0].y + (sort_select.height + 1) * 6, (float)sort_select.width * 6, (float)sort_select.height * 6};
    this->sort_select_position[2] = {(float)sort_select_position[0].x, (float)sort_select_position[1].y + (sort_select.height + 1) * 6, (float)sort_select.width * 6, (float)sort_select.height * 6};
}

void character_player::update()
{
    update_sort_buttons();

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
    else if (is_sort_open == true && IsKeyPressed(KEY_ENTER))
    {
        if (current_button == 0)
        {
            sort_by_weight();
        }
        else if (current_button == 1)
        {
            sort_by_value();
        }
        else if (current_button == 2)
        {
            sort_by_name();
        }

        current_button = 0;
        is_sort_open = false;
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

    std::cout << "DEBUG: Items are sorted by weight now." << std::endl;
}

void character_player::sort_by_value()
{
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
                container.setItem(container.getItem(i+ 1), i);
                // set item from extra slot in i + 1
                container.setItem(container.getItem(13), i + 1);
            }
        }
    }

    std::cout << "DEBUG: Items are sorted by value now." << std::endl;
}

void character_player::sort_by_name()
{
    // go through all set item slots
    for (int i = 0; i < container_current_slot; i++)
    {
        // actual sort algorithm
        // this currently sorts by value lol
        for (int i = 0; i < container_current_slot - 1; i++)
        {
            if (container.getItem(i)->getName() > container.getItem(i + 1)->getName())
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

    std::cout << "DEBUG: Items are sorted by name now." << std::endl;
}

// sort gui
void character_player::update_sort_buttons()
{
    if (IsKeyPressed(KEY_TAB) && is_sort_open == true|| IsKeyPressed(KEY_I) && is_sort_open == true)
    {
        is_sort_open = false;
    }
    else if (IsKeyPressed(KEY_TAB) && is_sort_open == false)
    {
        is_sort_open = true;
    }

    if (is_sort_open)
    {
        if (IsKeyPressed(KEY_W) && current_button > 0)
        {
            current_button--;
        }
        else if (IsKeyPressed(KEY_S) && current_button < 2)
        {
            current_button++;
        }
    }

}
// gets used in inventory_ui.cpp to make sure it only gets drawn when inventory is open
void character_player::draw_sort_buttons()
{
    if (is_sort_open)
    {
        DrawTexturePro(sort_buttons,
                       {0, 0, (float)sort_buttons.width, (float)sort_buttons.height},
                       {sort_base_position},
                       {0, 0}, 0, WHITE);

        DrawTexturePro(sort_select,
                       {0, 0, (float)sort_select.width, (float)sort_select.height},
                       {sort_select_position[current_button]},
                       {0, 0}, 0, WHITE);
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

bool character_player::get_sort_open() { return is_sort_open; }

