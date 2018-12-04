#include "items.h"

Item::Item()
{

}

Item::Item(string name, bool required)
{
    this->name = name;
    this->required = required;
}

string Item::getItemName()
{
    return name;
}


bool Item::isRequired()
{
    return required;
}

void Item::deleteThis()
{
    delete this;
}
