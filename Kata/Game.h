#pragma once
#ifndef GAME_H
#define GAME_H

#include <vector>
#include <map>
#include <string>
#include "Player.h"

class Game
{
	private:
		std::vector<Player> players;
		std::vector<int> geese;
		std::map<std::string, Player> names;
		static Game* instance;
		Game();
	public:
		static Game* getInstance();
		void addPlayer(std::string name);
		void movePlayer(std::string name, int diceOne, int diceTwo);
		void executeCommand(std::string command);
		void clearPlayers();
		std::string getNameFromCommand(std::string command);
		std::string getPlayerFromSpace(int space);
		bool isGoose(int space);
		std::vector<Player> getPlayers() {
			return this->players;
		};
		std::map<std::string, Player> getNames() {
			return this->names;
		}
};

#endif