#ifndef RAYLIBSTARTER_INVENTORY_TEMPLATE_H
#define RAYLIBSTARTER_INVENTORY_TEMPLATE_H

#include <iostream>

template <typename T, int size>
class Inventory_Template
{
public:
    T items_container[size] {};

    void setItem(T item, int slot)
    {
        if (slot < size)
        {
            items_container[slot] = item;
            std::cout << "DEBUG: Item set " << slot << std::endl;
        }
        else
        {
            std::cout << "DEBUG: Item array full, no item added." << std::endl;
        }
    }

    T getItem(int slot)
    {
        return items_container[slot];
    }
};

#endif //RAYLIBSTARTER_INVENTORY_TEMPLATE_H
