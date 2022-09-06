#include "inventory_ui.h"


inventory_ui::inventory_ui()
{
    this->backpack = LoadTexture("assets/graphics/gui/backpack.png");
    this->inventory_base = LoadTexture("assets/graphics/gui/inventory_new.png");
    this->inventory_selection = LoadTexture("assets/graphics/gui/selection.png");
    this->inventory_infos = LoadTexture("assets/graphics/gui/infos.png");

    this->ui_infos_position.x = 195; // GetScreenWidth()/2 - this->inventory_infos.width/2;
    this->ui_infos_position.y = GetScreenHeight() / 2 - this->inventory_infos.height - 50;

    this->tutorial_base = LoadTexture("assets/graphics/gui/tutorial.png");

    this->tileset = LoadTexture("assets/map/tileset.png");

    this->set_slots();

}

void inventory_ui::update()
{

    navigate_inventory();

    if (IsKeyPressed(KEY_ENTER))
    {
        is_tutorial = false;
    }

}

void inventory_ui::draw()
{
    // draw a little backpack in the corner of the screen
    // gui_isOpen determines which on the backpack sheet will be drawn and therefore if the icon seems open or not
    DrawTexturePro(this->backpack,
                   {(float)gui_isOpen * 16, 0, 16, 16},
                   {(float)GetScreenWidth() - backpack.width/2*gui_scale_factor, (float)GetScreenHeight() - backpack.width/2*gui_scale_factor, 16*this->gui_scale_factor, 16 * this->gui_scale_factor},
                   {16*2, 16*2}, 0, WHITE);

    // draw the inventory itself if it is open
    if (this->gui_isOpen == true)
    {
        // draw the base
        DrawTexturePro(this->inventory_base,
                       {0, 0, (float)this->inventory_base.width, (float)this->inventory_base.height},
                       {this->inventory_position},
                       {0, 0}, 0, WHITE);

        // draw the selection
        DrawTexturePro(this->inventory_selection,
                       {0, 0, (float)this->inventory_selection.width, (float)this->inventory_selection.height},
                       {this->ui_slots[gui_current_slot].x, this->ui_slots[gui_current_slot].y, this->inventory_selection.width * gui_scale_factor, this->inventory_selection.height * this->gui_scale_factor},
                       {0, 0} ,0, WHITE);

        // draw items within the inventory
        this->draw_items();

        // draw total weight info
        DrawText(("Weight: " + std::to_string(player->get_total_weight())).c_str(), ui_weight_position[0].x, ui_weight_position[0].y, 25, GetColor(0xfb5a5aff));
        DrawText(("Strength: " + std::to_string(player->get_total_strength())).c_str(), ui_weight_position[1].x, ui_weight_position[0].y +  30, 25, GetColor(0xfb5a5aff));
    }

    // draw the info panel if you want
    if (gui_isInfo == true && player->get_sort_open() == false)
    {
        DrawTexturePro(this->inventory_infos,
                       {0, 0, (float)this->inventory_infos.width, (float)this->inventory_infos.height},
                       {(float)GetScreenWidth()/2 - this->inventory_base.width/2*this->gui_scale_factor, (float)GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor, (float)this->inventory_base.width * this->gui_scale_factor, (float)this->inventory_base.height * this->gui_scale_factor},
                       {0, 0} ,0, WHITE);


        this->draw_info();
    }

    if (is_tutorial == true)
    {
        draw_tutorial();
    }
}

void inventory_ui::draw_items()
{
    // go through all slots and draw every single item slot
    for (int i = 0; i < 16; i++)
    {
        this->draw_current_slot(i);
    }
}

void inventory_ui::draw_current_slot(int i)
{
    // draw every occupied slot
    if (this->player->get_current_slot() > i)
    {
        DrawTexturePro(player->get_texture(i),
                       {0, 0, 16, 16},
                       {this->ui_slots[i]},
                       {0, 0}, 0, WHITE);
    }
    // only draw dagger in weapon slot if there is a dagger in it
    if (this->player->get_weapons_occupied() == true) //
    {
        DrawTexturePro(this->player->get_texture(10),
                       {0, 0, 16, 16},
                       {this->ui_slots[10].x, this->ui_slots[10].y, 16 * gui_scale_factor, 16 * gui_scale_factor},
                       {0, 0}, 0, WHITE);
    }
    // only draw ring in ring slot if there is a ring in it
    if (this->player->get_rings_occupied() == true)
    {
        DrawTexturePro(this->player->get_texture(11),
                       {0, 0, 16, 16},
                       {this->ui_slots[11].x, this->ui_slots[11].y, 16 * gui_scale_factor, 16 * gui_scale_factor},
                       {0, 0}, 0, WHITE);
    }

    // only draw armor if slot is occupied
    if (this->player->get_armor_occupied() == true)
    {
        DrawTexturePro(this->player->get_texture(12),
                       {0, 0, 16, 16},
                       {this->ui_slots[12].x, this->ui_slots[12].y, 16 * gui_scale_factor, 16 * gui_scale_factor},
                       {0, 0}, 0, WHITE);
    }
}

