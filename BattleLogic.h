#ifndef BATTLELOGIC_H
#define BATTLELOGIC_H

#include "Item.h"
#include "Enemy.h"
#include "Character.h"
#include <QString>

using namespace std;

class BattleLogic {
private:
    QString returnMessage;
    int battRes;

public:

    BattleLogic (Item inItem, Enemy inEnemy, Character* inCharacter);
    void enemyTurn();
    QString getMessage();
    int getBattRes();
};

#endif // BATTLELOGIC_H
