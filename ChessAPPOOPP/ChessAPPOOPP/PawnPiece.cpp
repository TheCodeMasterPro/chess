#include "PawnPiece.h"
#include "Board.h"

PawnPiece::PawnPiece(const char& type, Board* board) : ChessPiece(type, board) 
{
	this->isFirstMove = true;
}

bool PawnPiece::isValidMove(const string& move)
{
	// example: for 'c6d5'
	int xSrc = move[0];   // c
	int ySrc = move[1];   // 6
	int xDest = move[2];  // d
	int yDest = move[3];  // 5
	string moveOneIdx = "";
	string moveTwoIdx = "";


	if (this->isFirstMove)
	{
		if (this->_board->getIsWhiteTurn() ? (yDest - ySrc != 1 && yDest - ySrc != 2) : (ySrc - yDest != 1 && ySrc - yDest != 2))
		{
			return false;
		}
	}
	else
	{
		if (this->_board->getIsWhiteTurn() ? (yDest - ySrc != 1) : (ySrc - yDest != 1))
		{
			return false;
		}
	}
	if ((xSrc - xDest != 0) && (this->_board->getIsWhiteTurn() ? (yDest - ySrc == 2) : (ySrc - yDest == 2)))
	{
		return false;
	}
	if (xSrc - xDest != 0 && abs(xSrc - xDest) != 1)
	{
		return false;
	}
	moveOneIdx += xSrc;
	this->_board->getIsWhiteTurn() ? moveOneIdx += ySrc + 1 : moveOneIdx += ySrc - 1;
	if (xSrc - xDest == 0)
	{
		if (this->_board->getPieceByIdx(moveOneIdx) != nullptr)
		{
			return false;
		}
		if (this->_board->getIsWhiteTurn() ? yDest - ySrc == 2 : ySrc - yDest == 2)
		{
			moveTwoIdx += xDest;
			moveTwoIdx += yDest;
			if (this->_board->getPieceByIdx(moveTwoIdx) != nullptr)
			{
				return false;
			}
		}
	}
	else
	{
		if (this->_board->getPieceByIdx(move.substr(2, 2)) == nullptr)
		{
			return false;
		}
	}

	if (this->isFirstMove)
	{
		this->isFirstMove = false;
	}
	return true;
}
