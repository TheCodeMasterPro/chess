#include "Board.h"

ChessPiece* createPiece(const char& type, Board* board);

Board::Board(const string& start)
{
	char type = ' ';
	string idx = "";
	this->isWhiteTurn = true;
	this->pieces = new ChessPiece**[BOARD_SIDE];
	for (int i = 0; i < BOARD_SIDE; i++)
	{
		pieces[i] = new ChessPiece*[BOARD_SIDE];
	}

	for (int y = 0; y < BOARD_SIDE; y++)
	{
		for (int x = 0; x < BOARD_SIDE; x++)
		{
			idx = "";
			type = start[(y * BOARD_SIDE + x)];
			this->pieces[y][x] = createPiece(type, this);
			idx += (x + SMALL_A_ASCII);
			idx += (abs(y - 8) + 48);
			if (pieces[y][x] != nullptr)
			{
				if (pieces[y][x]->getType() == 'k')
				{
					this->setBlackKingidx(idx);
				}
				if (pieces[y][x]->getType() == 'K')
				{
					this->setWhiteKingidx(idx);
				}
			}
		}
	}
}

Board::~Board()
{
	for (int i = 0; i < BOARD_SIDE; i++)
	{
		for (int j = 0; j < BOARD_SIDE; j++)
		{
			if (this->pieces[i][j] != nullptr)
			{
				delete this->pieces[i][j];
			}
		}
	}
}

ChessPiece* createPiece(const char& type, Board* board)
{
	ChessPiece* tmp = nullptr;
	switch (type)
	{
	case '#':
		return nullptr;
		break;

	case 'k': case 'K':
		tmp = new KingPiece(type, board);
		break;

	case 'q': case 'Q':
		tmp = new QueenPiece(type, board);
		break;

	case 'r': case 'R':
		tmp = new RookPiece(type, board);
		break;

	case 'n': case 'N':
		tmp = new KnightPiece(type, board);
		break;
	
	case 'b': case 'B':
		tmp = new BishopPiece(type, board);
		break;

	case 'p': case 'P':
		tmp = new PawnPiece(type, board);
		break;

	default:
		tmp = nullptr;
	}
	return tmp;
}

MoveCodes Board::move(const string& move)
{
	string chessMove = move.substr(2, 2);
	ChessPiece* sourcePiece = this->getPieceByIdx(move.substr(0, 2));
	ChessPiece* destPiece = this->getPieceByIdx(move.substr(2, 2));
	
	if (this->isPieceAlreadyThere(move))
	{
		return PieceAlreadyThere;
	}
	if (!this->isMoveHisPlayer(sourcePiece))
	{
		return DoesntMoveHisPlayer;
	}
	if (this->isEatsHisPlayer(destPiece))
	{
		return EatsHisPlayer;
	}	
	if (sourcePiece->isValidMove(move) == false)
	{
		return IllegalMovement;
	}
	
	movePiece(move.substr(0, 2), move.substr(2, 2), sourcePiece, destPiece);
	if (sourcePiece->getType() == 'k')
	{
		this->setBlackKingidx(move.substr(2, 2));
	}
	if (sourcePiece->getType() == 'K')
	{
		this->setWhiteKingidx(move.substr(2, 2));
	}
	if (this->isTriesToChessHimself())
	{
		movePiece(move.substr(2, 2), move.substr(0, 2), sourcePiece, destPiece);
		this->setPieceByIdx(move.substr(2, 2), destPiece);
		if (sourcePiece->getType() == 'k')
		{
			this->setBlackKingidx(move.substr(0, 2));
		}
		if (sourcePiece->getType() == 'K')
		{
			this->setWhiteKingidx(move.substr(0, 2));
		}
		return TriesToChessHimself;
	}
	delete destPiece;

	if (this->isWhiteTurn ? sourcePiece->isValidMove(chessMove + this->blackKingIdx) : sourcePiece->isValidMove(chessMove + this->whiteKingIdx))
	{
		return ValidMoveDoneChess;
	}
	return ValidMove;
}

