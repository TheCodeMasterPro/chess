#include "Game.h"

Game::Game(const string& start) : _board(start) 
{
	this->_start = start;
}

string Game::getMove()
{
	return this->_p.getMessageFromGraphics();
}

void Game::sendCode(MoveCodes moveCode)
{
	char msgToSend[1024];
	msgToSend[0] = moveCode;
	msgToSend[1] = NULL;
	this->_p.sendMessageToGraphics(msgToSend);
}

void Game::runGame()
{
	this->startGame();
	MoveCodes code;

	// get message from graphics
	string moveMsg = this->getMove();

	while (moveMsg != "quit")
	{
		// should handle the string the sent from graphics
		// according the protocol. Ex: e2e4           (move e2 to e4)
		ChessPiece* tmp;
		cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
		for (int i = 0; i < BOARD_SIDE; i++)
		{
			for (int j = 0; j < BOARD_SIDE; j++)
			{
				tmp = this->_board.getPieceByIdx(j, i);
				if (tmp == nullptr)
				{
					cout << "#";
				}
				else
				{
					cout << tmp->getType();
				}
			}
			cout << endl;
		}
		code = _board.move(moveMsg);
		cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
		for (int i = 0; i < BOARD_SIDE; i++)
		{
			for (int j = 0; j < BOARD_SIDE; j++)
			{
				tmp = this->_board.getPieceByIdx(j, i);
				if (tmp == nullptr)
				{
					cout << "#";
				}
				else
				{
					cout << tmp->getType();
				}
			}
			cout << endl;
		}
		this->sendCode(code);
		if (code == ValidMove || code == ValidMoveDoneChess || code == ValidMove)
		{
			this->_board.setIsWhiteTurn(!this->_board.getIsWhiteTurn());
		}
		// get message from graphics
		moveMsg = this->getMove();

	}
	this->endGame();
}

void Game::startGame()
{
	bool isConnect = this->_p.connect();
	string ans;
	char msgToGraphics[1024];

	srand(time_t(NULL));
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = this->_p.connect();
		}
		else
		{
			this->_p.close();
			return;
		}
	}
	strcpy_s(msgToGraphics, this->_start.c_str()); // "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR1"
	this->_p.sendMessageToGraphics(msgToGraphics);   // send the board string
}

void Game::endGame()
{
	this->_p.close();
}
