#include "Character.h"

Character::Character(string inName, int inHealth)
{
    myName = inName;
    maxHealth = 1000;
    setHealth(inHealth);
    XP = 0;
    attack = 500;
    defence = 600;
}

string Character::getName()
{
    return myName;
}

void Character::setHealth(int inHealth)
{
    if (inHealth > maxHealth)
    {
        myHealth = maxHealth;
    }
    else if(inHealth < 0){
        myHealth = 0;
    }else
       myHealth = inHealth;
}

int Character::getHealth()
{
    return myHealth;
}

Item Character::getInventoryItem(int i)
{
    return inventory[i];
}

void Character::addInventoryItem(Item myItem)
{
    inventory.push_back(myItem);
}

bool Character::isItemInInventory(string itemName)
{
    int i;
    int size = inventory.size();
    for(i = 0; i < size; i++)
    {
        if(inventory.at(i).getShortDescription() == itemName)
        {
            return true;
        }
    }
    return false;
}

int Character::deleteItem(string itemName)
{
    int i;
    int size = inventory.size();
    for(i = 0; i < size; i++)
    {
        if(inventory.at(i).getShortDescription() == itemName)
        {
            inventory.erase(inventory.begin() + i) ;
            return i ;
        }
    }
    return -1 ;
}

float Character::getXP()
{
    return XP;
}

void Character::setXP(float points)
{
    XP = points;
}

int Character::getAttack()
{
    return attack;
}

int Character::getDefence()
{
    return defence;
}

void Character::setAttack(int inAttack)
{
    if(inAttack > 1000)
    {
        attack = 1000;
    } else if(inAttack < 0){
        attack = 0;
    } else {
        attack = inAttack;
    }
}


void Character::setDefence(int inDefence)
{
    if(inDefence > 2000)
    {
        defence = 2000;
    } else if(inDefence < 0){
        defence = 0;
    } else {
        defence = inDefence;
    }
}
