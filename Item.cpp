#include "Item.h"

Item::Item (string inDescription, bool inEdible, bool inWeapon, int inPower, QSound *sound) {
    description = inDescription;
    edibleCheck = inEdible;
    weaponCheck = inWeapon;
    setPower(inPower);
    playSound = sound;
}

Item::Item ()
{
    description = "null";
    edibleCheck = false;
    weaponCheck = false;
    setPower(0);
}

Item::Item(string inDescription) {
    description = inDescription;
}

bool Item::isEdible(){
    return edibleCheck;
}

bool Item::isWeapon(){
    return weaponCheck;
}

void Item::setPower(int inPower)
{
    if(inPower > 9999 || inPower < 0)
        power = inPower;
    else
        power = inPower;
}

int Item::getPower()
{
    return power;
}

string Item::getShortDescription()
{
    return description;
}

string Item::getLongDescription()
{
    return " item(s), " + description + ".\n";
}

void Item::weaponSound()
{
    playSound->play();
}
