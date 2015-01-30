#include "Room.h"

Room::Room(string description, QPixmap* room_view) {

    this->description = description;
    this->room_view = room_view;
}

void Room::setExits(Room *north, Room *east, Room *south, Room *west, Room *up, Room *down) {
    if (north != NULL)
        exits["north"] = north;
    if (east != NULL)
        exits["east"] = east;
    if (south != NULL)
        exits["south"] = south;
    if (west != NULL)
        exits["west"] = west;
    if (up != NULL)
        exits["up"] = up;
    if (down != NULL)
        exits["down"] = down;
}

QPixmap* Room::getRoomImage() {
    return room_view;
}

string Room::shortDescription() {
    return description;
}

string Room::longDescription() {
    return "You are now in " + description + ".\n" + displayItem() + exitString();
}

string Room::exitString() {
    string returnString = "\nexits =";
    for (map<string, Room*>::iterator i = exits.begin(); i != exits.end(); i++)
        // Loop through map
        returnString += "  " + i->first;	// access the "first" element of the pair (direction as a string)
    return returnString;
}

Room* Room::nextRoom(string direction) {
    map<string, Room*>::iterator next = exits.find(direction); //returns an iterator for the "pair"
    if (next == exits.end())
        return NULL; // if exits.end() was returned, there's no room in that direction.
    return next->second; // If there is a room, remove the "second" (Room*)
                // part of the "pair" (<string, Room*>) and return it.
}

void Room::addItem(Item *inItem) {
    itemsInRoom.push_back(*inItem);
}

string Room::displayItem() {
    string tempString = "items in room = ";
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1) {
        tempString = "no items in room";
        }
    else if (itemsInRoom.size() > 0) {
       int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            tempString = tempString + itemsInRoom[x].getShortDescription() + "  " ;
            x++;
            }
        }
    return tempString;
    }

int Room::numberOfItems() {
    return itemsInRoom.size();
}

int Room::isItemInRoom(string inString)
{
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1) {
        return false;
        }
    else if (itemsInRoom.size() > 0) {
       int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            // compare inString with short description
            int tempFlag = inString.compare( itemsInRoom[x].getShortDescription());
            if (tempFlag == 0) {
                itemsInRoom.erase(itemsInRoom.begin()+x);
                return x;
            }
            x++;
            }
        }
    return -1;
}

//Below are the functions for adding
//Enemies to rooms, as well as other
//enemy stuff.

void Room::addEnemy(Enemy *inEnemy)
{
    enemysInRoom.push_back(*inEnemy);
}

string Room::displayEnemy() {
    string tempString = " An enemy ";
    int sizeEnemys = (enemysInRoom.size());
    if (enemysInRoom.size() < 1) {
        tempString = "no items in room";
        }
    else if (enemysInRoom.size() > 0) {
       int x = (0);
        for (int n = sizeEnemys; n > 0; n--) {
            tempString = tempString + enemysInRoom[x].getShortDescription() + " has spotted you! " ;
            x++;
            }
        }
    return tempString;
}

int Room::numberOfEnemys() {
    return enemysInRoom.size();
}

int Room::isEnemyInRoom(string inString)
{
    int sizeEnemys = (enemysInRoom.size());
    if (enemysInRoom.size() < 1) {
        return false;
        }
    else if (enemysInRoom.size() > 0) {
       int x = (0);
        for (int n = sizeEnemys; n > 0; n--) {
            // compare inString with short description
            int tempFlag = inString.compare( enemysInRoom[x].getShortDescription());
            if (tempFlag == 0) {
                enemysInRoom.erase(enemysInRoom.begin()+x);
                return x;
            }
            x++;
            }
        }
    return -1;
}

string Room::getItemName(int i)
{
    string name;
    name = itemsInRoom[i].getShortDescription();
    return name;
}

int Room::getItemPower(int i)
{
    int power;
    power = itemsInRoom[i].getPower();
    return power;
}

string Room::getEnemyName(int i)
{
    string name;
    name = enemysInRoom[i].getShortDescription();
    return name;
}

int Room::getEnemyHealth(int i)
{
    int health;
    health = enemysInRoom[i].getHealth();
    return health;
}

int Room::getEnemyAttack(int i)
{
    int attack;
    attack = enemysInRoom[i].getAttack();
    return attack;
}

int Room::getEnemyDefence(int i)
{
    int defence;
    defence = enemysInRoom[i].getDefence();
    return defence;
}
