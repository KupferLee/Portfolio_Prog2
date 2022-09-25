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
    void Draw_GUI();
    void Update(bool inventory);
    void Set_Starting_Pos();
    bool Is_Message_Open();
};


#endif //RAYLIBSTARTER_CHARACTER_ROBOT_H
