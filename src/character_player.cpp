//
// Created by Lee on 13.08.2022.
//

#include "character_player.h"

character_player::character_player()
{
    // Player
    this->texture = LoadTexture("assets/graphics/characters/player_32.png");

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

void character_player::Update(bool inventory, bool robot_message)
{
    Update_Sort_Buttons();
    Calculate_Weight();
    Check_Item_Collision();

    // put this here so position isnt fucked up
    Get_Position_X();
    Get_Position_Y();
    Get_Position_Z();

    if (inventory == true)
    {
        Item_Drop();
    }


    if (is_sort_open == true && IsKeyPressed(KEY_ENTER))
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
    if (total_weight <= strength && inventory == false && robot_message == false)
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
            this->position.y -= 32;
            this->facing_direction = up;
        }
            // left
        else if (IsKeyPressed(KEY_A) && Map->Get_Tile(Get_Position_Z() - 1) == 0)
        {
            this->position.x -= 32;
        }
            // down
        else if (IsKeyPressed(KEY_S) && Map->Get_Tile(Get_Position_Z() + 30) == 0)
        {
            this->position.y += 32;
            this->facing_direction = down;
        }
            //right
        else if (IsKeyPressed(KEY_D) && Map->Get_Tile(Get_Position_Z()  + 1) == 0)
        {
            this->position.x += 32;
        }
    }
}


