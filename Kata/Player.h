#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

class Player
{
	private:
		std::vector<int> geese;
		int position;
	public:
		std::string name;
		Player();
		Player(std::string name);
		void setPosition(int position)
		{
			this->position = position;
		}
		int getPosition()
		{
			return this->position;
		}
};

#endif