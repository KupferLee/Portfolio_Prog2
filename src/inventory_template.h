//
// Created by Lee on 11.08.2022.
//

#ifndef RAYLIBSTARTER_INVENTORY_TEMPLATE_H
#define RAYLIBSTARTER_INVENTORY_TEMPLATE_H

template <typename T, int size>
class Inventory_Template
{
public:
    T items_container[size];

    void setItem(T item, int slot)
    {
        if (slot <= size)
        {
            // this gives error "Segmentation fault"
            items_container[slot] = item;
        }
    }

    T getItem(int slot)
    {
        return items_container[slot];
    }
};

#endif //RAYLIBSTARTER_INVENTORY_TEMPLATE_H
