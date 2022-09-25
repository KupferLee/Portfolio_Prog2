//
// Created by Lee on 22.09.2022.
//

#ifndef RAYLIBSTARTER_CHARACTER_ROBOT_H
#define RAYLIBSTARTER_CHARACTER_ROBOT_H

#include "character_base.h"

class character_robot : public character_base {
protected:
    // GUI
    bool is_message_open = false;
    bool was_message_seen = false;

    float scale_factor = 6;
    Vector2 message_position = {0, 0};

    Texture2D message;

    // Path finding
    bool Check_Left();
    bool Check_Right();
    bool Check_Down();
    bool Left_Equal_Down();
    bool Right_Equal_Down();
    bool Right_Equal_Left();
    bool Reached_Finish();

    // items
    int which_item = -1;

public:
    character_robot();
    void Update(bool inventory);
    void Set_Starting_Pos();

    void Find_Path();
    void Draw_Path();

    bool Is_Message_Open();
    void Draw_GUI();

    int Item_Found();
    void Item_Pick_Up();

};


#endif //RAYLIBSTARTER_CHARACTER_ROBOT_H
