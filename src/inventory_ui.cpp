#include "inventory_ui.h"


inventory_ui::inventory_ui()
{
    this->backpack = LoadTexture("assets/graphics/gui/backpack.png");
    this->inventory_base = LoadTexture("assets/graphics/gui/inventory_new.png");
    this->inventory_selection = LoadTexture("assets/graphics/gui/selection.png");
    this->inventory_infos = LoadTexture("assets/graphics/gui/infos.png");
    this->tutorial_base = LoadTexture("assets/graphics/gui/tutorial.png");

    this->Set_Slots();

}

void inventory_ui::Update()
{
    if (IsKeyPressed(KEY_ENTER))
    {
        is_tutorial = false;
    }

    if (is_tutorial == false)
    {
        Navigate_Inventory();

        // change position of backpack
        if (IsKeyPressed(KEY_E))
        {
            if (backpack_slot == 0)
            {
                backpack_slot = 1;
            }
            else if (backpack_slot == 1)
            {
                backpack_slot = 0;
            }
        }
    }


}

void inventory_ui::Draw()
{
    // draw a little backpack in the corner of the screen
    // is_open determines which on the backpack sheet will be drawn and therefore if the icon seems open or not
    DrawTexturePro(this->backpack,
                   {(float)is_open * 16, 0, 16, 16},
                   {this->backpack_position[backpack_slot]},
                   {16*2, 16*2}, 0, WHITE);

    // draw the inventory itself if it is open
    if (this->is_open == true)
    {
        // draw the base
        DrawTexturePro(this->inventory_base,
                       {0, 0, (float)this->inventory_base.width, (float)this->inventory_base.height},
                       {this->inventory_position},
                       {0, 0}, 0, WHITE);

        // draw the selection
        DrawTexturePro(this->inventory_selection,
                       {0, 0, (float)this->inventory_selection.width, (float)this->inventory_selection.height},
                       {this->slot_position[current_slot].x, this->slot_position[current_slot].y, this->inventory_selection.width * scale_factor, this->inventory_selection.height * this->scale_factor},
                       {0, 0} ,0, WHITE);

        // draw items within the inventory
        this->Draw_Items();

        // draw total weight info
        DrawText(("Weight: " + std::to_string(Player->Get_Total_Weight())).c_str(), weight_position[0].x, weight_position[0].y, 25, GetColor(0xfb5a5aff));
        DrawText(("Strength: " + std::to_string(Player->Get_Total_Strength())).c_str(), weight_position[1].x, weight_position[0].y + 30, 25, GetColor(0xfb5a5aff));

        Player->Draw_Sort_Buttons();
    }

    // draw the info panel if you want
    if (is_info == true && Player->Get_Sort_Open() == false)
    {
        DrawTexturePro(this->inventory_infos,
                       {0, 0, (float)this->inventory_infos.width, (float)this->inventory_infos.height},
                       {(float)GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor, (float)GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->scale_factor, (float)this->inventory_base.width * this->scale_factor, (float)this->inventory_base.height * this->scale_factor},
                       {0, 0} ,0, WHITE);


        this->Draw_Info();
    }

    if (is_tutorial == true)
    {
        Draw_Tutorial();
    }
}

void inventory_ui::Draw_Items()
{
    // go through all slots and draw every single item slot
    for (int i = 0; i < 16; i++)
    {
        this->Draw_Current_Slot(i);
    }
}

