#include "Player.h"
#pragma once
#include <string>

#define START 0

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
