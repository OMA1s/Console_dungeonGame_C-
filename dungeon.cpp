#include "dungeon.h"

void Dungeon::setUpDungeon()
{
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            room room;
            room.row = r;
            room.col = c;
            rooms[r][c] = room;
        }
    }

    GameCharacter bat = GameCharacter("Bat", 20, 5);
    GameCharacter rat = GameCharacter("Rat", 20, 10);
    GameCharacter troll = GameCharacter("Troll", 100, 10);

    rooms[2][1].enemies.push_back(bat);
    rooms[1][2].enemies.push_back(rat);
    rooms[0][0].enemies.push_back(troll);

    item healingPotion;
    healingPotion.name = "Healing Potion";
    healingPotion.health = 20;
    healingPotion.damage = 0;

    item sword;
    sword.name = "Sword";
    sword.damage = 20;
    sword.health = 0;

    rooms[1][1].items.push_back(healingPotion);
    rooms[0][2].items.push_back(sword);
}