#pragma once

#include "ChessPiece.h"
#include "BishopPiece.h"
#include "KingPiece.h"
#include "KnightPiece.h"
#include "PawnPiece.h"
#include "QueenPiece.h"
#include "RookPiece.h"
#include <string>
#include <math.h>

using std::string;

#define BOARD_SIDE 8

enum MoveCodes
{
	ValidMove = '0',
	ValidMoveDoneChess,  // '1'
	DoesntMoveHisPlayer, // '2'
	EatsHisPlayer,       // '3'
	TriesToChessHimself, // '4'
	UnvalidIndexes,      // '5'
	IllegalMovement,     // '6'
	PieceAlreadyThere,   // '7'
	ValidMoveDoneMate,   // '8'
};

class Board
{
public:
	Board(const string& start);
	~Board();
	MoveCodes move(const string& move);
	bool isChess(const Board* board, const string& move);
	bool isMate(const Board* board, const string& move);
	ChessPiece* getPieceByIdx(const string& idx) const;
	ChessPiece* getPieceByIdx(const int& x, const int& y) const;
	void setPieceByIdx(const string& idx, ChessPiece* piece);
	void setPieceByIdx(const int& x, const int& y, ChessPiece* piece);
	void setIsWhiteTurn(const bool isWhiteTurn);
	bool getIsWhiteTurn() const;
	void setWhiteKingidx(const string& idx);
	void setBlackKingidx(const string& idx);
private:
	bool isWhiteTurn;
	string whiteKingIdx;
	string blackKingIdx;
	ChessPiece*** pieces;
	bool isPieceAlreadyThere(const string& move) const;
	bool isMoveHisPlayer(const ChessPiece* sourcePiece) const;
	bool isEatsHisPlayer(const ChessPiece* destPiece) const;
	bool isTriesToChessHimself();
	void movePiece(const string& sourceIdx, const string& destIdx, ChessPiece* sourcePiece, ChessPiece* destPiece);
};