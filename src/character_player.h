//
// Created by Lee on 13.08.2022.
//

#ifndef RAYLIBSTARTER_CHARACTER_PLAYER_H
#define RAYLIBSTARTER_CHARACTER_PLAYER_H

#include "character_base.h"
#include "item_base.h"
#include "inventory_template.h"
#include "item_dagger.h"
#include "item_chest.h"
#include "item_potion.h"
#include "item_apple.h"
#include "item_crystal.h"
#include "item_ring.h"
#include "item_armor.h"

#include "map.h"


class character_player : public character_base {
public:
    character_player();
    void Update();

    // collision
    map* Map = nullptr;

protected:

    void Movement_Controls();
    void Calculate_Weight();
    void Check_Item_Collision();

    bool can_move = true;
    int base_strength = 20; // determines how much weight can be put in inventory
    int strength = 0;
    int total_weight = 0;

    // item objects
    item_dagger* Dagger = new item_dagger;
    item_chest* Chest = new item_chest;
    item_potion* Potion = new item_potion;
    item_apple* Golden_Apple = new item_apple;
    item_crystal* Crystal = new item_crystal;
    item_ring* Ring = new item_ring;
    item_armor* Armor = new item_armor;

    // Inventory for item objects
    Inventory_Template<item_base*, 14> Inventory;
    int inventory_slot = 0;
    void Item_Pickup(item_base* Item);
    //void item_drop();

    bool is_weapons_occupied;
    bool is_rings_occupied;
    bool is_armor_occupied;

    // sort algorithm
    void Sort_By_Weight();
    void Sort_By_Name();
    void Sort_By_Value();

    Texture2D sort_buttons;
    Texture2D sort_select;
    Rectangle sort_base_position;
    Rectangle sort_select_position[3];

    int current_button = 0;
    bool is_sort_open = false;

    void Update_Sort_Buttons();



public:
    int Get_Current_Slot();
    Texture2D Get_Texture(int slot);
    std::string Get_Item_Name(int slot);
    int Get_Item_Weight(int slot);
    int Get_Item_Value(int slot);
    std::string Get_Item_Description(int slot);

    bool Get_Weapons_Occupied();
    bool Get_Rings_Occupied();
    bool Get_Armor_Occupied();

    int Get_Total_Weight();
    int Get_Total_Strength();

    void Set_Can_Move(bool move);

    bool Get_Sort_Open();
    void Draw_Sort_Buttons();

};


#endif //RAYLIBSTARTER_CHARACTER_PLAYER_H
