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
    // TODO: dedicated equipment slots
    if (IsKeyPressed(KEY_M))
    {
        this->item_pickUp(this->dagger);
    }
    else if(IsKeyPressed(KEY_N))
    {
        this->item_pickUp(this->chest);
    }
    else if(IsKeyPressed(KEY_B))
    {
        this->item_pickUp(this->potion);
    }
    else if(IsKeyPressed(KEY_H))
    {
        this->item_pickUp(this->golden_apple);
    }
    else if(IsKeyPressed(KEY_J))
    {
        this->item_pickUp(this->crystal);
    }
    else if(IsKeyPressed(KEY_K))
    {
        this->item_pickUp(this->ring);
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
    if (this->gui_isOpen == true && this->isInfoOpen() == false &&  IsKeyPressed(KEY_TAB))
    {
        this->gui_current_slot = this->gui_special_slot_weapons;
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


        this->draw_info();
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
    // draw every occupied slot
    if (this->container_current_slot > i)
    {
        DrawTexturePro(this->tileset,
                       {(float)this->container.getItem(i)->getID()*16, 0, 16, 16},
                       {this->ui_slots[i].x, this->ui_slots[i].y, 16 * gui_scale_factor, 16 * gui_scale_factor},
                       {0, 0}, 0, WHITE);
    }
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
}

void inventory_ui::draw_info()
{
    // draw info for current normal slot if occupied
    if (gui_current_slot <= container_current_slot-1)
    {
        // print info accessing the container item
        DrawText(("Slot: " + std::to_string(this->gui_current_slot)).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40, 30, WHITE);
        DrawText(("Name: " + container.getItem(gui_current_slot)->getName()).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40 * 2, 30, WHITE);
        DrawText(("Weight: " + std::to_string(container.getItem(gui_current_slot)->getWeight())).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40 * 3, 30, WHITE);
        DrawText(("Value: " + std::to_string(container.getItem(gui_current_slot)->getValue())).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40 * 4, 30, WHITE);
        DrawText(("Description: " + container.getItem(gui_current_slot)->getDescription()).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40 * 5, 30, WHITE);
    }
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
    // draw no info since not occupied
    else
    {
        DrawText(("Slot: " + std::to_string(this->gui_current_slot)).c_str(), this->ui_infos_position.x, this->ui_infos_position.y + 40, 30, WHITE);
    }
}

void inventory_ui::item_pickUp(item_base* item)
{
    // only fill in the first 13 slots, not the 3 special ones
    if (this->container_current_slot < 13 && item != dagger && item != ring)
    {
        container.setItem(item, this->container_current_slot);

        this->container_current_slot++;
    }
    // if pick up weapon and special slot weapon empty fill in special slot
    else if (item == dagger && container.getItem(gui_special_slot_weapons) == NULL)
    {
        container.setItem(item, this->gui_special_slot_weapons);
    }
    // if pick up ring and special slot ring empty fill in special slot
    else if (item == ring) // && container.getItem(14 == NULL)
    {
        container.setItem(item, this->gui_special_slot_rings);
    }
    else
    {
        std::cout << "ERROR: No item assigned." << std::endl;
    }


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


    // second row
    this->ui_slots[3].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor;
    this->ui_slots[3].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor;

    this->ui_slots[4].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 3;
    this->ui_slots[4].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor;

    //third row
    this->ui_slots[5].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor;
    this->ui_slots[5].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 2;

    this->ui_slots[6].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 2;
    this->ui_slots[6].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 2;

    this->ui_slots[7].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 4;
    this->ui_slots[7].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 2;

    // fourth row
    this->ui_slots[8].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor;
    this->ui_slots[8].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 3;

    this->ui_slots[9].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 3;
    this->ui_slots[9].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 3;

    // fifth row
    this->ui_slots[10].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * this->gui_scale_factor;
    this->ui_slots[10].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 4;

    this->ui_slots[11].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 2;
    this->ui_slots[11].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 4;

    this->ui_slots[12].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 4;
    this->ui_slots[12].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 4;

    // special slots
    this->ui_slots[gui_special_slot_weapons].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 6;
    this->ui_slots[gui_special_slot_weapons].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor;

    this->ui_slots[gui_special_slot_rings].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 6;
    this->ui_slots[gui_special_slot_rings].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 2;

    this->ui_slots[gui_special_slot_x].x = GetScreenWidth() / 2 - this->inventory_base.width / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 6;
    this->ui_slots[gui_special_slot_x].y = GetScreenHeight() / 2 - this->inventory_base.height / 2 * this->gui_scale_factor + 2 * gui_scale_factor + 16 * gui_scale_factor * 4;
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