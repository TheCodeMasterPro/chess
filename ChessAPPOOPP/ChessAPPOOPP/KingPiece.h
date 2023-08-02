#pragma once

#include "ChessPiece.h"
#include <string>

using std::string;

class KingPiece : public ChessPiece
{
public:
	KingPiece(const char& type, Board* board);
	virtual bool isValidMove(const string& move) override;
private:

};