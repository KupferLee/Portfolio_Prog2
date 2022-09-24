#ifndef RAYLIBSTARTER_CHARACTER_BASE_H
#define RAYLIBSTARTER_CHARACTER_BASE_H


#include "raylib.h"
#include "map.h"
#include <memory>


class character_base {
protected:
    Texture2D texture;
    Vector2 position{};
    Vector2 character_center = {0, 0};

    Vector3 current_tile{};
    Vector2 finish = {0, 0};
    Vector2 start = {0, 0};

    Texture2D message;
    Vector2 message_position = {0, 0};
    float scale_factor = 6;

    enum direction {down, up};
    direction facing_direction = down;

    bool can_move = true;
    bool is_message_open = false;
    bool was_message_seen = false;

    void Find_Path();
    bool Check_Left();
    bool Check_Right();
    bool Check_Down();
    bool Left_Equal_Down();
    bool Right_Equal_Down();
    bool Right_Equal_Left();
    bool Reached_Finish();



public:
    int Get_Position_X();
    int Get_Position_Y();
    int Get_Position_Z();
    void Draw();

    map* Map = nullptr;


};


#endif //RAYLIBSTARTER_CHARACTER_BASE_H
