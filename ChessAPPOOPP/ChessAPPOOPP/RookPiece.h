#pragma once

#include "ChessPiece.h"
#include <string>

using std::string;

class RookPiece : public ChessPiece
{
public:
	RookPiece(const char& type, Board* board);
	virtual bool isValidMove(const string& move) override;
	static bool isValidMove(const Board* board, const string& move);
private:

};