void inventory_ui::Draw_Current_Slot(int i)
{
    // draw every occupied slot
    if (this->Player->Get_Current_Slot() > i)
    {
        DrawTexturePro(Player->Get_Item_Texture(i),
                       {0, 0, 16, 16},
                       {this->slot_position[i]},
                       {0, 0}, 0, WHITE);
    }
    // only draw Dagger in weapon slot if there is a Dagger in it
    if (this->Player->Get_Weapons_Occupied() == true) //
    {
        DrawTexturePro(this->Player->Get_Item_Texture(10),
                       {0, 0, 16, 16},
                       {this->slot_position[10].x, this->slot_position[10].y, 16 * scale_factor, 16 * scale_factor},
                       {0, 0}, 0, WHITE);
    }
    // only draw ring in ring slot if there is a ring in it
    if (this->Player->Get_Rings_Occupied() == true)
    {
        DrawTexturePro(this->Player->Get_Item_Texture(11),
                       {0, 0, 16, 16},
                       {this->slot_position[11].x, this->slot_position[11].y, 16 * scale_factor, 16 * scale_factor},
                       {0, 0}, 0, WHITE);
    }

    // only draw Armor if slot is occupied
    if (this->Player->Get_Armor_Occupied() == true)
    {
        DrawTexturePro(this->Player->Get_Item_Texture(12),
                       {0, 0, 16, 16},
                       {this->slot_position[12].x, this->slot_position[12].y, 16 * scale_factor, 16 * scale_factor},
                       {0, 0}, 0, WHITE);
    }
}

void inventory_ui::Draw_Info()
{
    // draw info for current normal slot if occupied
    if (current_slot <= Player->Get_Current_Slot() - 1)
    {
        // print info accessing the Inventory item
        DrawText(("Slot: " + std::to_string(this->current_slot)).c_str(), this->infos_position.x, this->infos_position.y + 40, 30, WHITE);
        DrawText(("Name: " + Player->Get_Item_Name(current_slot)).c_str(), this->infos_position.x, this->infos_position.y + 40 * 2, 30, WHITE);
        DrawText(("Weight: " + std::to_string(Player->Get_Item_Weight(current_slot))).c_str(), this->infos_position.x, this->infos_position.y + 40 * 3, 30, WHITE);
        DrawText(("Value: " + std::to_string(Player->Get_Item_Value(current_slot))).c_str(), this->infos_position.x, this->infos_position.y + 40 * 4, 30, WHITE);
        DrawText(("Description: " + (Player->Get_Item_Description(current_slot))).c_str(), this->infos_position.x, this->infos_position.y + 40 * 5, 30, WHITE);
    }
    // draw info for weapon if special slot selected and occupied
    if (Player->Get_Weapons_Occupied() == true && this->current_slot == this->special_slot_weapons)
    {
        DrawText(("Slot: " + std::to_string(this->special_slot_weapons)).c_str(), this->infos_position.x, this->infos_position.y + 40, 30, WHITE);
        DrawText(("Name: " + Player->Get_Item_Name(10)).c_str(), this->infos_position.x, this->infos_position.y + 40 * 2, 30, WHITE);
        DrawText(("Weight: " + std::to_string(Player->Get_Item_Weight(special_slot_weapons))).c_str(), this->infos_position.x, this->infos_position.y + 40 * 3, 30, WHITE);
        DrawText(("Value: " + std::to_string(Player->Get_Item_Value(current_slot))).c_str(), this->infos_position.x, this->infos_position.y + 40 * 4, 30, WHITE);
        DrawText(("Description: " + Player->Get_Item_Description(current_slot)).c_str(), this->infos_position.x, this->infos_position.y + 40 * 5, 30, WHITE);

    }
    // draw info for ring if special slot selected and occupied
    if (Player->Get_Rings_Occupied() == true && this->current_slot == this->special_slot_rings) {
        DrawText(("Slot: " + std::to_string(this->special_slot_rings)).c_str(), this->infos_position.x,
                 this->infos_position.y + 40, 30, WHITE);
        DrawText(("Name: " + Player->Get_Item_Name(special_slot_rings)).c_str(), this->infos_position.x,
                 this->infos_position.y + 40 * 2, 30, WHITE);
        DrawText(("Weight: " + std::to_string(Player->Get_Item_Weight(special_slot_rings))).c_str(),
                 this->infos_position.x, this->infos_position.y + 40 * 3, 30, WHITE);
        DrawText(("Value: " + std::to_string(Player->Get_Item_Value(special_slot_rings))).c_str(),
                 this->infos_position.x, this->infos_position.y + 40 * 4, 30, WHITE);
        DrawText(("Description: " + Player->Get_Item_Description(special_slot_rings)).c_str(),
                 this->infos_position.x, this->infos_position.y + 40 * 5, 30, WHITE);

    }
    if (Player->Get_Armor_Occupied() == true && this->current_slot == this->special_slot_armor)
    {
        DrawText(("Slot: " + std::to_string(this->special_slot_armor)).c_str(), this->infos_position.x,
                 this->infos_position.y + 40, 30, WHITE);
        DrawText(("Name: " + Player->Get_Item_Name(special_slot_armor)).c_str(), this->infos_position.x,
                 this->infos_position.y + 40 * 2, 30, WHITE);
        DrawText(("Weight: " + std::to_string(Player->Get_Item_Weight(special_slot_armor))).c_str(),
                 this->infos_position.x, this->infos_position.y + 40 * 3, 30, WHITE);
        DrawText(("Value: " + std::to_string(Player->Get_Item_Value(special_slot_armor))).c_str(),
                 this->infos_position.x, this->infos_position.y + 40 * 4, 30, WHITE);
        DrawText(("Description: " + Player->Get_Item_Description(special_slot_armor)).c_str(),
                 this->infos_position.x, this->infos_position.y + 40 * 5, 30, WHITE);
    }
    // draw no info since not occupied
    else
    {
        DrawText(("Slot: " + std::to_string(this->current_slot)).c_str(), this->infos_position.x, this->infos_position.y + 40, 30, WHITE);
    }
}

