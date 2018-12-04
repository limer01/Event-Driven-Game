#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QBrush>
#include <QImage>
#include <QMediaPlayer>

MainWindow
::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setup();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setup() //Setup scene
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,600,400);
    scene->setBackgroundBrush(QBrush(QImage(":/images/map.png")));

    readFile(":/text/long_descriptions.txt", &roomDescriptions, 19);  // Read File

    createRooms();     // Create Rooms
    setTasks();       // Create Tasks
    myItems = new Backpack();

    ui->terminal_Room->setText(QString::fromStdString("Current Room: A"));
    ui->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->view->setScene(scene);



}

void MainWindow::createRooms()
{
    Room *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *m, *n, *o, *p, *q, *r, *s, *t;

    // Create Rooms (Short , Long Descriptions)
    a = new Room("A", roomDescriptions[0]);
    b = new Room("B", roomDescriptions[1]);
    c = new Room("C", roomDescriptions[2]);
    d = new Room("D", roomDescriptions[3]);
    e = new Room("E", roomDescriptions[4]);
    f = new Room("F", roomDescriptions[5]);
    g = new Room("G", roomDescriptions[6]);
    h = new Room("H", roomDescriptions[7]);
    i = new Room("I", roomDescriptions[8]);
    j = new Room("J", roomDescriptions[9]);
    k = new Room("K", roomDescriptions[10]);
    l = new Room("L", roomDescriptions[11]);
    m = new Room("M", roomDescriptions[12]);
    n = new Room("N", roomDescriptions[13]);
    o = new Room("O", roomDescriptions[14]);
    p = new Room("P", roomDescriptions[15]);
    q = new Room("Q", roomDescriptions[16]);
    r = new Room("R", roomDescriptions[17]);
    s = new Room("S", roomDescriptions[18]);
    t = new Room("T", roomDescriptions[19]);

    // Set exits for each room
    a->setExits(b, NULL, NULL, NULL);
    b->setExits(NULL, NULL, a, c);
    c->setExits(d, b, NULL, NULL);
    d->setExits(f, NULL, c, NULL);
    e->setExits(g, NULL, NULL, f);
    f->setExits(NULL, e, d, h);
    g->setExits(NULL, NULL, e, NULL);
    h->setExits(i, f, n, NULL);
    i->setExits(NULL, NULL, h, j);
    j->setExits(NULL, i, NULL, k);
    k->setExits(NULL, j, l, NULL);
    l->setExits(k, NULL, m, s);
    m->setExits(l, n, o, p);
    n->setExits(h, NULL, NULL, m);
    o->setExits(m, NULL, NULL, NULL);
    p->setExits(NULL, m, NULL, q);
    q->setExits(r, p, NULL, NULL);
    r->setExits(t, s, q, NULL);
    s->setExits(NULL, l, NULL, r);
    t->setExits(NULL, NULL, r, NULL);

    //Add each room to vector rooms for teleport function
    rooms.push_back(a);
    rooms.push_back(b);
    rooms.push_back(c);
    rooms.push_back(d);
    rooms.push_back(e);
    rooms.push_back(f);
    rooms.push_back(g);
    rooms.push_back(h);
    rooms.push_back(i);
    rooms.push_back(j);
    rooms.push_back(k);
    rooms.push_back(l);
    rooms.push_back(m);
    rooms.push_back(n);
    rooms.push_back(o);
    rooms.push_back(p);
    rooms.push_back(q);
    rooms.push_back(r);
    rooms.push_back(s);
    rooms.push_back(t);

    //Set rooms where items are available
    itemRoom[0] = c;
    itemRoom[1] = k;
    itemRoom[2] = q;

    //Set starting room
    currentRoom = a;
    getRoomDescription();

}

/**
 *  Creates tasks and sets required items to complete each task
 */
void MainWindow::setTasks()
{
    Task *firstTask, *secondTask, *thirdTask, *fourthTask;
    Item *key, *fuel, *combination;

    firstTask = new Task("Find out where you are! (Read Map)", "");

    secondTask = new Task("Open Trap Door (Room E)", "");
    key = new Item("Key", true);
    secondTask->setRequiredItems(key);
    itemRoom[0]->addItemsToRoom(key);

    thirdTask = new Task("Turn on the generator! (Room O)", "");
    fuel = new Item("Fuel", true);
    thirdTask->setRequiredItems(fuel);
    itemRoom[1]->addItemsToRoom(fuel);


    fourthTask = new Task("Open the door to escape! (Room T)", "");
    combination = new Item("Combination", true);
    fourthTask->setRequiredItems(combination);
    itemRoom[2]->addItemsToRoom(combination);



    allTask[0] = firstTask;
    allTask[1] = secondTask;
    allTask[2] = thirdTask;
    allTask[3] = fourthTask;

    currentTask = allTask[0];               //Sets current task to first task
    taskText = currentTask->getTaskDesc();  //Gets task description for current task

}

/**
 *  Function to go to each room
 */
