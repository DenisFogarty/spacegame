#include "Enemy.h"

Enemy::Enemy (string inDescription, int inHealth, float inValue, int attack, int defence, QPixmap* image) {
    description = inDescription;
    setHealth(inHealth);
    value = inValue;
    setAttack(attack);
    setDefence(defence);
    enemy_view = image;
    maxHealth = inHealth;
}

Enemy::Enemy() {
    description = "null";
}

void Enemy::setHealth(int inHealth)
{
    if (inHealth < 0)
       health = 0;
    else
       health = inHealth;
}

double Enemy::getHealth()
{
    return health;
}

void Enemy::setAttack(int inAttack)
{
    attack = inAttack;
}

int Enemy::getAttack()
{
    return attack;
}

void Enemy::setDefence(int inDefence)
{
    defence = inDefence;
}

int Enemy::getDefence()
{
    return defence;
}

void Enemy::setValue(float inValue)
{
    if (inValue > 9999 || inValue < 0)
       value = inValue;
    else
       value = inValue;
}

float Enemy::getValue()
{
    return value;
}

string Enemy::getShortDescription()
{
    return description;
}

string Enemy::getLongDescription()
{
    return " Enemy(s), " + description + ".\n";
}

QPixmap* Enemy::getEnemyImage()
{
    return enemy_view;
}