bool inventory_ui::Is_Backpack_Open() { return is_open; }

// assign all the slot_position coordinates relatively to inventory base
// they get assigned in .cpp instead of .h because they are dependend on the texture width
void inventory_ui::Set_Slots()
{
    // base
    this->inventory_position = {(float)GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor, (float)GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->scale_factor, (float)this->inventory_base.width * this->scale_factor, (float)this->inventory_base.height * this->scale_factor};

    this->backpack_position[0] = {(float)GetScreenWidth() - backpack.width / 2 * scale_factor, (float)GetScreenHeight() - backpack.width / 2 * scale_factor, 16 * this->scale_factor, 16 * this->scale_factor};
    this->backpack_position[1] = {8 * scale_factor, (float)GetScreenHeight() - backpack.width / 2 * scale_factor, 16 * this->scale_factor, 16 * this->scale_factor};

    // first row 0 - 4
    this->slot_position[0] = {(float)inventory_position.x + 12 * scale_factor, (float)inventory_position.y + 13 * scale_factor, (float)16 * scale_factor, (float)16 * scale_factor};
    this->slot_position[1] = {(float)this->slot_position[0].x + this->slot_offset, (float)this->slot_position[0].y, this->slot_position->width, this->slot_position->height};
    this->slot_position[2] = {(float)this->slot_position[1].x + this->slot_offset, (float)this->slot_position[1].y, this->slot_position->width, this->slot_position->height};
    this->slot_position[3] = {(float)this->slot_position[2].x + this->slot_offset, (float)this->slot_position[2].y, this->slot_position->width, this->slot_position->height};
    this->slot_position[4] = {(float)this->slot_position[3].x + this->slot_offset, (float)this->slot_position[3].y, this->slot_position->width, this->slot_position->height};

    // second row 5 - 9
    this->slot_position[5] = {(float)this->slot_position[0].x, (float)this->slot_position[0].y + this->slot_offset, this->slot_position->width, this->slot_position->height};
    this->slot_position[6] = {(float)this->slot_position[5].x + this->slot_offset, (float)this->slot_position[5].y, this->slot_position->width, this->slot_position->height};
    this->slot_position[7] = {(float)this->slot_position[6].x + this->slot_offset, (float)this->slot_position[6].y, this->slot_position->width, this->slot_position->height};
    this->slot_position[8] = {(float)this->slot_position[7].x + this->slot_offset, (float)this->slot_position[7].y, this->slot_position->width, this->slot_position->height};
    this->slot_position[9] = {(float)this->slot_position[8].x + this->slot_offset, (float)this->slot_position[8].y, this->slot_position->width, this->slot_position->height};

    // special slots
    this->slot_position[special_slot_weapons] = {(float)this->slot_position[0].x, (float)this->slot_position[5].y + 23 * scale_factor};
    this->slot_position[special_slot_rings] = {(float)this->slot_position[special_slot_weapons].x + this->slot_offset, (float)this->slot_position[special_slot_weapons].y};
    this->slot_position[special_slot_armor] = {(float)this->slot_position[special_slot_rings].x + this->slot_offset, (float)this->slot_position[special_slot_weapons].y};

    this->weight_position[0] = {slot_position[12].x + 23 * scale_factor, slot_position[12].y + 3 * scale_factor };
    this->weight_position[1] = {weight_position[0].x, weight_position[0].y + 30};

    // info tutorial
    this->infos_position = {195, (float)GetScreenHeight() / 2 - this->inventory_infos.height - 50};
}