void MainWindow::goRoom(string direction)
{
    ui->textBox->setText(QString::fromStdString(""));
    Room* nextRoom = currentRoom->nextRoom(direction);

    if (nextRoom != NULL)
    {
        currentRoom = nextRoom;
        ui->terminal_Room->setText(QString::fromStdString("Current Room: " + currentRoom->shortDesc()));
        getRoomDescription();

    }
    else
    {   //Error message if the player attempts to go to a room that doesn't exist
        ui->textBox->setText(QString::fromStdString("There is nothing but a blank wall, you must try another direction..."));
    }
}

/**
 *  Function to check if tasks are complete
 */
void MainWindow::checkTask(int a)
{
    if (!currentTask->getTaskComplete()){
        currentTask->setTaskComplete(true);
        currentTask = allTask[a];
        taskText += " (Complete)\n" + currentTask->getTaskDesc(); //Adds (Complete) to the task description once complete
    }
}

/**
 *  Function to read in file long_descriptions.txt which contains room descriptions and add to vector v
 */
void MainWindow::readFile(QString f, vector<QString> *v, int size)
{
    qDebug("read file");
    v->reserve(size);
    QFile file(f);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug("if");
        return;
    }

    QTextStream in(&file);
    while(!in.atEnd()){
        qDebug("while");
        QString line = in.readLine();
        v->push_back(line);
    }
}



void MainWindow::on_north_clicked()
{
    goRoom("north");  //When north is clicked in the UI calls function goRoom and supplies direction

}

void MainWindow::on_east_clicked()
{
    goRoom("east");

}

void MainWindow::on_south_clicked()
{
    goRoom("south");

}

void MainWindow::on_west_clicked()
{
    goRoom("west");

}

/**
 *  Function to display room description to UI
 */
void MainWindow::getRoomDescription()
{
    roomText = currentRoom->longDesc().toStdString();
    if(currentRoom->checkItem()){
        roomText += "\nItem available: " + currentRoom->getItemFromRoom()->getItemName() + " (Button B to pick up)";
    }
    ui->textBox->setText(QString::fromStdString(roomText));
}

/**
 *  Function to teleport player to random room when teleport button is clicked
 */
void MainWindow::on_teleport_clicked()
{
    int Rand;
    Room* randRoom = rooms.at(Rand = rand() % 20);
    currentRoom = randRoom;    //Sets current room to random room
    getRoomDescription();
    ui->terminal_Room->setText(QString::fromStdString("Current Room: " + currentRoom->shortDesc()));
}

void MainWindow::on_displayTask_clicked()
{
    //Displays current and complete tasks when display tasks button is clicked
    ui->textBox->setText(QString::fromStdString(taskText));
}

/**
 *  Function to define what happens when button A is clicked.
 *  buttonA is defined as the action button, used to complete a task.
 */
void MainWindow::on_buttonA_clicked()
{
    //If current room is A and task is not already complete output to UI outcome of completing first task
    if (currentRoom->shortDesc() == "A" && !allTask[0]->checkComplete()){
        checkTask(1);
        ui->textBox->setText(QString::fromStdString("====MAP DETAILS====\nSouth East: (Room C) Key\nSouth West: (Room Q) Combination\nNorth: (Room K) Fuel"));
    }
    if(currentRoom->shortDesc() == "E" && myItems->getItem(0)->getItemName() == currentTask->getRequiredItem().getItemName() && !allTask[1]->checkComplete()){
        checkTask(2);
        ui->textBox->setText(QString::fromStdString("You find an old set of instructions.\nDocument details that in order to exit you need to power the generator and find the combination."));
    }
    if (currentRoom->shortDesc() == "O" && myItems->getItem(1)->getItemName() == currentTask->getRequiredItem().getItemName() && !allTask[2]->checkComplete()){
        checkTask(3);
        ui->textBox->setText(QString::fromStdString("The generator roars to life!"));
    }
    if (currentRoom->shortDesc() == "T" && myItems->getItem(2)->getItemName() == currentTask->getRequiredItem().getItemName() && !allTask[3]->checkComplete()){
        currentTask->setTaskComplete(true);
        checkTask(4);
        ui->textBox->setText(QString::fromStdString("You have escaped. GAME COMPLETE"));
    }
}

/**
 *  Function to define what happens when button B is clicked.
 *  buttonB is defined as the take item button, used to pick up an item.
 */
void MainWindow::on_buttonB_clicked()
{
    //If current room has item
    if(currentRoom->checkItem()){
        if (currentRoom->getItemFromRoom()->getItemName() == "Key"){
            myItems->addItem(currentRoom->getItemFromRoom(), 0);
            ui->terminal_Item1->setText(QString::fromStdString("Key"));
        }
        else if(currentRoom->getItemFromRoom()->getItemName() == "Fuel"){
            myItems->addItem(currentRoom->getItemFromRoom(), 1);
            ui->terminal_Item2->setText(QString::fromStdString("Fuel"));
        }
        else if(currentRoom->getItemFromRoom()->getItemName() == "Combination"){
            myItems->addItem(currentRoom->getItemFromRoom(), 2);
            ui->terminal_Item3->setText(QString::fromStdString("Combination"));
        }
        currentRoom->setHasItem(false);
    }
    else{ //Error message if buttonB is clicked and no item is present in room
        ui->textBox->setText(QString::fromStdString("There is no item present in this room!"));
    }   
}
