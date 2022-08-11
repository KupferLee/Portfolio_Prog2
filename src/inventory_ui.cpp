//
// Created by Lee on 06.08.2022.
//

#include "inventory_ui.h"


inventory_ui::inventory_ui()
{
    this->backpack = LoadTexture("assets/graphics/gui/backpack.png");
    this->inventory_base = LoadTexture("assets/graphics/gui/inventory.png");
    this->inventory_selection = LoadTexture("assets/graphics/gui/selection.png");
    this->inventory_infos = LoadTexture("assets/graphics/gui/infos.png");

    this->ui_infos_position.x = 195; // GetScreenWidth()/2 - this->inventory_infos.width/2;
    this->ui_infos_position.y = GetScreenHeight() / 2 - this->inventory_infos.height - 50;

    this->tileset = LoadTexture("assets/map/tileset.png");

    this->set_slots();



}

void inventory_ui::update() {

    // set object items into inventory container
    if (IsKeyPressed(KEY_M))
    {
        this->item_pickUp(this->dagger);
    }
    else if(IsKeyPressed(KEY_N))
    {
        this->item_pickUp(this->chest);
    }
    else if (IsKeyPressed(KEY_B))
    {
        for (int i; i <= this->container_current_slot-1; i++)
        {
            std::cout << container.getItem(i-1)->getName() << std::endl;
        }
    }


    // navigate in the inventory
    // right
    if (this->gui_isOpen == true && this->gui_isInfo == false && IsKeyPressed(KEY_D) && this->gui_current_slot <= 14) {
        this->gui_current_slot++;
    }
    //left
    if (this->gui_isOpen == true && this->gui_isInfo == false && IsKeyPressed(KEY_A) && this->gui_current_slot >= 1) {
        this->gui_current_slot--;
    }

    // special ui_slots
    // down
    // weapons to rings
    if (this->gui_isOpen == true && this->gui_isInfo == false && this->gui_current_slot == this->gui_special_slot_weapons &&
        IsKeyPressed(KEY_S)) {
        this->gui_current_slot = this->gui_special_slot_rings;
    }
    // rings to x
    else if (this->gui_isOpen == true && this->gui_isInfo == false && this->gui_current_slot == this->gui_special_slot_rings &&
             IsKeyPressed(KEY_S))
    {
        this->gui_current_slot = this->gui_special_slot_x;
    }

    // up
    // x to rings
    if (this->gui_isOpen == true && this->gui_isInfo == false && this->gui_current_slot == this->gui_special_slot_x &&
        IsKeyPressed(KEY_W))
    {
        this->gui_current_slot = this->gui_special_slot_rings;
    }
    // rings to weapons
    else if (this->gui_isOpen == true && this->gui_isInfo == false && this->gui_current_slot == this->gui_special_slot_rings &&
             IsKeyPressed(KEY_W))
    {
        this->gui_current_slot = this->gui_special_slot_weapons;
    }

    // TODO: up and down
    /*
    // up
    this->slots_up();

    // down
    this->slots_down();
    */

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

    // use this to determine which item to get?
    switch (gui_current_slot)
    {
        case 0:
            break;
        case 1:
            break;
    }
}

