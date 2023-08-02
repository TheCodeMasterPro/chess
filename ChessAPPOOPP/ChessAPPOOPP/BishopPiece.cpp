#include "BishopPiece.h"
#include "Board.h"
#include <math.h>

BishopPiece::BishopPiece(const char& type, Board* board) : ChessPiece(type, board) {}

bool BishopPiece::isValidMove(const string& move)
{
	// example: for 'c6d5'
	int xSrc = move[0];   // c
	int ySrc = move[1];   // 6
	int xDest = move[2];  // d
	int yDest = move[3];  // 5
	int x = 0;
	int y = 0;
	string tmp = "";
	if (abs(xSrc - xDest) == abs(ySrc - yDest))
	{
		int xDirection = (xDest - xSrc > 0) ? 1 : -1;
		int yDirection = (yDest - ySrc > 0) ? 1 : -1;
		for (y = ySrc + yDirection, x = xSrc + xDirection; (yDirection == 1) ? y < yDest : y > yDest; y += yDirection, x += xDirection)
		{
			tmp = "";
			tmp += (char)x;
			tmp += (char)y;
			if (_board->getPieceByIdx(tmp) != nullptr)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool BishopPiece::isValidMove(const Board* board, const string& move)
{
	// example: for 'c6d5'
	int xSrc = move[0];   // c
	int ySrc = move[1];   // 6
	int xDest = move[2];  // d
	int yDest = move[3];  // 5
	int x = 0;
	int y = 0;
	string tmp = "";
	if (abs(xSrc - xDest) == abs(ySrc - yDest))
	{
		int xDirection = (xDest - xSrc > 0) ? 1 : -1;
		int yDirection = (yDest - ySrc > 0) ? 1 : -1;
		for (y = ySrc + yDirection, x = xSrc + xDirection; (yDirection == 1) ? y < yDest : y > yDest; y += yDirection, x += xDirection)
		{
			tmp = "";
			tmp += (char)x;
			tmp += (char)y;
			if (board->getPieceByIdx(tmp) != nullptr)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}
