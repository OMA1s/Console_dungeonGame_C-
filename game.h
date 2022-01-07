#include "dungeon.h"
#include "player.h"

#include <vector>

#ifndef GAME_H
#define GAME_H

class Game{
    private:
    Dungeon *dungeon;
    Player *player;

    public:
    bool isGameOver;
    std::vector<std::string> getMovementActions();
    void handleMovementActions();
    void printActions(std::vector<std::string>);
    void initiateRoomSequence();
    void handleEnemyActions();
    void engageInCombate();
    void handleItemActions();
    Game(Player *, Dungeon *);
};







#endif