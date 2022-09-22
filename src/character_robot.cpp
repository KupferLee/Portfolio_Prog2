//
// Created by Lee on 22.09.2022.
//

#include "character_robot.h"

character_robot::character_robot()
{
    this->texture = LoadTexture("assets/graphics/characters/robot_32.png");
    this->facing_direction = down;
}

void character_robot::Update()
{
    /*
    if (IsKeyPressed(KEY_SPACE))
    {
        if (Vector2Distance({Map->Get_Start_Pos().x - 32, Map->Get_Start_Pos().y}, Map->Get_Fin_Pos()) < Vector2Distance({Map->Get_Start_Pos().x + 32, Map->Get_Start_Pos().y}, Map->Get_Fin_Pos()) && Vector2Distance({Map->Get_Start_Pos().x, Map->Get_Start_Pos().y + 32}, Map->Get_Fin_Pos()))
        {
            this->position = {this->position.x - 32, this->position.y};
            Map->Add_Robot_Path(position.x, position.y);
        }
        else if (Vector2Distance({Map->Get_Start_Pos().x + 32, Map->Get_Start_Pos().y}, Map->Get_Fin_Pos()) < Vector2Distance({Map->Get_Start_Pos().x - 32, Map->Get_Start_Pos().y}, Map->Get_Fin_Pos()) && Vector2Distance({Map->Get_Start_Pos().x, Map->Get_Start_Pos().y + 32}, Map->Get_Fin_Pos()))
        {
            this->position = {this->position.x + 32, this->position.y};
            Map->Add_Robot_Path(position.x, position.y);
        }
        else if (Vector2Distance({Map->Get_Start_Pos().x, Map->Get_Start_Pos().y + 32}, Map->Get_Fin_Pos()) < Vector2Distance({Map->Get_Start_Pos().x - 32, Map->Get_Start_Pos().y}, Map->Get_Fin_Pos()) && Vector2Distance({Map->Get_Start_Pos().x + 32, Map->Get_Start_Pos().y}, Map->Get_Fin_Pos()))
        {
            this->position = {this->position.x, this->position.y + 32};
            Map->Add_Robot_Path(position.x, position.y);
        }
    }
    */
    
}


void character_robot::Draw_Path()
{
    DrawText(("X: " + std::to_string((int)Map->Get_Start_Pos().x)).c_str(), 30, 30, 30, BLACK);
    DrawText(("Y: " + std::to_string((int)Map->Get_Start_Pos().y)).c_str(), 30, 70, 30, BLACK);

    DrawText(("X: " + std::to_string((int)Map->Get_Fin_Pos().x)).c_str(), 30, 120, 30, BLACK);
    DrawText(("Y: " + std::to_string((int)Map->Get_Fin_Pos().y)).c_str(), 30, 160, 30, BLACK);

    if (IsKeyDown(KEY_H))
    {
        if (Vector2Distance({Map->Get_Start_Pos().x - 32, Map->Get_Start_Pos().y}, Map->Get_Fin_Pos()) < Vector2Distance({Map->Get_Start_Pos().x + 32, Map->Get_Start_Pos().y}, Map->Get_Fin_Pos()))
        {
        }
        else
        {

        }

        // DrawRectangle(current_step.x, current_step.y, 32, 32, PINK);

        DrawRectangle(Map->Get_Start_Pos().x * 32, Map->Get_Start_Pos().y * 32, 32, 32, GREEN);
        DrawRectangle(Map->Get_Fin_Pos().x * 32, Map->Get_Fin_Pos().y * 32, 32, 32, RED);

        DrawLine(Map->Get_Start_Pos().x * 32 + 16, Map->Get_Start_Pos().y * 32 + 16, Map->Get_Fin_Pos().x * 32 + 16, Map->Get_Fin_Pos().y * 32 + 16, PINK);

    }
}

void character_robot::Set_Starting_Pos() { this->position = {(Map->Get_Start_Pos().x + 1) * 32, (Map->Get_Start_Pos().y + 1) * 32}; }