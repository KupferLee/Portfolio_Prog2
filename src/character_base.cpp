#include "character_base.h"

int character_base::Get_Position_X()
{
    this->current_tile.x = (this->position.x / 32) - 1;

    return current_tile.x;
}

int character_base::Get_Position_Y()
{
    this->current_tile.y = this->position.y / 32;

    return current_tile.y;
}

int character_base::Get_Position_Z()
{
    this->current_tile.z = 30 * (this->current_tile.y - 1) + this->current_tile.x;
    return current_tile.z;
}

void character_base::Draw()
{

    DrawTexturePro(this->texture,
                   {(float)facing_direction*32, (float)facing_direction*32, 32, 32},
                   {this->position.x, this->position.y, 32, 32},
                   {32, 32}, 0, WHITE);

}


void character_base::Find_Path()
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

bool character_base::Check_Left()
{
    if (Vector2Distance({character_center.x - 32, character_center.y + 16}, finish)
        < Vector2Distance({character_center.x + 32, character_center.y}, finish)
        && Vector2Distance({character_center.x - 32, character_center.y}, finish)
           < Vector2Distance({character_center.x, character_center.y + 32}, finish))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool character_base::Check_Right()
{
    if (Vector2Distance({character_center.x + 32, character_center.y}, finish)
        < Vector2Distance({character_center.x - 32, position.y}, finish)
        && Vector2Distance({character_center.x + 32, character_center.y}, finish)
           < Vector2Distance({character_center.x, character_center.y + 32}, finish))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool character_base::Check_Down()
{
    if (Vector2Distance({character_center.x, character_center.y + 32}, finish)
        < Vector2Distance({character_center.x - 32, character_center.y}, finish)
        && Vector2Distance({character_center.x, character_center.y + 32}, finish)
           < Vector2Distance({character_center.x + 32, character_center.y}, finish))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool character_base::Left_Equal_Down()
{
    if (Vector2Distance({character_center.x - 32, character_center.y}, finish)
        < Vector2Distance({character_center.x + 32, character_center.y}, finish)
        && Vector2Distance({character_center.x - 32, character_center.y}, finish)
           == Vector2Distance({character_center.x, character_center.y + 32}, finish))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool character_base::Right_Equal_Down()
{
    if (Vector2Distance({character_center.x + 32, character_center.y}, finish)
        < Vector2Distance({character_center.x - 32, character_center.y}, finish)
        && Vector2Distance({character_center.x + 32, character_center.y}, finish)
           == Vector2Distance({character_center.x, character_center.y + 32}, finish))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool character_base::Right_Equal_Left()
{
    if (Vector2Distance({character_center.x + 32, character_center.y}, finish)
        == Vector2Distance({character_center.x - 32, character_center.y}, finish)
        && Vector2Distance({character_center.x, character_center.y + 32}, finish)
           <= Vector2Distance({character_center.x + 32, character_center.y}, finish))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool character_base::Reached_Finish()
{
    if (character_center.x == finish.x && character_center.y == finish.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}
