//
// Created by Lee on 06.08.2022.
//

#include "ui_inventory.h"

ui_inventory::ui_inventory()
{
    this->backpack = LoadTexture("assets/graphics/gui/backpack.png");
    this->inventory_base = LoadTexture("assets/graphics/gui/inventory.png");
    this->inventory_selection = LoadTexture("assets/graphics/gui/selection.png");
    this->inventory_infos = LoadTexture("assets/graphics/gui/infos.png");

    this->infos_position.x = 195; // GetScreenWidth()/2 - this->inventory_infos.width/2;
    this->infos_position.y = GetScreenHeight()/2 - this->inventory_infos.height;

    this->set_slots();

}

void ui_inventory::update()
{
    // navigate in the inventory
    // right
    if (this->isOpen == true && this->isInfo == false && IsKeyPressed(KEY_D) && this->current_slot <= 14)
    {
        this->current_slot++;
    }
    //left
    if (this->isOpen == true && this->isInfo == false && IsKeyPressed(KEY_A) && this->current_slot >= 1)
    {
        this->current_slot--;
    }

    // TODO: up and down
    /*
    // up
    this->slots_up();

    // down
    this->slots_down();
    */

    // when i pressed change inventory state
    if(IsKeyPressed(KEY_I) && this->isOpen == true && this->isInfo == false)
    {
        this->isOpen = false;
    }

    else if (IsKeyPressed(KEY_I) && this->isOpen == false)
    {
        this->isOpen = true;
    }

    // if inventory is open and space is pressed open info box
    if (IsKeyPressed(KEY_SPACE) && this->isOpen == true && this->isInfo == false)
    {
        this->isInfo = true;
    }
    else if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_I) && this->isInfo == true)
    {
        this->isInfo = false;
    }

    // use this to determine which item to get?
    switch (current_slot)
    {
        case 0:
            break;
        case 1:
            break;
    }
}

void ui_inventory::draw()
{
    // draw a little backpack in the corner of the screen
    // isOpen determines which on the backpack sheet will be drawn and therefore if the icon seems open or not
    DrawTexturePro(this->backpack,
                   {(float)isOpen * 16, 0, 16, 16},
                   {(float)40, (float)GetScreenHeight() - 80, 16*this->scale_factor, 16*this->scale_factor},
                   {16*2, 16*2}, 0, WHITE);

    // draw the inventory itself if it is open
    if (this->isOpen == true)
    {
        // draw the base
        DrawTexturePro(this->inventory_base,
                       {0, 0, (float)this->inventory_base.width, (float)this->inventory_base.height},
                       {(float)GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor, (float)GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor, (float)this->inventory_base.width*this->scale_factor, (float)this->inventory_base.height*this->scale_factor},
                       {0, 0}, 0, WHITE);

        // draw the selection
        DrawTexturePro(this->inventory_selection,
                       {0, 0, (float)this->inventory_selection.width, (float)this->inventory_selection.height},
                       {this->slots[current_slot].x, this->slots[current_slot].y, this->inventory_selection.width*scale_factor, this->inventory_selection.height*this->scale_factor},
                       {0, 0} ,0, WHITE);
    }

    // draw the info panel if you want
    if (isInfo == true)
    {
        DrawTexturePro(this->inventory_infos,
                       {0, 0, (float)this->inventory_infos.width, (float)this->inventory_infos.height},
                       {(float)GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor, (float)GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor, (float)this->inventory_base.width*this->scale_factor, (float)this->inventory_base.height*this->scale_factor},
                       {0, 0} ,0, WHITE);

        DrawText("This is an example.", this->infos_position.x, this->infos_position.y, 30, WHITE);
        DrawText("Name: ", this->infos_position.x, this->infos_position.y + 40, 30, WHITE);
        DrawText("Weight: ", this->infos_position.x, this->infos_position.y + 40*2, 30, WHITE);
        DrawText("Value: ", this->infos_position.x, this->infos_position.y + 40*3, 30, WHITE);
        DrawText("Description: ", this->infos_position.x, this->infos_position.y + 40*4, 30, WHITE);

    }

}