void inventory_ui::draw_info()
{
    // draw info for current normal slot if occupied
    if (gui_current_slot <= player->get_current_slot()-1)
    {
        // print info accessing the container item
        DrawText(("Slot: " + std::to_string(this->gui_current_slot)).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40, 30, WHITE);
        DrawText(("Name: " + player->get_item_name(gui_current_slot)).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40 * 2, 30, WHITE);
        DrawText(("Weight: " + std::to_string(player->get_item_weight(gui_current_slot))).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40 * 3, 30, WHITE);
        DrawText(("Value: " + std::to_string(player->get_item_value(gui_current_slot))).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40 * 4, 30, WHITE);
        DrawText(("Description: " + (player->get_item_description(gui_current_slot))).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40 * 5, 30, WHITE);
    }
    // draw info for weapon if special slot selected and occupied
    if (player->get_weapons_occupied() == true && this->gui_current_slot == this->special_slot_weapons)
    {
        DrawText(("Slot: " + std::to_string(this->special_slot_weapons)).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40, 30, WHITE);
        DrawText(("Name: " + player->get_item_name(10)).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40 * 2, 30, WHITE);
        DrawText(("Weight: " + std::to_string(player->get_item_weight(special_slot_weapons))).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40 * 3, 30, WHITE);
        DrawText(("Value: " + std::to_string(player->get_item_value(gui_current_slot))).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40 * 4, 30, WHITE);
        DrawText(("Description: " + player->get_item_description(gui_current_slot)).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40 * 5, 30, WHITE);

    }
    // draw info for ring if special slot selected and occupied
    if (player->get_rings_occupied() == true && this->gui_current_slot == this->special_slot_rings) {
        DrawText(("Slot: " + std::to_string(this->special_slot_rings)).c_str(), this->ui_infos_position.x,
                 this->ui_infos_position.y + 40, 30, WHITE);
        DrawText(("Name: " + player->get_item_name(special_slot_rings)).c_str(), this->ui_infos_position.x,
                 this->ui_infos_position.y + 40 * 2, 30, WHITE);
        DrawText(("Weight: " + std::to_string(player->get_item_weight(special_slot_rings))).c_str(),
                 this->ui_infos_position.x, this->ui_infos_position.y + 40 * 3, 30, WHITE);
        DrawText(("Value: " + std::to_string(player->get_item_value(special_slot_rings))).c_str(),
                 this->ui_infos_position.x, this->ui_infos_position.y + 40 * 4, 30, WHITE);
        DrawText(("Description: " + player->get_item_description(special_slot_rings)).c_str(),
                 this->ui_infos_position.x, this->ui_infos_position.y + 40 * 5, 30, WHITE);

    }
    if (player->get_armor_occupied() == true && this->gui_current_slot == this->special_slot_armor)
    {
        DrawText(("Slot: " + std::to_string(this->special_slot_armor)).c_str(), this->ui_infos_position.x,
                 this->ui_infos_position.y + 40, 30, WHITE);
        DrawText(("Name: " + player->get_item_name(special_slot_armor)).c_str(), this->ui_infos_position.x,
                 this->ui_infos_position.y + 40 * 2, 30, WHITE);
        DrawText(("Weight: " + std::to_string(player->get_item_weight(special_slot_armor))).c_str(),
                 this->ui_infos_position.x, this->ui_infos_position.y + 40 * 3, 30, WHITE);
        DrawText(("Value: " + std::to_string(player->get_item_value(special_slot_armor))).c_str(),
                 this->ui_infos_position.x, this->ui_infos_position.y + 40 * 4, 30, WHITE);
        DrawText(("Description: " + player->get_item_description(special_slot_armor)).c_str(),
                 this->ui_infos_position.x, this->ui_infos_position.y + 40 * 5, 30, WHITE);
    }
    // draw no info since not occupied
    else
    {
        DrawText(("Slot: " + std::to_string(this->gui_current_slot)).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40, 30, WHITE);
    }
}

bool inventory_ui::isBackpackOpen() { return gui_isOpen; }

bool inventory_ui::isInfoOpen() { return gui_isInfo; }

