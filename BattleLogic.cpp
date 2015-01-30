#include "BattleLogic.h"


BattleLogic::BattleLogic(Item inItem, Enemy inEnemy, Character* inCharacter)
{



    if(inItem.isWeapon())
    {
        battRes = 0;
        inEnemy.setHealth(inEnemy.getHealth()-inItem.getPower());
        returnMessage = "Nice hit!";
    }
    else if(inItem.isEdible())
    {
        battRes = 1;
        inCharacter->setHealth(inCharacter->getHealth() + inItem.getPower());
        returnMessage = "Your snack restored health.";
    }

    //when enemy is defeated
    if(inEnemy.getHealth() == 0)
    {
        battRes = 2;
        returnMessage = "Enemy has been defeated.";
    }
}


int BattleLogic::getBattRes()
{
    return battRes;
}

QString BattleLogic::getMessage()
{
    return returnMessage;
}
