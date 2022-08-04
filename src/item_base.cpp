//
// Created by Lee on 04.08.2022.
//

#include "item_base.h"

// methods that return attributs of the object since that will be the same for every child object

int item_base::getWeight() { return this->weight; }

std::string item_base::getName() { return name; }

std::string item_base::getDescription() { return this->description; }

int item_base::getValue() { return this->value; }

