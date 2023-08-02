#pragma once

#include "ChessPiece.h"
#include <string>

using std::string;

class KnightPiece : public ChessPiece
{
public:
	KnightPiece(const char& type, Board* board);
	virtual bool isValidMove(const string& move) override;
private:

};