// Inventory
// items get filled into normal slots, equipment gets automatically equipped to special slots
// if the equipment slot is full already the item gets added to a normal slot
void character_player::Item_Pickup(item_base* item)
{
    // only fill in the first 10 slots, not the 3 special ones
    if (this->inventory_slot < 10 && item != Dagger && item != Ring && item != Armor )
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

// drop the last item that was added to your inventory
// if there is already an item on the tile you standing on you cannot drop your item
void character_player::Item_Drop()
{
    if(IsKeyPressed(KEY_BACKSPACE) && Map->Get_Item(current_tile.z) == -1 && inventory_slot > 0)
    {
        if (Inventory.getItem(inventory_slot-1) == Dagger)
        {
            item_id = 4;
        }
        else if (Inventory.getItem(inventory_slot-1) == Chest)
        {
            item_id = 5;
        }
        else if (Inventory.getItem(inventory_slot-1) == Potion)
        {
            item_id = 6;
        }
        else if (Inventory.getItem(inventory_slot-1) == Golden_Apple)
        {
            item_id = 7;
        }
        else if (Inventory.getItem(inventory_slot-1) == Crystal)
        {
            item_id = 8;
        }
        else if (Inventory.getItem(inventory_slot-1) == Ring)
        {
            item_id = 9;
        }
        if (Inventory.getItem(inventory_slot-1) == Armor)
        {
            item_id = 10;
        }

        Map->Set_Item(current_tile.z, item_id);
        inventory_slot = inventory_slot - 1;
    }
    // drop equipment from special slots
    // there is a weird bug still
    else if (IsKeyPressed(KEY_BACKSPACE) && inventory_slot == 0)
    {
        // here is a weird bug with weapons?
        if (is_armor_occupied)
        {
            Map->Set_Item(current_tile.z, 10);
            Inventory.setItem(NULL, 12);
            is_armor_occupied = false;
        }
        else if (is_rings_occupied)
        {
            Map->Set_Item(current_tile.z, 9);
            Inventory.setItem(NULL, 11);
            is_rings_occupied = false;
        }
        else if (is_weapons_occupied)
        {
            Map->Set_Item(current_tile.z, 4);
            Inventory.setItem(NULL, 10);
            is_weapons_occupied = false;
        }
    }
}

void character_player::Check_Item_Collision()
{
    if (IsKeyPressed(KEY_ENTER))
    {
        if (inventory_slot < 10)
        {
            if (Map->Get_Item(current_tile.z) == 5)
            {
                Item_Pickup(Chest);
                Map->Set_Item(current_tile.z, -1);
            }

            if (Map->Get_Item(current_tile.z) == 6)
            {
                Item_Pickup(Potion);
                Map->Set_Item(current_tile.z, -1);
            }

            if (Map->Get_Item(current_tile.z) == 7)
            {
                Item_Pickup(Golden_Apple);
                Map->Set_Item(current_tile.z, -1);
            }

            if (Map->Get_Item(current_tile.z) == 8)
            {
                Item_Pickup(Crystal);
                Map->Set_Item(current_tile.z, -1);
            }
        }

        if (Map->Get_Item(current_tile.z) == 4) //  && is_weapons_occupied == false
        {
            Item_Pickup(Dagger);
            Map->Set_Item(current_tile.z, -1);
        }

        if (Map->Get_Item(current_tile.z) == 9) // && is_rings_occupied == false
        {
            Item_Pickup(Ring);
            Map->Set_Item(current_tile.z, -1);
        }

        if (Map->Get_Item(current_tile.z) == 10) // && is_armor_occupied == false
        {
            Item_Pickup(Armor);
            Map->Set_Item(current_tile.z, -1);
        }
    }



    // add items for testing sort
    if (IsKeyPressed(KEY_M))
    {
        Item_Pickup(Dagger);
        Item_Pickup(Ring);
        Item_Pickup(Armor);

        Item_Pickup(Golden_Apple);
        Item_Pickup(Crystal);
        Item_Pickup(Chest);
        Item_Pickup(Potion);
        Item_Pickup(Golden_Apple);
        Item_Pickup(Crystal);
        Item_Pickup(Chest);
        Item_Pickup(Potion);
    }
    // delete all items
    else if (IsKeyPressed(KEY_N))
    {
        for (int i = 0; i <= 12; i++)
        {
            Inventory.setItem(NULL, i);
        }
        inventory_slot = 0;
        is_armor_occupied = false;
        is_weapons_occupied = false;
        is_rings_occupied = false;
    }
}

void character_player::Robot_Item(int item)
{
    switch (item)
    {
        case 4:
            Item_Pickup(Dagger);
            break;

        case 5:
            Item_Pickup(Chest);
            break;

        case 6:
            Item_Pickup(Potion);
            break;

        case 7:
            Item_Pickup(Golden_Apple);
            break;

        case 8:
            Item_Pickup(Crystal);
            break;

        case 9:
            Item_Pickup(Ring);
            break;

        case 10:
            Item_Pickup(Armor);
            break;
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

// sort algorithms
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

    std::cout << "DEBUG: Items are sorted by weight now, lowest to highest." << std::endl;
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

    std::cout << "DEBUG: Items are sorted by value now, highest to lowest." << std::endl;
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

    std::cout << "DEBUG: Items are sorted by name now, A to Z." << std::endl;
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

void character_player::Set_Starting_Pos() { this->position = {(Map->Get_Start_Pos().x + 1) * 32, (Map->Get_Start_Pos().y + 1) * 32}; }

// return item attributes
int character_player::Get_Current_Slot() { return this->inventory_slot; }

Texture2D character_player::Get_Item_Texture(int slot) { if (Inventory.getItem(slot) != NULL) return Inventory.getItem(slot)->Get_Texture(); }

std::string character_player::Get_Item_Name(int slot) { return Inventory.getItem(slot)->Get_Name(); }

int character_player::Get_Item_Weight(int slot) { return Inventory.getItem(slot)->Get_Weight(); }

int character_player::Get_Item_Value(int slot) { return Inventory.getItem(slot)->Get_Value(); }

std::string character_player::Get_Item_Description(int slot) { return Inventory.getItem(slot)->Get_Description(); }

bool character_player::Get_Weapons_Occupied() { return is_weapons_occupied; }

bool character_player::Get_Rings_Occupied() { return is_rings_occupied; }

bool character_player::Get_Armor_Occupied() { return is_armor_occupied; }

int character_player::Get_Total_Weight() { return total_weight; }

int character_player::Get_Total_Strength() { return this->strength; }

bool character_player::Get_Sort_Open() { return is_sort_open; }



