#ifndef ITEMS_H
#define ITEMS_H

#include <string>
#include "delete.h"

using namespace std;


class Item: public Delete
{
public:
    Item();
    Item(string name, bool  required);
    string getItemName();
    bool isRequired();
    void deleteThis();

private:
    string name;
    bool required;
};

#endif // ITEMS_H
