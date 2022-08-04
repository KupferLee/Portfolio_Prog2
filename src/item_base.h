//
// Created by Lee on 04.08.2022.
//

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

protected:
    int weight = 0;
    std::string name = "empty";
    std::string description = "empty";
    //char name[5] = {'e', 'm', 'p', 't', 'y'};
    //char description[5] = {'e', 'm', 'p', 't', 'y'};
    int value = 0;

    Texture2D texture;
};


#endif //RAYLIBSTARTER_ITEM_BASE_H
