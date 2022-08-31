#ifndef RAYLIBSTARTER_CHARACTER_BASE_H
#define RAYLIBSTARTER_CHARACTER_BASE_H


#include "raylib.h"


class character_base {
protected:
    Vector2 position;

    int movement_speed;
    enum direction {down, up};
    direction facing_direction;

    Texture2D texture;




public:
    virtual Vector2 getPosition();
    void draw();
    //void update();

};


#endif //RAYLIBSTARTER_CHARACTER_BASE_H