ChessPiece* Board::getPieceByIdx(const string& idx) const
{
	int x = idx[0] - SMALL_A_ASCII;
	int y = abs(idx[1] - 56);
	return getPieceByIdx(x, y);
}

ChessPiece* Board::getPieceByIdx(const int& x, const int& y) const
{
	return this->pieces[y][x];
}

void Board::setPieceByIdx(const string& idx, ChessPiece* piece)
{
	int x = idx[0] - SMALL_A_ASCII;
	int y = abs(idx[1] - 56);
	this->setPieceByIdx(x, y, piece);
}

void Board::setPieceByIdx(const int& x, const int& y, ChessPiece* piece)
{
	this->pieces[y][x] = piece;
}

void Board::setIsWhiteTurn(const bool isWhiteTurn)
{
	this->isWhiteTurn = isWhiteTurn;
}

bool Board::getIsWhiteTurn() const
{
	return this->isWhiteTurn;
}

void Board::setWhiteKingidx(const string& idx)
{
	this->whiteKingIdx = idx;
}

void Board::setBlackKingidx(const string& idx)
{
	this->blackKingIdx = idx;
}

bool Board::isPieceAlreadyThere(const string& move) const
{
	if (move.substr(0, 2) == move.substr(2, 2)) // For some reason, the frontend does not allowed it
	{
		return true;
	}
	return false;
}

bool Board::isMoveHisPlayer(const ChessPiece* sourcePiece) const
{
	char sourceToolType = ' ';
	bool isSelfMovement;
	if (sourcePiece == nullptr)
	{
		return false;
	}
	sourceToolType = sourcePiece->getType();
	isSelfMovement = this->isWhiteTurn ? (sourceToolType >= CAPITAL_A_ASCII && sourceToolType <= CAPITAL_Z_ASCII) : (sourceToolType >= SMALL_A_ASCII && sourceToolType <= SMALL_Z_ASCII);
	if (!isSelfMovement)
	{
		return false;
	}
	return true;
}

bool Board::isEatsHisPlayer(const ChessPiece* destPiece) const
{
	bool isMovementToSelf;
	char destToolType;
	if (destPiece != nullptr)
	{
		destToolType = destPiece->getType();
		isMovementToSelf = this->isWhiteTurn ? (destToolType >= CAPITAL_A_ASCII && destToolType <= CAPITAL_Z_ASCII) : (destToolType >= SMALL_A_ASCII && destToolType <= SMALL_Z_ASCII);
		if (isMovementToSelf)
		{
			return true;
		}
	}
	return false;
}

bool Board::isTriesToChessHimself() // need to be fixed!
{
	ChessPiece* currPiece;
	string currIdx = "";
	string kingIdx = this->isWhiteTurn ? this->whiteKingIdx : this->blackKingIdx;
	this->isWhiteTurn = !this->isWhiteTurn;
	for (int y = 0; y < BOARD_SIDE; y++)
	{
		for (int x = 0; x < BOARD_SIDE; x++)
		{
			currPiece = this->getPieceByIdx(x, y);
			if (this->isMoveHisPlayer(this->getPieceByIdx(x, y)))
			{
				currIdx = "";
				currIdx += (x + SMALL_A_ASCII);
				currIdx += (abs(y - 8) + 48);
				
				if (currPiece->isValidMove(currIdx + kingIdx))
				{
					this->isWhiteTurn = !this->isWhiteTurn;
					return true;
				}
			}
		}
	}
	this->isWhiteTurn = !this->isWhiteTurn;
	return false;
}

void Board::movePiece(const string& sourceIdx, const string& destIdx, ChessPiece* sourcePiece, ChessPiece* destPiece)
{
	if (destPiece != nullptr)
	{
		this->setPieceByIdx(destIdx, nullptr);
	}
	this->setPieceByIdx(sourceIdx, nullptr);
	this->setPieceByIdx(destIdx, sourcePiece);
}