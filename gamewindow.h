#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "Character.h"
#include "Room.h"
#include "Item.h"
#include "Enemy.h"
#include "BattleLogic.h"
#include <iostream>
#include <string>
#include <QPixmap>
#include <QString>
#include <QPushButton>
#include <QMovie>
#include <QSound>
#include <QAudioOutput>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    friend class MainWindow;
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

private Q_SLOTS:
    void finish() ;

private slots:

    void on_north_butt_clicked();

    void on_east_butt_clicked();

    void on_west_butt_clicked();

    void on_south_butt_clicked();

    void on_map_butt_clicked(bool checked);

    void on_down_butt_clicked();

    void on_up_butt_clicked();

    void on_activate_clicked();

    void on_room_items_doubleClicked(const QModelIndex &index);

    void on_run_butt_clicked();

    void on_inventory_clicked(const QModelIndex &index);

    void on_use_item_butt_clicked();


    void on_build_energy_clicked();

    void on_block_butt_clicked();

private:
    void play();
    string go(string direction);
    bool power;
    bool timeToGo ;
    QMovie *movie ;

    Ui::GameWindow *ui;
    void imageSetup(QPushButton* pb, QPixmap* pixmap);
    void setRoomImage();
    void setMapImage();

    void createRooms();
    void printWelcome();
    void printHelp();
    void createItems();
    void displayItems();
    void createEnemys();
    void displayEnemys();
    void addItemToWindow();
    void setBars();
    void gameOver();
    int battlePhase();
    void enemyTurn(string myMove);
    void setBattleView(bool battleInd);

    Room *currentRoom;
    Room *previousRoom;
    string dir;
    int currentLevel;
    int battleItemPos;
    bool inBattle;
    Character *character;
    Item selectedItem;
    QString finalOutputMessage;
    bool powerCellIn ;
    QSound *sound;
    QAudioOutput *audio;
    QTimer *timer;

    Room *Cockpit, *Toilet, *Closet, *Hall_1, *Power, *Elevator_1, *Escape_Pod;
    Room *Bed_1, *Bed_2, *Bed_3, *Bed_4, *Hall_2, *Hall_3, *Elevator_2, *Kitchen;
    Room *Weapons, *Elevator_3, *Engines;

};

#endif // GAMEWINDOW_H
