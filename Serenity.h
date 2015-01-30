#ifndef SERENITY_H
#define SERENITY_H


#include "Command.h"
#include "Parser.h"
#include "Room.h"
#include "item.h"
#include <iostream>
#include <string>
using namespace std;

class Serenity {
private:
    Parser parser;
    Room *currentRoom;
    void createRooms();
    void printWelcome();
    inline bool processCommand(Command command);
    void printHelp();
    void goRoom(Command command);
    void eatFood(Command command);
    void createItems();
    void displayItems();

public:
    Serenity();
    void play();
    string go(string direction);
};

#endif // SERENITY_H