void inventory_ui::Navigate_Inventory()
{

    // navigate in the inventory
    if (is_open == true && is_info == false && Player->Get_Sort_Open() == false)
    {
        if (IsKeyPressed(KEY_D) && current_slot < 12 && current_slot != 4 && current_slot != 9 && current_slot != 12)
        {
            current_slot++;
        }
        else if (IsKeyPressed(KEY_A) && current_slot > 0 && current_slot != 5 && current_slot != 10 && current_slot != 0)
        {
            current_slot--;
        }

        else if (IsKeyPressed(KEY_S) && current_slot <= 4)
        {
            current_slot += 5;
        }
        else if (IsKeyPressed(KEY_W) && current_slot > 4)
        {
            current_slot -= 5;
        }

        else if (IsKeyPressed(KEY_S) && current_slot == 5)
        {
            current_slot = 10;
        }
        else if (IsKeyPressed(KEY_S) && current_slot == 6)
        {
            current_slot = 11;
        }
        else if (IsKeyPressed(KEY_S) && current_slot == 7)
        {
            current_slot = 12;
        }

        else if (IsKeyPressed(KEY_S) && current_slot == 10)
        {
            current_slot = 5;
        }
        else if (IsKeyPressed(KEY_S) && current_slot == 11)
        {
            current_slot = 6;
        }
        else if (IsKeyPressed(KEY_S) && current_slot == 12)
        {
            current_slot = 7;
        }
    }


    // when i pressed change inventory state
    if(IsKeyPressed(KEY_I) && this->is_open == true && this->is_info == false)
    {
        this->is_open = false;
    }

    else if (IsKeyPressed(KEY_I) && this->is_open == false)
    {
        this->is_open = true;
    }

    // if inventory is open and space is pressed open info box
    if (IsKeyPressed(KEY_SPACE) && this->is_open == true && this->is_info == false)
    {
        this->is_info = true;
    }
    else if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_I) && this->is_info == true)
    {
        this->is_info = false;
    }
}

void inventory_ui::Draw_Tutorial()
{
    DrawTexturePro(this->tutorial_base,
                   {0, 0, (float)this->tutorial_base.width, (float)this->tutorial_base.height},
                   {(float)GetScreenWidth()/2 - this->tutorial_base.width/2*this->scale_factor, (float)GetScreenHeight() / 2 - this->tutorial_base.height / 2 * this->scale_factor, (float)this->tutorial_base.width * this->scale_factor, (float)this->tutorial_base.height * this->scale_factor},
                   {0, 0} ,0, WHITE);

    DrawText("Move with WASD", infos_position.x, infos_position.y, 30, WHITE);
    DrawText("Find path with SPACE", infos_position.x, infos_position.y + 40, 30, WHITE);
    DrawText("Open inventory with I", infos_position.x, infos_position.y + 80, 30, WHITE);
    DrawText("Collect item on Map with ENTER", infos_position.x, infos_position.y + 120, 30, WHITE);
    DrawText("Add 3b) items with M, erase with N", infos_position.x, infos_position.y + 160, 30, WHITE);
    DrawText("Sort items with TAB", infos_position.x, infos_position.y + 200, 30, WHITE);
    DrawText("Change backpack position with E", infos_position.x, infos_position.y + 240, 30, WHITE);

    DrawText("Close tutorial with ENTER", infos_position.x, infos_position.y + 300, 30, WHITE);
}