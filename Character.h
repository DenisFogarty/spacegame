#ifndef CHARACTER_H
#define CHARACTER_H

#include <map>
#include <string>
#include <vector>
#include "Item.h"
using namespace std;
using std::vector;

class Character
{
    friend class GameWindow;

private:


    string myName;
    int myHealth;
    int maxHealth;
    float XP;
    int attack;
    int defence;

    vector <Item> inventory;
    Character(string inName, int inHealth);

    string getName();
    void setHealth(int inHealth);
    int getHealth();
    string displayInventory();
    Item getInventoryItem(int i);
    void addInventoryItem(Item myItem);
    float getXP();
    void setXP(float points);
    int getAttack();
    void setAttack(int inAttack);
    int getDefence();
    void setDefence(int inDefence);
    bool isItemInInventory(string itemName);
    int deleteItem(string itemName) ;

};

#endif // CHARACTER_H
