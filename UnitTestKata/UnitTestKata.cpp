#include "pch.h"
#include "CppUnitTest.h"
#include "../Kata/Game.h"
#include "../Kata/Player.h"
#include "../Kata/Game.cpp"
#include "../Kata/Player.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestKata
{
	TEST_CLASS(UnitTestKata)
	{
	public:
		TEST_METHOD(TestAddPlayer)
		{
			Game* game = Game::getInstance();
			std::string name = "Lucian";
			unsigned oldSize = game->getPlayers().size();
			game->addPlayer(name);
			Assert::AreEqual(oldSize + 1, game->getPlayers().size());
			Assert::AreEqual(name, game->getPlayers()[oldSize].name);
		}
		TEST_METHOD(TestMovePlayer)
		{
			Game* game = Game::getInstance();
			std::string name = "Lucian";
			game->movePlayer(name, 1, 3);
			Assert::AreEqual(4, game->getNames()[name].getPosition());
		}

		TEST_METHOD(TestExactDiceWin)
		{
			Game* game = Game::getInstance();
			std::string name = "Winner";
			game->addPlayer(name);
			game->movePlayer(name, 60, 3);
			Assert::AreEqual(FINISH, game->getNames()[name].getPosition());
		}

		TEST_METHOD(TestBounce)
		{
			Game* game = Game::getInstance();
			std::string name = "Bouncer";
			int bouncedDestination = 58;
			game->addPlayer(name);
			game->movePlayer(name, 60, 2);
			game->movePlayer(name, 1, 5);
			Assert::AreEqual(bouncedDestination, game->getNames()[name].getPosition());
		}
		TEST_METHOD(TestAddPlayerCommand)
		{
			Game* game = Game::getInstance();
			std::string name = "Winner";
			game->addPlayer(name);
			game->movePlayer(name, 60, 3);
			Assert::AreEqual(FINISH, game->getNames()[name].getPosition());
		}

		TEST_METHOD(TestClearMethod)
		{
			Game* game = Game::getInstance();
			unsigned expected = 0;
			game->clearPlayers();
			Assert::AreEqual(expected, game->getPlayers().size());
		}

		TEST_METHOD(TestAddComand)
		{
			Game* game = Game::getInstance();
			unsigned expected = 1;
			std::string name = "Jim";
			std::string command = "add player " + name;
			game->clearPlayers();
			game->executeCommand(command);
			Assert::AreEqual(expected, game->getPlayers().size());
			Assert::AreEqual(name, game->getPlayers()[0].name);
		}

		TEST_METHOD(TestMoveCommand)
		{
			Game* game = Game::getInstance();
			std::string name = "Random";
			std::string command = "move player " + name;
			game->addPlayer(name);
			game->executeCommand(command);
			Assert::AreNotEqual(START, game->getNames()[name].getPosition());
		}

		TEST_METHOD(TestBridge)
		{
			Game* game = Game::getInstance();
			std::string name = "Bridger";
			std::string command = "add player " + name;
			int expected = 12;
			game->executeCommand(command);
			game->movePlayer(name, 3, 3);
			Assert::AreEqual(expected, game->getNames()[name].getPosition());
		}

		TEST_METHOD(TestGoose)
		{
			Game* game = Game::getInstance();
			std::string name = "Goose";
			std::string command = "add player " + name;
			int expected = 10;
			game->executeCommand(command);
			game->movePlayer(name, 2, 3);
			Assert::AreEqual(expected, game->getNames()[name].getPosition());
		}

		TEST_METHOD(TestDoubleGoose)
		{
			Game* game = Game::getInstance();
			std::string name = "DoubleGoose";
			std::string command = "add player " + name;
			int expected = 22;
			game->executeCommand(command);
			game->movePlayer(name, 2, 3);
			game->movePlayer(name, 1, 3);
			Assert::AreEqual(expected, game->getNames()[name].getPosition());
		}

		TEST_METHOD(TestSimplePrank)
		{
			Game* game = Game::getInstance();
			game->clearPlayers();
			std::string playerOne = "Prankster";
			std::string commandOne = "add player " + playerOne;
			std::string playerTwo = "Target";
			std::string commandTwo = "add player " + playerTwo;
			int expected = 7;
			int initial = 3;
			game->executeCommand(commandOne);
			game->executeCommand(commandTwo);
			game->movePlayer(playerOne, 1, 2);
			game->movePlayer(playerTwo, 4, 3);
			game->movePlayer(playerOne, 2, 2);
			Assert::AreEqual(expected, game->getNames()[playerOne].getPosition());
			Assert::AreEqual(initial, game->getNames()[playerTwo].getPosition());
		}

		TEST_METHOD(TestBridgePrank)
		{
			Game* game = Game::getInstance();
			game->clearPlayers();
			std::string playerOne = "Prankster";
			std::string commandOne = "add player " + playerOne;
			std::string playerTwo = "Target";
			std::string commandTwo = "add player " + playerTwo;
			int expected = 12;
			game->executeCommand(commandOne);
			game->executeCommand(commandTwo);
			game->movePlayer(playerTwo, 6, 6);
			game->movePlayer(playerOne, 4, 2);
			Assert::AreEqual(expected, game->getNames()[playerOne].getPosition());
			Assert::AreEqual(BRIDGE, game->getNames()[playerTwo].getPosition());
		}

		TEST_METHOD(TestGoosePrank)
		{
			Game* game = Game::getInstance();
			game->clearPlayers();
			std::string playerOne = "Prankster";
			std::string commandOne = "add player " + playerOne;
			std::string playerTwo = "Target";
			std::string commandTwo = "add player " + playerTwo;
			int expected = 29;
			int goose = 27;
			game->executeCommand(commandOne);
			game->executeCommand(commandTwo);
			game->movePlayer(playerOne, 24, 1);
			game->movePlayer(playerTwo, 29, 0);
			game->movePlayer(playerOne, 1, 1);
			Assert::AreEqual(expected, game->getNames()[playerOne].getPosition());
			Assert::AreEqual(goose, game->getNames()[playerTwo].getPosition());
		}
	};
}
