#include "player.h"

Player::Player(std::string _name, int _health, int _damage) : GameCharacter(_name, _health, _damage){

}

void Player::heal(int amount)
{
    if (currentHealth + amount >= maxHealth)
    {
        currentHealth = maxHealth;
    }
    else
    {
        currentHealth += amount;
    }
}

void Player::moveToRoom(room *newRoom)
{
    previousRoom = currentRoom;
    currentRoom = newRoom;
}

void Player::retreat()
{
    room *tempRoom = currentRoom;
    currentRoom = previousRoom;
    previousRoom = tempRoom;
}

void Player::pickItem(item it)
{
    damage += it.damage;
    heal(it.health);
}