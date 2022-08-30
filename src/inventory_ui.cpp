#include "inventory_ui.h"


inventory_ui::inventory_ui()
{
    this->backpack = LoadTexture("assets/graphics/gui/backpack.png");
    this->inventory_base = LoadTexture("assets/graphics/gui/inventory_new.png");
    this->inventory_selection = LoadTexture("assets/graphics/gui/selection.png");
    this->inventory_infos = LoadTexture("assets/graphics/gui/infos.png");

    this->ui_infos_position.x = 195; // GetScreenWidth()/2 - this->inventory_infos.width/2;
    this->ui_infos_position.y = GetScreenHeight() / 2 - this->inventory_infos.height - 50;

    this->tileset = LoadTexture("assets/map/tileset.png");

    this->set_slots();

}

void inventory_ui::update()
{

    navigate_inventory();

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
    }

    // draw the info panel if you want
    if (gui_isInfo == true)
    {
        DrawTexturePro(this->inventory_infos,
                       {0, 0, (float)this->inventory_infos.width, (float)this->inventory_infos.height},
                       {(float)GetScreenWidth()/2 - this->inventory_base.width/2*this->gui_scale_factor, (float)GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor, (float)this->inventory_base.width * this->gui_scale_factor, (float)this->inventory_base.height * this->gui_scale_factor},
                       {0, 0} ,0, WHITE);


        this->draw_info();
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
        std::cout << "DEBUG: Item drawn" << std::endl;

        DrawTexturePro(player->get_texture(i),
                       {0, 0, 16, 16},
                       {this->ui_slots[i]},
                       {0, 0}, 0, WHITE);
    }
    /*
    // only draw dagger in weapon slot if there is a dagger in it
    if (this->container.getItem(this->gui_special_slot_weapons) == this->dagger)
    {
        DrawTexturePro(this->tileset,
                       {(float)this->container.getItem(this->gui_special_slot_weapons)->getID()*16, 0, 16, 16},
                       {this->ui_slots[this->gui_special_slot_weapons].x, this->ui_slots[this->gui_special_slot_weapons].y, 16 * gui_scale_factor, 16 * gui_scale_factor},
                       {0, 0}, 0, WHITE);
    }
    // only draw ring in ring slot if there is a ring in it
    if (this->container.getItem(this->gui_special_slot_rings) == this->ring)
    {
        DrawTexturePro(this->tileset,
                       {(float)this->container.getItem(this->gui_special_slot_rings)->getID()*16, 0, 16, 16},
                       {this->ui_slots[this->gui_special_slot_rings].x, this->ui_slots[this->gui_special_slot_rings].y, 16 * gui_scale_factor, 16 * gui_scale_factor},
                       {0, 0}, 0, WHITE);
    }
     */
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

    /*
    // draw info for weapon if special slot selected and occupied
    if (this->container.getItem(this->gui_special_slot_weapons) == this->dagger && this->gui_current_slot == this->gui_special_slot_weapons)
    {
        DrawText(("Slot: " + std::to_string(this->gui_special_slot_weapons)).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40, 30, WHITE);
        DrawText(("Name: " + container.getItem(this->gui_special_slot_weapons)->getName()).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40 * 2, 30, WHITE);
        DrawText(("Weight: " + std::to_string(container.getItem(this->gui_special_slot_weapons)->getWeight())).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40 * 3, 30, WHITE);
        DrawText(("Value: " + std::to_string(container.getItem(this->gui_special_slot_weapons)->getValue())).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40 * 4, 30, WHITE);
        DrawText(("Description: " + container.getItem(this->gui_special_slot_weapons)->getDescription()).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40 * 5, 30, WHITE);

    }
    // draw info for ring if special slot selected and occupied
    if (this->container.getItem(this->gui_special_slot_rings) == this->ring && this->gui_current_slot == this->gui_special_slot_rings)
    {
        DrawText(("Slot: " + std::to_string(this->gui_special_slot_rings)).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40, 30, WHITE);
        DrawText(("Name: " + container.getItem(this->gui_special_slot_rings)->getName()).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40 * 2, 30, WHITE);
        DrawText(("Weight: " + std::to_string(container.getItem(this->gui_special_slot_rings)->getWeight())).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40 * 3, 30, WHITE);
        DrawText(("Value: " + std::to_string(container.getItem(this->gui_special_slot_rings)->getValue())).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40 * 4, 30, WHITE);
        DrawText(("Description: " + container.getItem(this->gui_special_slot_rings)->getDescription()).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40 * 5, 30, WHITE);

    }
     */

    // draw no info since not occupied
    else
    {
        DrawText(("Slot: " + std::to_string(this->gui_current_slot)).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40, 30, WHITE);
    }
}

bool inventory_ui::isBackpackOpen() { return gui_isOpen; }

bool inventory_ui::isInfoOpen() { return gui_isInfo; }

// assign all the ui_slots coordinates relatively to inventory base
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
    this->ui_slots[gui_special_slot_weapons] = {(float)this->ui_slots[0].x, (float)this->ui_slots[5].y + 23*gui_scale_factor};
    this->ui_slots[gui_special_slot_rings] = {(float)this->ui_slots[gui_special_slot_weapons].x + this->slot_offset, (float)this->ui_slots[gui_special_slot_weapons].y};
    this->ui_slots[gui_special_slot_x] = {(float)this->ui_slots[gui_special_slot_rings].x + this->slot_offset, (float)this->ui_slots[gui_special_slot_weapons].y};
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
            gui_current_slot = gui_special_slot_weapons;
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