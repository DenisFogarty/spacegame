#ifndef ENEMY_H
#define ENEMY_H

#include <map>
#include <string>
#include <iostream>
#include <QPixmap>
using namespace std;

class Enemy {
    friend class GameWindow;
    friend class Room;

private:
    string description;
    string longDescription;
    double health;
    float value;
    int attack;
    int defence;
    QPixmap* enemy_view;

    QPixmap* getEnemyImage();
    Enemy (string description, int health, float value, int attack, int defence, QPixmap* image);
    Enemy ();
    string getShortDescription();
    string getLongDescription();
    double getHealth();
    void setHealth(int inHealth);
    float getValue();
    void setValue(float value);
    int getAttack();
    void setAttack(int inAttack);
    int getDefence();
    void setDefence(int inDefence);
    int maxHealth;
};

#endif // ENEMY_H
