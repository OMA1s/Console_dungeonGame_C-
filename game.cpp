#include "game.h"
#include <iostream>

Game::Game(Player *_player, Dungeon *_dungeon) : player(_player), dungeon(_dungeon)
{
    isGameOver = false;

    dungeon->setUpDungeon();
    player->currentRoom = &dungeon->rooms[dungeon->rows - 1][dungeon->cols - 1];
}

std::vector<std::string> Game::getMovementActions()
{
    std::vector<std::string> actions;
    room *currentRoom = player->currentRoom;
    if (currentRoom->col > 0)
    {
        actions.push_back("Move Left");
    }
    if (currentRoom->row > 0)
    {
        actions.push_back("Move Up");
    }
    if (currentRoom->row < dungeon->rows - 1)
    {
        actions.push_back("Move Down");
    }
    if (currentRoom->col < dungeon->cols - 1)
    {
        actions.push_back("Move Right");
    }
    return actions;
}

void Game::handleMovementActions()
{
    std::cout<<"Your current room is "<<player->currentRoom->row<<" "<<player->currentRoom->col<<std::endl;
    std::cout<<"Where do you want to move next?"<<std::endl;
    std::vector<std::string> actions = getMovementActions();
    printActions(actions);
    
    int input;
    std::cin>> input;
    std::string chosenAction = actions[input - 1];

    int horizontalMovement = 0;
    int verticalMovement = 0;
    if (chosenAction == "Move Left")
    {
        horizontalMovement = -1;
    }
    else if (chosenAction == "Move Right")
    {
        horizontalMovement = 1;
    }
    else if (chosenAction == "Move Up")
    {
        verticalMovement = -1;
    }
    else if (chosenAction == "Move Down")
    {
        verticalMovement = 1;
    }

    room *newRoom = &dungeon->rooms[player->currentRoom->row + verticalMovement][player->currentRoom->col + horizontalMovement];
    player->moveToRoom(newRoom);
    std::cout<<"You are now in room "<<newRoom->row<<" "<<newRoom->col<<std::endl;
}

void Game::initiateRoomSequence()
{
    room *plyroom = player->currentRoom;
    if (plyroom->row == 0 && plyroom->col == 0 && plyroom->enemies.empty())
    {
        std::cout<<"Congrats, you defeated final boss "<<player->getName()
        <<"GL on your coding journey!!!";
        isGameOver = true;
        return;
    }

    if (!plyroom->enemies.empty())
    {
        handleEnemyActions();
    }
    else if (!plyroom->items.empty())
    {
        handleItemActions();
    }
    else
    {
        handleMovementActions();
    }
    
}

void Game::printActions(std::vector<std::string> actions)
{
    int count = 1;
    for (auto &&action : actions)
        {
            std::cout<<count<<". "<<action<<std::endl;
            count++;
        }
}

void Game::handleEnemyActions()
{
    std::cout<<"There is an enemy "<<player->currentRoom->enemies[0].getName() <<
    " in this room! What would you like to do?\n";
    std::vector<std::string> actions;
    actions.push_back("Engage enemy");
    actions.push_back("Retreat");
    printActions(actions);

    int input;
    std::cin>>input;
    if (input == 1)
    {
        engageInCombate();
    }
    else
    {
        player->retreat();
    }
}

void Game::engageInCombate()
{
    GameCharacter *enemy = &player->currentRoom->enemies[0];
    while (true)
    {
        enemy->takeDamage(player->getDamage());
        std::cout<<"You struck "<<enemy->getName()<<" and dealt "
        <<player->getDamage()<<" damage.\n";
        std::cout<<enemy->getName()<<" now has "<<enemy->getHealth()<<" remaining.\n";
        if (!enemy->checkIfAlive())
        {
            std::cout<<"You defeated "<<enemy->getName()<<"!\n";
            player->currentRoom->enemies.clear();
            return;
        }
        

        player->takeDamage(enemy->getDamage());
        std::cout<<"You took "<<enemy->getDamage()<<" amount of damage. "
        <<"You now have "<<player->getHealth()<<" health remaining.\n";
        if (!player->checkIfAlive())
        {
            std::cout<<"You have been defeated.\n";
            return;
        }

        std::cout<<"Would you like to keep fighting or retreat?\n";
        std::vector<std::string> actions;
        actions.push_back("Keep Fighting");
        actions.push_back("Retreat");
        printActions(actions);

        int input;
        std::cin>>input;
        if (input != 1)
        {
            player->retreat();
            return;
        }
    }
}

void Game::handleItemActions()
    {
        item it = player->currentRoom->items[0];
        std::cout<<"You found a "<<it.name <<
        " in this room! What would you like to do?\n";
        std::vector<std::string> actions;
        actions.push_back("Use item");
        actions.push_back("Ignore item");
        printActions(actions);

        int input;
        std::cin>>input;
        if (input == 1)
        {
            player->pickItem(it);
            std::cout<<"You picked "<<it.name<<". Your health now is: "<<player->getHealth()
            <<" and your damage now is: "<<player->getDamage()<<"\n";
            player->currentRoom->items.clear();
        }
        else
        {
            handleMovementActions();
        }
    }