#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "Player.h"
#include "Game.h"

int main()
{
    std::vector<Player> players;
    std::map<std::string, Player> names;
    Game* game = Game::getInstance();

    while (true)
    {
        std::string command;
        std::getline(std::cin, command);
        game->executeCommand(command);
    }
}

