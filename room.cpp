 #include "room.h"

Room::Room()
{

}

/**
 * Create a Room object. Short and long description to be supplied.
 * Default value of hasItem is set to false.
 */
Room::Room(string description, QString longDescription)
{
    this->desc = description;
    this->lDesc = longDescription;
    this->hasItem = false;
}

/**
 * Return short description of room.
 */
string Room::shortDesc()
{
    return desc;
}

QString Room::longDesc()
{
    return lDesc;
}

void Room::setExits(Room *north, Room *east, Room *south, Room *west)
{
    if (north != NULL){
        exits["north"] = north;
    }
    if (east != NULL){
        exits["east"] = east;
    }
    if (south != NULL){
        exits["south"] = south;
    }
    if (west != NULL){
        exits["west"] = west;
    }
}


Room* Room::nextRoom(string direction)
{
    map<string, Room*>::iterator next = exits.find(direction);
    if (next == exits.end())
    {
        return NULL;
    }
    return next->second;
}

/**
 * Add item (*item1) to room.
 * Set Room hasItem to true.
 */
void Room::addItemsToRoom(Item *item1)
{
    this->roomItems = item1;
    this->hasItem = true;
}


Item* Room::getItemFromRoom()
{
    return roomItems;
}

bool Room::checkItem()
{
    return hasItem;
}

void Room::setHasItem(bool flag)
{
    this->hasItem = flag;
}

void Room::deleteThis()
{
    delete this;
}

