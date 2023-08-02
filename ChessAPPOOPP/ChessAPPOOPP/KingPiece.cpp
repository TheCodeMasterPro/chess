#include "KingPiece.h"
#include "Board.h"

KingPiece::KingPiece(const char& type, Board* board) : ChessPiece(type, board) {}

bool KingPiece::isValidMove(const string& move)
{
	// example: for 'c6d5'
	int xSrc = move[0];   // c
	int ySrc = move[1];   // 6
	int xDest = move[2];  // d
	int yDest = move[3];  // 5
	if (abs(xSrc - xDest) > 1 || abs(ySrc - yDest) > 1)
	{
		return false;
	}
	return true;
}


