#include <iostream>
#include "game.h"

int main()
{
    Player player = Player("Omais", 100, 10);
    Dungeon dungeon;
    Game game = Game(&player, &dungeon);
    while (!game.isGameOver)
    {
        game.initiateRoomSequence();
    }
}