#include <iostream>

using namespace std;
#include "Serenity.h"

int main(int argc, char argv[]) {
    Serenity temp;
    temp.play();
    return 0;
}

Serenity::Serenity() {
    createRooms();
}

void Serenity::createRooms() {
    Room *a, *b, *c, *d, *e;

    a = new Room("elevator");
    b = new Room("weapons");
        b->addItem(new Item("lazer gun", 3, 33, 0));
        b->addItem(new Item("cake", 4, 44, 6));
    c = new Room("c");
    d = new Room("d");
    e = new Room("engine room");

//             (N, E, S, W)
    a->setExits(NULL, NULL, b, NULL);
    b->setExits(a, d, e, c);
    c->setExits(NULL, b, NULL, NULL);
    d->setExits(NULL, NULL, NULL, b);
    e->setExits(b, NULL, NULL, NULL);

        currentRoom = a;
}

/**
 *  Main play routine.  Loops until end of play.
 */
void Serenity::play() {
    printWelcome();

    // Enter the main command loop.  Here we repeatedly read commands and
    // execute them until the ZorkUL game is over.

    bool finished = false;
    while (!finished) {
        // Create pointer to command and give it a command.
        Command* command = parser.getCommand();
        // Pass dereferenced command and check for end of game.
        finished = processCommand(*command);
        // Free the memory allocated by "parser.getCommand()"
        //   with ("return new Command(...)")
        delete command;
    }
    cout << endl;
    cout << "end" << endl;
}

void Serenity::printWelcome() {
    cout << "start"<< endl;
    cout << "info for help"<< endl;
    cout << endl;
    cout << currentRoom->longDescription() << endl;
}

/**
 * Given a command, process (that is: execute) the command.
 * If this command ends the ZorkUL game, true is returned, otherwise false is
 * returned.
 */
inline bool Serenity::processCommand(Command command) {
    if (command.isUnknown()) {
        cout << "invalid input"<< endl;
        return false;
    }

    string commandWord = command.getCommandWord();
    if (commandWord.compare("info") == 0)
        printHelp();

    else if (commandWord.compare("map") == 0)
        {
        cout << "       [elevator]      " << endl;
        cout << "           |           " << endl;
        cout << "           |           " << endl;
        cout << "[c] -- [weapons] -- [d]" << endl;
        cout << "           |           " << endl;
        cout << "           |           " << endl;
        cout << "       [engines]       " << endl;
        }
    else if (commandWord.compare("eat") == 0){
    }


    else if (commandWord.compare("go") == 0)
        goRoom(command);

    else if (commandWord.compare("take") == 0)
    {
        if (!command.hasSecondWord()) {
        cout << "incomplete input"<< endl;
        }
        else
         if (command.hasSecondWord()) {
        cout << "You're trying to take the " + command.getSecondWord() + "."<< endl;
        int location = currentRoom->isItemInRoom(command.getSecondWord());
        if (location  < 0 )
            cout << "item is not in room" << endl;
        else
            cout << "item is in room" << endl;
            cout << "index number " << + location << endl;
            cout << endl;
            cout << currentRoom->longDescription() << endl;
        }
    }

    else if (commandWord.compare("put") == 0)
    {

    }
    /*
    {
    if (!command.hasSecondWord()) {
        cout << "incomplete input"<< endl;
        }
        else
            if (command.hasSecondWord()) {
            cout << "you're adding " + command.getSecondWord() << endl;
            itemsInRoom.push_Back;
        }
    }
*/
    else if (commandWord.compare("quit") == 0) {
        if (command.hasSecondWord())
            cout << "overdefined input"<< endl;
        else
            return true; /**signal to quit*/
    }
    return false;
}
/** COMMANDS **/
void Serenity::printHelp() {
    cout << "valid inputs are; " << endl;
    parser.showCommands();

}

void Serenity::eatFood(Command command) {


}

void Serenity::goRoom(Command command) {
    if (!command.hasSecondWord()) {
        cout << "incomplete input"<< endl;
        return;
    }

    string direction = command.getSecondWord();

    // Try to leave current room.
    Room* nextRoom = currentRoom->nextRoom(direction);

    if (nextRoom == NULL)
        cout << "underdefined input"<< endl;
    else {
        currentRoom = nextRoom;
        cout << currentRoom->longDescription() << endl;
    }
}

string Serenity::go(string direction) {
    //Make the direction lowercase
    //transform(direction.begin(), direction.end(), direction.begin(),:: tolower);
    //Move to the next room
    Room* nextRoom = currentRoom->nextRoom(direction);
    if (nextRoom == NULL)
        return("direction null");
    else
    {
        currentRoom = nextRoom;
        return currentRoom->longDescription();
    }
}

