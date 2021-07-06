#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "Player.h"


std::string getNameFromCommand(std::string command) {
    std::stringstream splitter(command);
    std::string word;
    while (splitter >> word) {}
    return word;
}

int main()
{
    std::vector<Player> players;
    std::map<std::string, Player> names;
    int current_player = 0;

    while (true)
    {
        std::string command;
        std::getline(std::cin, command);
        if (command.substr(0, 3) == "add")
        {
            std::string name = getNameFromCommand(command);
            if (names.find(name) == names.end())
            {
                Player new_player(name);
                names[name] = new_player;
                players.push_back(new_player);
                std::cout << "players: ";
                std::cout << players[0].name;
                for (unsigned i = 1; i < players.size(); i++) {
                    std::cout << ", " << players[i].name;
                }
                std::cout << std::endl;
            }
            else
            {
                std::cout << name << ": already existing player" << std::endl;
            }
        }
        else if (command.substr(0, 4) == "move") {
            std::string name = getNameFromCommand(command);
            int diceOne = rand() % 6 + 1;
            int diceTwo = rand() % 6 + 1;
            names[name].move(diceOne, diceTwo);
        }
    }
}

