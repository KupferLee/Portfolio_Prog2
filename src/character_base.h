#ifndef RAYLIBSTARTER_CHARACTER_BASE_H
#define RAYLIBSTARTER_CHARACTER_BASE_H


#include "raylib.h"
#include "map.h"
#include <memory>


class character_base {
protected:
    Vector2 position{};
    Vector3 current_tile{};

    int movement_speed;
    enum direction {down, up};
    direction facing_direction = down;
    Rectangle hitbox;
    bool is_collision = false;
    bool can_move = true;
    Texture2D texture;



public:
    int Get_Position_X();
    int Get_Position_Y();
    int Get_Position_Z();
    void Draw();
    // collision

    map* Map = nullptr;


};


#endif //RAYLIBSTARTER_CHARACTER_BASE_H
