/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project, 
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include <iostream>
#include <thread>
#include "Game.h"

using std::cout;
using std::endl;
using std::string;


int main()
{
	Game session("rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR0");
	session.runGame();
	return 0;
}