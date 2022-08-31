#ifndef RAYLIBSTARTER_ITEM_RING_H
#define RAYLIBSTARTER_ITEM_RING_H

#include "item_base.h"

class item_ring : public item_base {
public:
    item_ring();

    int get_strength();

protected:
    int plus_strength = 0;
};


#endif //RAYLIBSTARTER_ITEM_RING_H
