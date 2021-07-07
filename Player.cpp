#include "Player.h"
#pragma once
#include <string>

Player::Player()
{
	this->name = "";
	this->position = START;
}

Player::Player(std::string name)
{
	this->name = name;
	this->position = START;
	this->geese.push_back(5);
	this->geese.push_back(9);
	this->geese.push_back(14);
	this->geese.push_back(18);
	this->geese.push_back(23);
	this->geese.push_back(27);
}

void Player::move(int diceOne, int diceTwo)
{
	int destination = this->position + (diceOne + diceTwo);
	printf("%s rolls %d, %d.", this->name.c_str(), diceOne, diceTwo);
	if (this->position == START && destination != BRIDGE)
	{
		printf(" %s moves from start to %d", this->name.c_str(), destination);
		while (isGoose(destination)) {
			this->position = destination;
			destination += (diceOne + diceTwo);
			printf(", The Goose. %s moves again and goes to %d", this->name.c_str(), destination);
		}
		printf(".\n");
	}
	else
	{
		if (destination <= FINISH) {
			if (destination == BRIDGE)
			{
				if (this->position == START)
				{
					printf(" %s moves from start to The Bridge. %s jumps to 12", this->name.c_str(), this->name.c_str());
				}
				else
				{
					printf(" %s moves from %d to The Bridge. %s jumps to 12", this->name.c_str(), this->position, this->name.c_str());
				}
			}
			else
			{
				printf(" %s moves from %d to %d", this->name.c_str(), this->position, destination);
			}
			if (destination < FINISH) {

				while (isGoose(destination)) {
					this->position = destination;
					destination += (diceOne + diceTwo);
					printf(", The Goose. %s moves again and goes to %d", this->name.c_str(), destination);
				}
				printf(".\n");
			}
			else if (destination == FINISH) {
				printf(" %s wins!!\n", this->name.c_str());
			}
		}
		else {
			int overflow = destination - FINISH;
			destination = FINISH - overflow;
			printf(" %s moves from %d to 63.", this->name.c_str(), this->position);
			printf(" %s bounces! %s returns to %d\n", this->name.c_str(), this->name.c_str(), destination);
		}
	}

	this->position = destination;
}

bool Player::isGoose(int space) {
	if (std::find(this->geese.begin(), this->geese.end(), space) != this->geese.end()) {
		return true;
	}
	return false;
}