#pragma once

#include "ChessPiece.h"
#include <string>

using std::string;

class PawnPiece : public ChessPiece
{
public:
	PawnPiece(const char& type, Board* board);
	virtual bool isValidMove(const string& move) override;
	//void setIsFirstMove(const bool isFirstMove);
private:
	bool isFirstMove;
};