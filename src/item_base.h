#ifndef RAYLIBSTARTER_ITEM_BASE_H
#define RAYLIBSTARTER_ITEM_BASE_H

#include "raylib.h"
#include "string"

class item_base {
public:
    virtual int getValue();
    virtual std::string getName();
    virtual std::string getDescription();
    virtual int getWeight();
    virtual int getID();
    virtual Texture2D getTexture();
    // TODO: make method that turns string to char for DrawText output

protected:
    int weight = 0;
    std::string name = "empty";
    std::string description = "empty";
    int value = 0;
    int texture_id = -1; // were on the tileset is this item
    Texture2D texture;
};


#endif //RAYLIBSTARTER_ITEM_BASE_H
