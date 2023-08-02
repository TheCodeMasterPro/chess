#pragma once

#include "Board.h"
#include "Pipe.h"
#include <iostream>
#include <thread>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Game
{
public:
	Game(const string& start);
	string getMove();
	void sendCode(MoveCodes moveCode);
	void runGame();
private:
	Board _board;
	Pipe _p;
	string _start;
	void startGame();
	void endGame();
};