#include "RookPiece.h"
#include "Board.h"

RookPiece::RookPiece(const char& type, Board* board) : ChessPiece(type, board) {}

bool RookPiece::isValidMove(const string& move)
{
	return isValidMove(_board, move);
}

bool RookPiece::isValidMove(const Board* board, const string& move)
{
	string tmp = "";
	// example: for 'a8a2'
	int xSrc = move[0];   // a
	int ySrc = move[1];   // 8
	int xDest = move[2];  // a
	int yDest = move[3];  // 2

	if (xSrc == xDest)
	{
		int direction = (yDest - ySrc > 0) ? 1 : -1;
		for (int y = ySrc + direction; (direction == 1) ? y < yDest : y > yDest; y += direction)
		{
			tmp = "";
			tmp += (char)xSrc;
			tmp += (char)y;
			if (board->getPieceByIdx(tmp) != nullptr)
			{
				return false;
			}
		}
		return true;
	}
	else if (ySrc == yDest)
	{
		int direction = (xDest - xSrc > 0) ? 1 : -1;
		for (int x = xSrc + direction; (direction == 1) ? x < xDest : x > xDest; x += direction)
		{
			tmp = "";
			tmp += (char)x;
			tmp += (char)ySrc;
			if (board->getPieceByIdx(tmp) != nullptr)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}
