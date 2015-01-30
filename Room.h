#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include <QPixmap>
#include "Item.h"
#include "Enemy.h"
using namespace std;
using std::vector;

class Room {
    friend class GameWindow;

private:

    map<string, Room*> exits;
    string exitString();

    vector <Item> itemsInRoom;
    vector <Enemy> enemysInRoom;

    string description;
    QPixmap* room_view;
    QPixmap *getRoomImage();
    int numberOfItems();
    int numberOfEnemys();
    Room(string description, QPixmap *room_view);
    void setExits(Room *north, Room *east, Room *south, Room *west, Room *up, Room *down);
    string shortDescription();
    string longDescription();
    Room* nextRoom(string direction);
    void addItem(Item *inItem);
    string displayItem();
    void addEnemy(Enemy *inEnemy);
    string displayEnemy();
    void setRoomImage(string room_image);
    int isItemInRoom(string inString);
    void removeItemFromRoom(int location);
    int isEnemyInRoom(string inString);
    void removeEnemyFromRoom(int location);
    string getItemName(int i);
    int getItemPower(int i);
    string getEnemyName(int i);
    int getEnemyAttack(int i);
    int getEnemyDefence(int i);
    int getEnemyHealth(int i);
};

#endif
