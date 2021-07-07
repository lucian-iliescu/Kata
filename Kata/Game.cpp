#pragma once

#include "Game.h"
#include <string>
#include <iostream>
#include <sstream>

#define START 0
#define FINISH 63
#define BRIDGE 6

Game* Game::instance = nullptr;

Game::Game()
{
    this->geese.push_back(5);
    this->geese.push_back(9);
    this->geese.push_back(14);
    this->geese.push_back(18);
    this->geese.push_back(23);
    this->geese.push_back(27);
}

Game* Game::getInstance() {
    if (instance == nullptr) {
        instance = new Game();
    }
    return instance;
}

void Game::addPlayer(std::string name) 
{
    if (this->names.find(name) == this->names.end())
    {
        Player new_player(name);
        this->names[name] = new_player;
        this->players.push_back(new_player);
        std::cout << "players: ";
        std::cout << this->players[0].name;
        for (unsigned i = 1; i < this->players.size(); i++) {
            std::cout << ", " << this->players[i].name;
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << name << ": already existing player" << std::endl;
    }
}

void Game::movePlayer(std::string name, int diceOne, int diceTwo) {
    int initialPosition = this->names[name].getPosition();
    int destination = initialPosition + (diceOne + diceTwo);
    std::string destinationPlayer = "";
    bool occupiedSpace = false;
    printf("%s rolls %d, %d.", name.c_str(), diceOne, diceTwo);
    if (initialPosition == START && destination != BRIDGE)
    {
        printf(" %s moves from start to %d", name.c_str(), destination);
        while (isGoose(destination)) {
            initialPosition = destination;
            destination += (diceOne + diceTwo);
            if (occupiedSpace)
            {
                occupiedSpace = false;
                if (initialPosition == START)
                    printf(", The Goose. On %d there is %s, who returns to %d. %s moves again and goes to %d", initialPosition, destinationPlayer.c_str(), this->names[destinationPlayer].getPosition(), name.c_str(), destination);
            }
            else
            {
                printf(", The Goose. %s moves again and goes to %d", name.c_str(), destination);
            }
        }
        printf(".");
    }
    else
    {
        if (destination <= FINISH) {
            if (destination == BRIDGE)
            {
                if (initialPosition == START)
                {
                    printf(" %s moves from start to The Bridge. %s jumps to 12", name.c_str(), name.c_str());
                }
                else
                {
                    printf(" %s moves from %d to The Bridge. %s jumps to 12", name.c_str(), initialPosition, name.c_str());
                }
                initialPosition = BRIDGE;
                destination = 12;
            }
            else
            {
                printf(" %s moves from %d to %d", name.c_str(), initialPosition, destination);
            }
            if (destination < FINISH) {

                while (isGoose(destination)) {
                    destinationPlayer = getPlayerFromSpace(destination);
                    if (destinationPlayer != "NO PLAYER") {
                        this->names[destinationPlayer].setPosition(initialPosition);
                        occupiedSpace = true;
                    }
                    initialPosition = destination;
                    destination += (diceOne + diceTwo);
                    if (occupiedSpace)
                    {
                        occupiedSpace = false;
                        printf(", The Goose. On %d there is %s, who returns to %d. %s moves again and goes to %d", initialPosition, destinationPlayer.c_str(), this->names[destinationPlayer].getPosition(), name.c_str(), destination);
                    }
                    else
                    {
                        printf(", The Goose. %s moves again and goes to %d", name.c_str(), destination);
                    }
                }
                printf(".");
            }
            else if (destination == FINISH) {
                printf(" %s wins!!", name.c_str());
            }
        }
        else {
            int overflow = destination - FINISH;
            destination = FINISH - overflow;
            printf(" %s moves from %d to 63.", name.c_str(), initialPosition);
            printf(" %s bounces! %s returns to %d", name.c_str(), name.c_str(), destination);
            destinationPlayer = getPlayerFromSpace(destination);
            if (destinationPlayer != "NO PLAYER") {
                this->names[destinationPlayer].setPosition(initialPosition);
                printf(" On %d there is %s, who returns to %d", destination, destinationPlayer.c_str(), initialPosition);
            }
        }
    }

    destinationPlayer = getPlayerFromSpace(destination);
    if (destinationPlayer != "NO PLAYER") {
        this->names[destinationPlayer].setPosition(initialPosition);
        printf(" On %d there is %s, who returns to %d", destination, destinationPlayer.c_str(), initialPosition);
    }
    printf("\n");
    this->names[name].setPosition(destination);
}

void Game::executeCommand(std::string command)
{
    if (command.substr(0, 3) == "add")
    {
        std::string name = getNameFromCommand(command);
        addPlayer(name);
    }
    else if (command.substr(0, 4) == "move") {
        int diceOne = rand() % 6 + 1;
        int diceTwo = rand() % 6 + 1;
        std::string name = getNameFromCommand(command);
        movePlayer(name, diceOne, diceTwo);
    }
}

void Game::clearPlayers() {
    this->players.clear();
    this->names.clear();
}

std::string Game::getNameFromCommand(std::string command)
{
    std::stringstream splitter(command);
    std::string word;
    while (splitter >> word) {}
    return word;
}

std::string Game::getPlayerFromSpace(int space) {
    for (unsigned i = 0; i < this->players.size(); i++) {
        std::string name = this->players[i].name;
        if (this->names[name].getPosition() == space)
        {
            return name;
        }
    }

    return "NO PLAYER";
}

bool Game::isGoose(int space) {
    if (std::find(this->geese.begin(), this->geese.end(), space) != this->geese.end()) {
        return true;
    }
    return false;
}