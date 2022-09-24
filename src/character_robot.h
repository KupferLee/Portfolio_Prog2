//
// Created by Lee on 22.09.2022.
//

#ifndef RAYLIBSTARTER_CHARACTER_ROBOT_H
#define RAYLIBSTARTER_CHARACTER_ROBOT_H

#include "character_base.h"

class character_robot : public character_base {
protected:
    bool is_message_open = false;
    bool was_message_seen = false;
    bool Check_Left();
    bool Check_Right();
    bool Check_Down();
    bool Left_Equal_Down();
    bool Right_Equal_Down();
    bool Right_Equal_Left();
    bool Reached_Finish();

    Vector2 finish = {0, 0};
    Vector2 start = {0, 0};
    Vector2 robot_center = {0, 0};
    Vector2 message_position = {0, 0};
    float scale_factor = 6;

    Texture2D message;

    void Find_Path();

public:
    character_robot();
    void Draw_Path();
    void Update(bool inventory);
    void Set_Starting_Pos();
};


#endif //RAYLIBSTARTER_CHARACTER_ROBOT_H
