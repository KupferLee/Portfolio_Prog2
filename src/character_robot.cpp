//
// Created by Lee on 22.09.2022.
//

#include "character_robot.h"

character_robot::character_robot()
{
    this->texture = LoadTexture("assets/graphics/characters/robot_32.png");
    this->message = LoadTexture("assets/graphics/gui/path_found.png");
    this->facing_direction = down;

    this->message_position = {195, (float)GetScreenHeight() / 2 - this->message.height - 50};
}

void character_robot::Update(bool inventory)
{
    // update movement every turn
    Get_Position_X();
    Get_Position_Y();
    Get_Position_Z();

    character_center = {position.x - 16, position.y - 16};

    if (inventory == false)
    {
        Find_Path();
    }

    if (is_message_open == true && IsKeyPressed(KEY_ENTER))
    {
        is_message_open = false;
    }
}


void character_robot::Draw_Path()
{
    if (IsKeyDown(KEY_H))
    {
        DrawText(("Start  X: " + std::to_string((int)Map->Get_Start_Pos().x)).c_str(), 30, 30, 30, BLACK);
        DrawText(("Start  Y: " + std::to_string((int)Map->Get_Start_Pos().y)).c_str(), 30, 70, 30, BLACK);
        DrawText(("Finish X: " + std::to_string((int)Map->Get_Fin_Pos().x)).c_str(), 30, 120, 30, BLACK);
        DrawText(("Finish Y: " + std::to_string((int)Map->Get_Fin_Pos().y)).c_str(), 30, 160, 30, BLACK);

        DrawCircle(start.x, start.y, 16, GREEN);
        DrawCircle(finish.x, finish.y, 16, RED);
        DrawCircle(character_center.x, character_center.y, 10, BLACK);
    }

    if (is_message_open == true)
    {
        // base texture that message is printed on
        DrawTexturePro(message,
                       {0, 0, (float)message.width, (float)message.height},
                       {(float)GetScreenWidth()/2 - message.width/2*scale_factor, (float)GetScreenHeight()/2 - message.height/2*scale_factor, (float)message.width*scale_factor, (float)message.height*scale_factor},
                       {0, 0}, 0, WHITE);

        // Text of the message
        DrawText("Your robot found the fastest path!", message_position.x, message_position.y, 30, WHITE);
        DrawText("To follow it stand on the start tile", message_position.x, message_position.y + 40, 30, WHITE);
        DrawText("and press SPACE!", message_position.x, message_position.y + 80, 30, WHITE);

        DrawText("Close this message with ENTER", message_position.x, message_position.y + 300, 30, WHITE);
    }
}

void character_robot::Set_Starting_Pos()
{
    this->start = {Map->Get_Start_Pos().x * 32 + 16, Map->Get_Start_Pos().y * 32 + 16};
    this->finish = {Map->Get_Fin_Pos().x * 32 + 16, Map->Get_Fin_Pos().y * 32 + 16};
    this->position = {(Map->Get_Start_Pos().x + 1) * 32, (Map->Get_Start_Pos().y + 1) * 32};
}
