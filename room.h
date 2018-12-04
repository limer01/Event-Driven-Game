#ifndef ROOM_H
#define ROOM_H

#include "items.h"
#include "delete.h"


#include <string>
#include <map>
#include <vector>
#include <QString>
#include <QFile>
#include <QDebug>
using namespace std;


class Room : public Delete
{

public:
    Room();
    Room(string description, QString longDescription);
    string shortDesc();
    QString longDesc();
    void setExits(Room *north, Room *east, Room *south, Room *west);
    Room* nextRoom(string direction);
    string getItemName();
    void addItemsToRoom(Item *item1);
    Item* getItemFromRoom();
    bool checkItem();
    void setHasItem(bool flag);
    void readFile();
    void deleteThis();

private:
    string desc;
    QString lDesc;
    bool hasItem;
    bool fileRead = false;
    map<string,Room*> exits;
    Item *roomItems;
    vector<QString> longDescriptions();

};

#endif // ROOM_H
