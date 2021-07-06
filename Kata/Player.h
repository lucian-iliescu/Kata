#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#define START 0
#define FINISH 63
#define BRIDGE 6
#include <string>
#include <vector>

class Player
{
	private:
		int position;
		std::vector<int> geese;
	public:
		std::string name;
		Player();
		Player(std::string name);
		void move(int dice_one, int dice_two);
		bool isGoose(int space);
		int setPosition(int position)
		{
			this->position = position;
		}
};

#endif