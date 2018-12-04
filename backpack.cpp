#include "backpack.h"

Backpack::Backpack()
{
    activeItems[0] = new Item();
    activeItems[1] = new Item();
    activeItems[2] = new Item();
}

void Backpack::addItem(Item *item, int index)
{
    activeItems[index] = item;
}

Item* Backpack::getItem(int index)
{
    return activeItems[index];
}

void Backpack::deleteThis()
{
    activeItems[0]->deleteThis();
    activeItems[1]->deleteThis();
    activeItems[2]->deleteThis();
}




