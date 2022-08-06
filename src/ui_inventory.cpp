//
// Created by Lee on 06.08.2022.
//

#include "ui_inventory.h"

ui_inventory::ui_inventory()
{
    this->backpack = LoadTexture("assets/graphics/gui/backpack.png");
    this->inventory_base = LoadTexture("assets/graphics/gui/inventory.png");
    this->inventory_selection = LoadTexture("assets/graphics/gui/selection.png");

    // assign all the slots coordinates relatively to inventory base

    // first row
    this->slots[0].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor;
    this->slots[0].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor;

    this->slots[1].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor + 16*scale_factor*2;
    this->slots[1].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor;

    this->slots[2].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor + 16*scale_factor*4;
    this->slots[2].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor;
    // special slot weapons
    this->slots[3].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor + 16*scale_factor*6;
    this->slots[3].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor;

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
    // special slot rings
    this->slots[9].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor + 16*scale_factor*6;
    this->slots[9].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor + 16*scale_factor*2;

    // fourth row
    this->slots[10].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor + 16*scale_factor;
    this->slots[10].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor + 16*scale_factor*3;

    this->slots[11].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor + 16*scale_factor*3;
    this->slots[11].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor + 16*scale_factor*3;

    // fifth row
    this->slots[12].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor;
    this->slots[12].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor + 16*scale_factor*4;

    this->slots[13].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor + 16*scale_factor*2;
    this->slots[13].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor + 16*scale_factor*4;

    this->slots[14].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor + 16*scale_factor*4;
    this->slots[14].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor + 16*scale_factor*4;
    // special slot idk yet
    this->slots[15].x = GetScreenWidth()/2 - this->inventory_base.width/2*this->scale_factor + 2*scale_factor + 16*scale_factor*6;
    this->slots[15].y = GetScreenHeight()/2 - this->inventory_base.height/2*this->scale_factor + 2*scale_factor + 16*scale_factor*4;
}

void ui_inventory::update()
{
    if (this->isOpen == true && IsKeyPressed(KEY_D) && this->current_slot <= 14)
    {
        this->current_slot++;
    }
    if (this->isOpen == true && IsKeyPressed(KEY_A) && this->current_slot >= 1)
    {
        this->current_slot--;
    }

    // when i pressed change inventory state
    if(IsKeyPressed(KEY_I) && this->isOpen == true)
    {
        this->isOpen = false;
    }

    else if (IsKeyPressed(KEY_I) && this->isOpen == false)
    {
        this->isOpen = true;
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


}

bool ui_inventory::isBackpackOpen() { return isOpen; }