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

    enum direction {down, up};
    direction facing_direction = down;

    bool can_move = true;


public:
    int Get_Position_X();
    int Get_Position_Y();
    int Get_Position_Z();
    void Draw();

    map* Map = nullptr;


};


#endif //RAYLIBSTARTER_CHARACTER_BASE_H
