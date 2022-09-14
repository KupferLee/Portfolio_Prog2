//
// Created by Lee on 13.08.2022.
//

#include "character_player.h"

character_player::character_player()
{
    // Player
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

    // collsion
}

void character_player::Update()
{
    Update_Sort_Buttons();

    if (IsKeyPressed(KEY_M))
    {
        Item_Pickup(Crystal);
        Item_Pickup(Golden_Apple);
        Item_Pickup(Potion);
        Item_Pickup(Chest);
        Item_Pickup(Golden_Apple);
        Item_Pickup(Crystal);
        Item_Pickup(Golden_Apple);
        Item_Pickup(Chest);
        Item_Pickup(Potion);
        Item_Pickup(Crystal);

        Item_Pickup(Dagger);
        Item_Pickup(Ring);
        Item_Pickup(Armor);

        Calculate_Weight();
    }
    else if (IsKeyPressed(KEY_N))
    {
        for (int i = 0; i < 10; i++)
        {
            inventory_slot = 0;
            Inventory.setItem(NULL, i);
        }
    }
    else if (is_sort_open == true && IsKeyPressed(KEY_ENTER))
    {
        if (current_button == 0)
        {
            Sort_By_Weight();
        }
        else if (current_button == 1)
        {
            Sort_By_Value();
        }
        else if (current_button == 2)
        {
            Sort_By_Name();
        }

        current_button = 0;
        is_sort_open = false;
    }

    if(Inventory.getItem(11) == Ring)
    {
        this->strength = base_strength + Ring->Get_Strength();
    }
    else
    {
        this->strength = base_strength;
    }

    // disable movement when total weight is more than Player strength
    if (total_weight < strength)
    {
        Movement_Controls();
    }
}

void character_player::Movement_Controls()
{
    // W A S D
    // only able to make step if tile you want to step on is grass
    if (this->can_move == true) //
    {
        // up
        if (IsKeyPressed(KEY_W) && Map->Get_Tile(Get_Position_Z() - 30) == 0)
        {
            // this->position.y = this->position.y - this->movement_speed;
            this->position.y -= 32;
            this->facing_direction = up;
        }
            // left
        else if (IsKeyPressed(KEY_A) && Map->Get_Tile(Get_Position_Z() - 1) == 0)
        {
            // this->position.x = this->position.x - this->movement_speed;
            this->position.x -= 32;
            this->facing_direction = down;
        }
            // down
        else if (IsKeyPressed(KEY_S) && Map->Get_Tile(Get_Position_Z() + 30) == 0)
        {
            // this->position.y = this->position.y + this->movement_speed;
            this->position.y += 32;
            this->facing_direction = down;
        }
            //right
        else if (IsKeyPressed(KEY_D) && Map->Get_Tile(Get_Position_Z()  + 1) == 0)
        {
            // this->position.x = this->position.x + this->movement_speed;
            this->position.x += 32;
            this->facing_direction = down;
        }

        this->hitbox = {position.x - 32, position.y - 32, 32, 32};
    }
}


// Inventory
void character_player::Item_Pickup(item_base* item)
{
    // only fill in the first 10 slots, not the 3 special ones
    if (this->inventory_slot < 10 && item != Dagger && item != Ring && item != Armor)
    {
        Inventory.setItem(item, this->inventory_slot);

        this->inventory_slot++;
    }
    // if pick up weapon and special slot weapon empty fill in special slot
    else if (item == Dagger && Inventory.getItem(10) == NULL)
    {
        Inventory.setItem(item, 10);
        is_weapons_occupied = true;
    }
    // if pick up ring and special slot ring empty fill in special slot
    else if (item == Ring && Inventory.getItem(11) == NULL)
    {
        Inventory.setItem(item, 11);
        is_rings_occupied = true;
    }
    else if (item == Armor && Inventory.getItem(12) == NULL)
    {
        Inventory.setItem(item, 12);
        is_armor_occupied = true;
    }
    else
    {
        std::cout << "ERROR: No item assigned." << std::endl;
    }

}

