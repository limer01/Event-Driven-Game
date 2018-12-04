#ifndef TASK_H
#define TASK_H

#include "items.h"
#include <string>
using namespace std;

class Task : public Delete
{


public:
    Task();
    Task(string description, string description1);
    string getTaskDesc();
    void setTaskComplete(bool complete);
    bool getTaskComplete();
    bool checkComplete();
    void setRequiredItems(Item *item1);
    Item  getRequiredItem();
    void deleteThis();

private:
    string taskDesc;
    string taskCompleteDesc;
    bool taskComplete;
    Item *requiredItems;

};

#endif // TASK_H
