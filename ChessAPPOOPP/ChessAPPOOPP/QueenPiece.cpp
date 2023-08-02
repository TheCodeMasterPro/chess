#include "QueenPiece.h"

QueenPiece::QueenPiece(const char& type, Board* board) : ChessPiece(type, board) {}

bool QueenPiece::isValidMove(const string& move)
{
	if (RookPiece::isValidMove(_board, move) || BishopPiece::isValidMove(_board, move))
	{
		return true;
	}
	return false;
}
