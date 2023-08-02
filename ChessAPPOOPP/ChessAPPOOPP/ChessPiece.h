#pragma once

#include <string>

using std::string;

#define CAPITAL_A_ASCII 65
#define CAPITAL_Z_ASCII 90
#define SMALL_A_ASCII 97
#define SMALL_Z_ASCII 122

class Board;

class ChessPiece
{
public:
	ChessPiece(const char& type, Board* board);
	virtual bool isValidMove(const string& move) = 0;
	char getType() const;
	bool isWhite() const;
protected:
	char _type;
	Board* _board;
};