#ifndef BACKPACK_H
#define BACKACK_H

#include "items.h"
#include "delete.h"

class Backpack : public Delete
{
public:
    Backpack();
    void addItem(Item *item, int index);
    Item* getItem(int index);
    void deleteThis();

private:
    Item *activeItems[2];
};

#endif // BACKPACK_H
