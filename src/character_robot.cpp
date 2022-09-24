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

    robot_center = {position.x - 16, position.y - 16};

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
        DrawCircle(robot_center.x, robot_center.y, 10, BLACK);
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

void character_robot::Find_Path()
{
    // do not consider water
    if (IsKeyDown(KEY_SPACE) && !Reached_Finish())
    {
        // checks which of the 3 neighbour tiles is closest to finish tile and steps onto it
        // check left
        if (Check_Left())
        {
            this->position = {this->position.x - 32, this->position.y};
        }
            // check right
        else if (Check_Right())
        {
            this->position = {this->position.x + 32, this->position.y};
        }
            // if right or left and down are same amount do down
            // if right and left are same amount do down
        else if (Right_Equal_Down() || Left_Equal_Down() || Right_Equal_Left())
        {
            this->position = {this->position.x, this->position.y + 32};
        }
            // check down
        else if (Check_Down())
        {
            this->position = {this->position.x, this->position.y + 32};

        }

        Map->Add_Robot_Path(this->current_tile.z);
    }
        // consider water with path finding
    else if (IsKeyDown(KEY_B) && !Reached_Finish())
    {
        // checks which of the 3 neighbour tiles is closest to finish tile and steps onto it
        // check left
        if (Check_Left() && Map->Get_Tile(current_tile.z - 1) == 0)
        {
            this->position = {this->position.x - 32, this->position.y};
        }
            // check right
        else if (Check_Right() && Map->Get_Tile(current_tile.z + 1) == 0)
        {
            this->position = {this->position.x + 32, this->position.y};
        }
            // if right or left and down are same amount do down
            // if right and left are same amount do down
        else if (Right_Equal_Down()  || Left_Equal_Down() || Right_Equal_Left() && Map->Get_Tile(current_tile.z) == 0)
        {
            this->position = {this->position.x, this->position.y + 32};
        }
            // check down
        else if (Check_Down() && Map->Get_Tile(current_tile.z + 30) == 0)
        {
            this->position = {this->position.x, this->position.y + 32};

        }

        Map->Add_Robot_Path(this->current_tile.z);
    }
    else if (Reached_Finish())
    {
        Map->Add_Robot_Path(this->current_tile.z);
        this->facing_direction = up;
        if (this->was_message_seen == false)
        {
            this->is_message_open = true;
            this->was_message_seen = true;
        }

    }
}

bool character_robot::Check_Left()
{
    if (Vector2Distance({robot_center.x - 32, robot_center.y + 16}, finish)
    < Vector2Distance({robot_center.x + 32, robot_center.y}, finish)
    && Vector2Distance({robot_center.x - 32, robot_center.y},finish)
    < Vector2Distance({robot_center.x, robot_center.y + 32}, finish))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool character_robot::Check_Right()
{
    if (Vector2Distance({robot_center.x + 32, robot_center.y}, finish)
    < Vector2Distance({robot_center.x - 32, position.y}, finish)
    && Vector2Distance({robot_center.x + 32, robot_center.y}, finish)
    < Vector2Distance({robot_center.x, robot_center.y + 32}, finish))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool character_robot::Check_Down()
{
    if (Vector2Distance({robot_center.x, robot_center.y + 32}, finish)
    < Vector2Distance({robot_center.x - 32, robot_center.y}, finish)
    && Vector2Distance({robot_center.x, robot_center.y + 32}, finish)
    < Vector2Distance({robot_center.x + 32, robot_center.y}, finish))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool character_robot::Left_Equal_Down()
{
    if (Vector2Distance({robot_center.x - 32, robot_center.y}, finish)
    < Vector2Distance({robot_center.x + 32, robot_center.y}, finish)
    && Vector2Distance({robot_center.x - 32, robot_center.y},finish)
    == Vector2Distance({robot_center.x, robot_center.y + 32}, finish))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool character_robot::Right_Equal_Down()
{
    if (Vector2Distance({robot_center.x + 32, robot_center.y}, finish)
    < Vector2Distance({robot_center.x - 32, robot_center.y}, finish)
    && Vector2Distance({robot_center.x + 32, robot_center.y}, finish)
    == Vector2Distance({robot_center.x, robot_center.y + 32}, finish))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool character_robot::Right_Equal_Left()
{
    if (Vector2Distance({robot_center.x + 32, robot_center.y}, finish)
    == Vector2Distance({robot_center.x - 32, robot_center.y}, finish)
    && Vector2Distance({robot_center.x, robot_center.y + 32}, finish)
    <= Vector2Distance({robot_center.x + 32, robot_center.y}, finish))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool character_robot::Reached_Finish()
{
    if (robot_center.x == finish.x && robot_center.y == finish.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}