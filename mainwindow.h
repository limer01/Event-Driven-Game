#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "room.h"
#include "task.h"
#include "items.h"
#include "backpack.h"
#include "delete.h"


#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <string>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setup();


private slots:

    void on_north_clicked();

    void on_east_clicked();

    void on_south_clicked();

    void on_west_clicked();

    void on_teleport_clicked();

    void on_displayTask_clicked();

    void on_buttonA_clicked();

    void on_buttonB_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Room *currentRoom;
    Room *itemRoom[2];
    Task *currentTask;
    Task *allTask[4];
    Backpack *myItems;
    string taskText;
    string roomText;
    vector<QString> roomDescriptions;
    vector<Room*> rooms;
    const string imageLocation = "qrc:/images/map.png";
    const string textFileLocation = "qrc:/text/";
    void createRooms();
    void setTasks();
    void goRoom(string direction);
    void checkTask(int a);
    void readFile(QString file, vector<QString>* v, int size);
    void getRoomDescription();

};

#endif // MAINWINDOW_H
