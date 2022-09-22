//
// Created by Lee on 22.09.2022.
//

#ifndef RAYLIBSTARTER_CHARACTER_ROBOT_H
#define RAYLIBSTARTER_CHARACTER_ROBOT_H

#include "character_base.h"

class character_robot : public character_base {
protected:


public:
    character_robot();
    void Draw_Path();
    void Update();
    void Set_Starting_Pos();
};


#endif //RAYLIBSTARTER_CHARACTER_ROBOT_H
