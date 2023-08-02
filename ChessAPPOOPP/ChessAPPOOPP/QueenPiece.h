#pragma once

#include "ChessPiece.h"
#include "RookPiece.h"
#include "BishopPiece.h"
#include <string>

using std::string;

class QueenPiece : public ChessPiece
{
public:
	QueenPiece(const char& type, Board* board);
	virtual bool isValidMove(const string& move) override;
private:

};
