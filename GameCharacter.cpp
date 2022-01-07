#include "GameCharacter.h"

GameCharacter::GameCharacter(std::string _name, int _health, int _damage) : name(_name), maxHealth(_health), damage(_damage){
    currentHealth = _health;
}

void GameCharacter::takeDamage(int _dmg)
{
    currentHealth -= _dmg;
}

bool GameCharacter::checkIfAlive()
{
    return currentHealth > 0;
}

int GameCharacter::getHealth()
{
    return currentHealth;
}

int GameCharacter::getDamage()
{
    return damage;
}

std::string GameCharacter::getName()
{
    return name;
}