void inventory_ui::draw()
{
    // draw a little backpack in the corner of the screen
    // gui_isOpen determines which on the backpack sheet will be drawn and therefore if the icon seems open or not
    DrawTexturePro(this->backpack,
                   {(float)gui_isOpen * 16, 0, 16, 16},
                   {(float)40, (float)GetScreenHeight() - 80, 16*this->gui_scale_factor, 16 * this->gui_scale_factor},
                   {16*2, 16*2}, 0, WHITE);

    // draw the inventory itself if it is open
    if (this->gui_isOpen == true)
    {
        // draw the base
        DrawTexturePro(this->inventory_base,
                       {0, 0, (float)this->inventory_base.width, (float)this->inventory_base.height},
                       {(float)GetScreenWidth()/2 - this->inventory_base.width/2*this->gui_scale_factor, (float)GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor, (float)this->inventory_base.width * this->gui_scale_factor, (float)this->inventory_base.height * this->gui_scale_factor},
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



        this->draw_text();
    }

}

void inventory_ui::draw_items()
{
    // go through all slots and draw every single item slot
    // currently slot 1 is always a chest
    for (int i = 0; i < 16; i++)
    {
        this->draw_current_slot(i);
    }
}

void inventory_ui::draw_current_slot(int i)
{
    if (this->container_current_slot > i)
    {
        DrawTexturePro(this->tileset,
                       {(float)this->container.getItem(i)->getID()*16, 0, 16, 16},
                       {this->ui_slots[i].x, this->ui_slots[i].y, 16 * gui_scale_factor, 16 * gui_scale_factor},
                       {0, 0}, 0, WHITE);
    }
}

void inventory_ui::draw_text()
{
    if (gui_current_slot <= container_current_slot)
    {
        // print info accessing the container item
        DrawText(("Name: " + container.getItem(gui_current_slot-1)->getName()).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40, 30, WHITE);
        DrawText(("Weight: " + std::to_string(container.getItem(gui_current_slot-1)->getWeight())).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40 * 2, 30, WHITE);
        DrawText(("Value: " + std::to_string(container.getItem(gui_current_slot-1)->getValue())).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40 * 3, 30, WHITE);
        DrawText(("Description: " + container.getItem(gui_current_slot-1)->getDescription()).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40 * 4, 30, WHITE);
    }
}

void inventory_ui::item_pickUp(item_base* item)
{
    container.setItem(item, this->container_current_slot);

    this->container_current_slot++;

}

void inventory_ui::item_drop() {}

bool inventory_ui::isBackpackOpen() { return gui_isOpen; }

bool inventory_ui::isInfoOpen() { return gui_isInfo; }

// assign all the ui_slots coordinates relatively to inventory base
void inventory_ui::set_slots() {

    // first row
    this->ui_slots[0].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor;
    this->ui_slots[0].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor;

    this->ui_slots[1].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 2;
    this->ui_slots[1].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor;

    this->ui_slots[2].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 4;
    this->ui_slots[2].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor;

    this->ui_slots[gui_special_slot_weapons].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 6;
    this->ui_slots[gui_special_slot_weapons].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor;

    // second row
    this->ui_slots[4].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor;
    this->ui_slots[4].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor;

    this->ui_slots[5].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 3;
    this->ui_slots[5].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor;

    //third row
    this->ui_slots[6].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor;
    this->ui_slots[6].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 2;

    this->ui_slots[7].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 2;
    this->ui_slots[7].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 2;

    this->ui_slots[8].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 4;
    this->ui_slots[8].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 2;

    this->ui_slots[gui_special_slot_rings].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 6;
    this->ui_slots[gui_special_slot_rings].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 2;

    // fourth row
    this->ui_slots[10].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor;
    this->ui_slots[10].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 3;

    this->ui_slots[11].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 3;
    this->ui_slots[11].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 3;

    // fifth row
    this->ui_slots[12].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * this->gui_scale_factor;
    this->ui_slots[12].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 4;

    this->ui_slots[13].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 2;
    this->ui_slots[13].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 4;

    this->ui_slots[14].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 4;
    this->ui_slots[14].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 4;
    // special slot idk yet
    this->ui_slots[15].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 6;
    this->ui_slots[15].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 4;
}

void inventory_ui::slots_up()
{
    if (this->gui_isOpen == true && IsKeyPressed(KEY_W))
    {
        if (this->gui_current_slot == 5)
        {
            this->gui_current_slot = 2;
        }
        else if (this->gui_current_slot == 6)
        {
            this->gui_current_slot = 3;
        }
        else if (this->gui_current_slot == 7 || this->gui_current_slot == 8)
        {
            this->gui_current_slot = 5;
        }
        else if (this->gui_current_slot == 9)
        {
            this->gui_current_slot = 6;
        }
        else if (this->gui_current_slot == 11)
        {
            this->gui_current_slot = 8;
        }
        else if (this->gui_current_slot == 12)
        {
            this->gui_current_slot = 9;
        }
        else if (this->gui_current_slot == 13 || this->gui_current_slot == 14)
        {
            this->gui_current_slot = 11;
        }
        else if (this->gui_current_slot == 15)
        {
            this->gui_current_slot = 12;
        }
        else if (this->gui_current_slot == this->gui_special_slot_x)
        {
            this->gui_current_slot = this->gui_special_slot_rings;
        }
        else if (this->gui_current_slot == this->gui_special_slot_rings)
        {
            this->gui_current_slot = this->gui_special_slot_weapons;
        }
    }
}

void inventory_ui::slots_down()
{
    if(this->gui_current_slot == 1 || this->gui_current_slot == 2)
    {
        this->gui_current_slot = 5;
    }
    else if (this->gui_current_slot == 3)
    {
        this->gui_current_slot = 6;
    }
    else if (this->gui_current_slot == 5)
    {
        this->gui_current_slot = 7;
    }
    else if (this->gui_current_slot == 6)
    {
        this->gui_current_slot = 8;
    }
    else if (this->gui_current_slot == 7 || this->gui_current_slot == 8)
    {
        this->gui_current_slot = 11;
    }
    else if (this->gui_current_slot == 9)
    {
        this->gui_current_slot = 12;
    }
    else if (this->gui_current_slot == 11)
    {
        this->gui_current_slot = 13;
    }
    else if (this->gui_current_slot == 12)
    {
        this->gui_current_slot = 15;
    }
}