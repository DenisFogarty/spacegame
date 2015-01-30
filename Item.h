#ifndef ITEM_H_
#define ITEM_H_

#include <map>
#include <string>
#include <iostream>
#include <QSound>
using namespace std;

class Item {
    friend class GameWindow;
    friend class Room;
    friend class Character;

private:
    string description;
    string longDescription;
    bool edibleCheck;
    bool weaponCheck;
    int power;

    Item (string inDescription, bool inEdible, bool inWeapon, int inPower, QSound *sound);
    Item ();
    Item (string description);
    string getShortDescription();
    string getLongDescription();
    bool isEdible();
    bool isWeapon();
    int getPower();
    void setPower(int inPower);
    void weaponSound();
    QSound *playSound;

};

#endif /*ITEM_H_*/