void character_player::Calculate_Weight()
{
    // first reset total weight
    this->total_weight = 0;

    // count through normal items and add weight
    for (int i = 0; i < inventory_slot; i++)
    {
        this->total_weight = total_weight + Inventory.getItem(i)->Get_Weight();
    }
    // count weapons and rings and Armor special if they are assigned
    if (Inventory.getItem(10) == Dagger)
    {
        this->total_weight = total_weight + Inventory.getItem(10)->Get_Weight();
    }
    if (Inventory.getItem(11) == Ring)
    {
        this->total_weight = total_weight + Inventory.getItem(11)->Get_Weight();
    }
    if (Inventory.getItem(12) == Armor)
    {
        this->total_weight = total_weight + Inventory.getItem(12)->Get_Weight();
    }
}

// sort algorithm
void character_player::Sort_By_Weight()
{
    // go through all set item slots
    for (int i = 0; i < inventory_slot; i++)
    {
        // actual sort algorithm
        for (int i = 0; i < inventory_slot - 1; i++)
        {
            if (Inventory.getItem(i)->Get_Weight() > Inventory.getItem(i + 1)->Get_Weight())
            {
                // set item from i in extra slot
                Inventory.setItem(Inventory.getItem(i), 13);
                // set item from i + 1 in i
                Inventory.setItem(Inventory.getItem(i + 1), i);
                // set item from extra slot in i + 1
                Inventory.setItem(Inventory.getItem(13), i + 1);
            }
        }
    }

    std::cout << "DEBUG: Items are sorted by weight now." << std::endl;
}

void character_player::Sort_By_Value()
{
    for (int i = 0; i < inventory_slot; i++)
    {
        // actual sort algorithm
        for (int i = 0; i < inventory_slot - 1; i++)
        {
            if (Inventory.getItem(i)->Get_Value() < Inventory.getItem(i + 1)->Get_Value())
            {
                // set item from i in extra slot
                Inventory.setItem(Inventory.getItem(i), 13);
                // set item from i + 1 in i
                Inventory.setItem(Inventory.getItem(i + 1), i);
                // set item from extra slot in i + 1
                Inventory.setItem(Inventory.getItem(13), i + 1);
            }
        }
    }

    std::cout << "DEBUG: Items are sorted by value now." << std::endl;
}

void character_player::Sort_By_Name()
{
    // go through all set item slots
    for (int i = 0; i < inventory_slot; i++)
    {
        // actual sort algorithm
        // this currently sorts by value lol
        for (int i = 0; i < inventory_slot - 1; i++)
        {
            if (Inventory.getItem(i)->Get_Name() > Inventory.getItem(i + 1)->Get_Name())
            {
                // set item from i in extra slot
                Inventory.setItem(Inventory.getItem(i), 13);
                // set item from i + 1 in i
                Inventory.setItem(Inventory.getItem(i + 1), i);
                // set item from extra slot in i + 1
                Inventory.setItem(Inventory.getItem(13), i + 1);
            }
        }
    }

    std::cout << "DEBUG: Items are sorted by name now." << std::endl;
}

// sort gui
void character_player::Update_Sort_Buttons()
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
void character_player::Draw_Sort_Buttons()
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
int character_player::Get_Current_Slot() { return this->inventory_slot; }

Texture2D character_player::Get_Texture(int slot) { return Inventory.getItem(slot)->Get_Texture(); }

std::string character_player::Get_Item_Name(int slot) { return Inventory.getItem(slot)->Get_Name(); }

int character_player::Get_Item_Weight(int slot) { return Inventory.getItem(slot)->Get_Weight(); }

int character_player::Get_Item_Value(int slot) { return Inventory.getItem(slot)->Get_Value(); }

std::string character_player::Get_Item_Description(int slot) { return Inventory.getItem(slot)->Get_Description(); }

bool character_player::Get_Weapons_Occupied() { return is_weapons_occupied; }

bool character_player::Get_Rings_Occupied() { return is_rings_occupied; }

bool character_player::Get_Armor_Occupied() { return is_armor_occupied; }

int character_player::Get_Total_Weight() { return total_weight; }

int character_player::Get_Total_Strength() { return this->strength; }

void character_player::Set_Can_Move(bool move) { can_move = move; }

bool character_player::Get_Sort_Open() { return is_sort_open; }