// assign all the ui_slots coordinates relatively to inventory base
// they get assigned in .cpp instead of .h because they are dependend on the texture width
void inventory_ui::set_slots()
{
    // base
    this->inventory_position = {(float)GetScreenWidth()/2 - this->inventory_base.width/2*this->gui_scale_factor, (float)GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor, (float)this->inventory_base.width * this->gui_scale_factor, (float)this->inventory_base.height * this->gui_scale_factor};

    // first row 0 - 4
    this->ui_slots[0] = {(float)inventory_position.x + 12*gui_scale_factor, (float)inventory_position.y + 13*gui_scale_factor, (float)16 * gui_scale_factor, (float)16 * gui_scale_factor};
    this->ui_slots[1] = {(float)this->ui_slots[0].x + this->slot_offset, (float)this->ui_slots[0].y, this->ui_slots->width, this->ui_slots->height};
    this->ui_slots[2] = {(float)this->ui_slots[1].x + this->slot_offset, (float)this->ui_slots[1].y, this->ui_slots->width, this->ui_slots->height};
    this->ui_slots[3] = {(float)this->ui_slots[2].x + this->slot_offset, (float)this->ui_slots[2].y, this->ui_slots->width, this->ui_slots->height};
    this->ui_slots[4] = {(float)this->ui_slots[3].x + this->slot_offset, (float)this->ui_slots[3].y, this->ui_slots->width, this->ui_slots->height};

    // second row 5 - 9
    this->ui_slots[5] = {(float)this->ui_slots[0].x, (float)this->ui_slots[0].y + this->slot_offset, this->ui_slots->width, this->ui_slots->height};
    this->ui_slots[6] = {(float)this->ui_slots[5].x + this->slot_offset, (float)this->ui_slots[5].y, this->ui_slots->width, this->ui_slots->height};
    this->ui_slots[7] = {(float)this->ui_slots[6].x + this->slot_offset, (float)this->ui_slots[6].y, this->ui_slots->width, this->ui_slots->height};
    this->ui_slots[8] = {(float)this->ui_slots[7].x + this->slot_offset, (float)this->ui_slots[7].y, this->ui_slots->width, this->ui_slots->height};
    this->ui_slots[9] = {(float)this->ui_slots[8].x + this->slot_offset, (float)this->ui_slots[8].y, this->ui_slots->width, this->ui_slots->height};

    // special slots
    this->ui_slots[special_slot_weapons] = {(float)this->ui_slots[0].x, (float)this->ui_slots[5].y + 23 * gui_scale_factor};
    this->ui_slots[special_slot_rings] = {(float)this->ui_slots[special_slot_weapons].x + this->slot_offset, (float)this->ui_slots[special_slot_weapons].y};
    this->ui_slots[special_slot_armor] = {(float)this->ui_slots[special_slot_rings].x + this->slot_offset, (float)this->ui_slots[special_slot_weapons].y};

    this->ui_weight_position[0] = { ui_slots[12].x + 23*gui_scale_factor, ui_slots[12].y+3*gui_scale_factor };
    this->ui_weight_position[1] = {ui_weight_position[0].x, ui_weight_position[0].y + 30};
}

void inventory_ui::navigate_inventory()
{

    // navigate in the inventory
    if (gui_isOpen == true && gui_isInfo == false)
    {
        if (IsKeyPressed(KEY_D) && gui_current_slot < 12)
        {
            gui_current_slot++;
        }
        else if (IsKeyPressed(KEY_A) && gui_current_slot > 0)
        {
            gui_current_slot--;
        }
        else if (IsKeyPressed(KEY_TAB))
        {
            gui_current_slot = special_slot_weapons;
        }
    }


    // when i pressed change inventory state
    if(IsKeyPressed(KEY_I) && this->gui_isOpen == true && this->gui_isInfo == false)
    {
        this->gui_isOpen = false;
    }

    else if (IsKeyPressed(KEY_I) && this->gui_isOpen == false)
    {
        this->gui_isOpen = true;
    }

    // if inventory is open and space is pressed open info box
    if (IsKeyPressed(KEY_SPACE) && this->gui_isOpen == true && this->gui_isInfo == false)
    {
        this->gui_isInfo = true;
    }
    else if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_I) && this->gui_isInfo == true)
    {
        this->gui_isInfo = false;
    }
}

void inventory_ui::draw_tutorial()
{
    DrawTexturePro(this->tutorial_base,
                   {0, 0, (float)this->tutorial_base.width, (float)this->tutorial_base.height},
                   {(float)GetScreenWidth()/2 - this->tutorial_base.width/2*this->gui_scale_factor, (float)GetScreenHeight() / 2 - this->tutorial_base.height / 2 * this->gui_scale_factor, (float)this->tutorial_base.width * this->gui_scale_factor, (float)this->tutorial_base.height * this->gui_scale_factor},
                   {0, 0} ,0, WHITE);

    DrawText("Move with WASD", ui_infos_position.x, ui_infos_position.y, 30, WHITE);
    DrawText("Open Inventory with I", ui_infos_position.x, ui_infos_position.y + 40, 30, WHITE);
    DrawText("Get Infos with SPACE", ui_infos_position.x, ui_infos_position.y + 80, 30, WHITE);
    DrawText("Add several Items with M", ui_infos_position.x, ui_infos_position.y + 120, 30, WHITE);
    DrawText("Sort Items with TAB", ui_infos_position.x, ui_infos_position.y + 160, 30, WHITE);
    DrawText("Erase GUI temporary with E", ui_infos_position.x, ui_infos_position.y + 200, 30, WHITE);

    DrawText("Close Tutorial with ENTER", ui_infos_position.x, ui_infos_position.y + 280, 30, WHITE);
}