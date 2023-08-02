#include "ChessPiece.h"

ChessPiece::ChessPiece(const char& type, Board* board)
{
	_type = type;
	_board = board;
}

char ChessPiece::getType() const
{
	return this->_type;
}

bool ChessPiece::isWhite() const
{
	if (this->_type >= CAPITAL_A_ASCII && this->_type <= CAPITAL_Z_ASCII)
	{
		return true;
	}
	else if (this->_type >= SMALL_A_ASCII && this->_type <= SMALL_Z_ASCII)
	{
		return false;
	}
}
