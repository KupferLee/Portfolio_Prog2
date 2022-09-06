#include "item_base.h"

// methods that return attributs of the object since that will be the same for every child object

int item_base::Get_Weight() { return this->weight; }

std::string item_base::Get_Name() { return name; }

std::string item_base::Get_Description() { return this->description; }

int item_base::Get_Value() { return this->value; }

int item_base::Get_ID() { return this->texture_id; }

Texture2D item_base::Get_Texture() { return this->texture; }