bool ui_inventory::isBackpackOpen() { return isOpen; }

bool ui_inventory::isInfoOpen() { return isInfo; }

// assign all the slots coordinates relatively to inventory base
void ui_inventory::set_slots() {

    // first row
    this->slots[0].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor;
    this->slots[0].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor;

    this->slots[1].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor + 16*scale_factor*2;
    this->slots[1].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor;

    this->slots[2].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor + 16*scale_factor*4;
    this->slots[2].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor;

    this->slots[special_slot_weapons].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor + 16*scale_factor*6;
    this->slots[special_slot_weapons].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor;

    // second row
    this->slots[4].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor + 16*scale_factor;
    this->slots[4].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor + 16*scale_factor;

    this->slots[5].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor + 16*scale_factor*3;
    this->slots[5].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor + 16*scale_factor;

    //third row
    this->slots[6].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor;
    this->slots[6].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor + 16*scale_factor*2;

    this->slots[7].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor + 16*scale_factor*2;
    this->slots[7].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor + 16*scale_factor*2;

    this->slots[8].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor + 16*scale_factor*4;
    this->slots[8].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor + 16*scale_factor*2;

    this->slots[special_slot_rings].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor + 16*scale_factor*6;
    this->slots[special_slot_rings].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor + 16*scale_factor*2;

    // fourth row
    this->slots[10].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor + 16*scale_factor;
    this->slots[10].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor + 16*scale_factor*3;

    this->slots[11].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor + 16*scale_factor*3;
    this->slots[11].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor + 16*scale_factor*3;

    // fifth row
    this->slots[12].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*this->scale_factor;
    this->slots[12].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor + 16*scale_factor*4;

    this->slots[13].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor + 16*scale_factor*2;
    this->slots[13].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor + 16*scale_factor*4;

    this->slots[14].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor + 16*scale_factor*4;
    this->slots[14].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor + 16*scale_factor*4;
    // special slot idk yet
    this->slots[15].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor + 16*scale_factor*6;
    this->slots[15].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor + 16*scale_factor*4;
}

void ui_inventory::slots_up()
{
    if (this->isOpen == true && IsKeyPressed(KEY_W))
    {
        if (this->current_slot == 5)
        {
            this->current_slot = 2;
        }
        else if (this->current_slot == 6)
        {
            this->current_slot = 3;
        }
        else if (this->current_slot == 7 || this->current_slot == 8)
        {
            this->current_slot = 5;
        }
        else if (this->current_slot == 9)
        {
            this->current_slot = 6;
        }
        else if (this->current_slot == 11)
        {
            this->current_slot = 8;
        }
        else if (this->current_slot == 12)
        {
            this->current_slot = 9;
        }
        else if (this->current_slot == 13 || this->current_slot == 14)
        {
            this->current_slot = 11;
        }
        else if (this->current_slot == 15)
        {
            this->current_slot = 12;
        }
        else if (this->current_slot == this->special_slot_x)
        {
            this->current_slot = this->special_slot_rings;
        }
        else if (this->current_slot == this->special_slot_rings)
        {
            this->current_slot = this->special_slot_weapons;
        }
    }
}

void ui_inventory::slots_down()
{
    if(this->current_slot == 1 || this->current_slot == 2)
    {
        this->current_slot = 5;
    }
    else if (this->current_slot == 3)
    {
        this->current_slot = 6;
    }
    else if (this->current_slot == 5)
    {
        this->current_slot = 7;
    }
    else if (this->current_slot == 6)
    {
        this->current_slot = 8;
    }
    else if (this->current_slot == 7 || this->current_slot == 8)
    {
        this->current_slot = 11;
    }
    else if (this->current_slot == 9)
    {
        this->current_slot = 12;
    }
    else if (this->current_slot == 11)
    {
        this->current_slot = 13;
    }
    else if (this->current_slot == 12)
    {
        this->current_slot = 15;
    }
}