#ifndef RAYLIBSTARTER_CHARACTER_BASE_H
#define RAYLIBSTARTER_CHARACTER_BASE_H


#include "raylib.h"
#include "map.h"


class character_base {
protected:
    Vector2 position;

    int movement_speed;
    enum direction {down, up};
    direction facing_direction = down;
    Rectangle hitbox;
    bool is_collision = false;
    bool can_move = true;
    Texture2D texture;



public:
    virtual Vector2 get_position();
    void Draw();
    // collision
    bool Check_Collision(Rectangle obstacle);
    Rectangle Get_Hitbox();

};


#endif //RAYLIBSTARTER_CHARACTER_BASE_H
