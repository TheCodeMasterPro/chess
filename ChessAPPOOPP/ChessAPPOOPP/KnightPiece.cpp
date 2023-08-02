#include "KnightPiece.h"

KnightPiece::KnightPiece(const char& type, Board* board) : ChessPiece(type, board) {}

bool KnightPiece::isValidMove(const string& move)
{
	// example: for 'a8a2'
	int xSrc = move[0];   // a
	int ySrc = move[1];   // 8
	int xDest = move[2];  // a
	int yDest = move[3];  // 2

	if ((abs(xSrc - xDest) == 1) && (abs(ySrc - yDest) == 2))
	{
		return true;
	}
	else if ((abs(xSrc - xDest) == 2) && (abs(ySrc - yDest) == 1))
	{
		return true;
	}
	return false;
}