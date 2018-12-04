#include "task.h"

Task::Task()
{

}


Task::Task(string description, string description1)
{
    this->taskDesc = description;
    this->taskCompleteDesc = description1;
    this->taskComplete = false;
}

string Task::getTaskDesc()
{
    return taskDesc;
}

void Task::setTaskComplete(bool complete)
{
    taskComplete = complete;
}

bool Task::getTaskComplete()
{
    return taskComplete;
}

bool Task::checkComplete()
{
    return taskComplete;
}

Item  Task::getRequiredItem()
{
    return *requiredItems;
}

void Task::deleteThis()
{
    delete this;
}

void Task::setRequiredItems(Item *item1)
{
    this->requiredItems = item1;

}
