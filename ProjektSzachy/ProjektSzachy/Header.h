#pragma once
#include <stdio.h>
#include <string.h>

#define ChessPiece struct piece
#define ChessP ChessPiece*


typedef enum { black, white } Allegiance;
typedef enum { pawn, knight, bishop, rook, queen, king } Piece;
typedef enum { false = 0, true } bool;
typedef enum { blank = 0, MayGo, Cursor } Helper;

typedef struct positions
{
	char X;
	char Y;
}position;

ChessPiece
{
	Allegiance team;
	Piece type;
	position standing;
};

typedef struct Moves
{
	position From;
	position To;
	Piece Moving;
	bool captured;
	struct Moves* next;
}SavedMoves;

void AddPast(SavedMoves** head, ChessP moving, const position To, bool Capture);

void setup(ChessP chessboard[8][8]);
void SetPiece(ChessP chessboard[8][8], const char X, const char Y, const Allegiance team, const Piece type);
void ChooseAPiece(ChessP chessboard[8][8], Helper AnotherArray[8][8], const Allegiance team, SavedMoves* history);
bool ActualMoving(ChessP chessboard[8][8], const position From, Helper AnotherArray[8][8], SavedMoves* history);

void PrintBoard(ChessP chessboard[8][8], Helper AnotherArray[8][8]);

//checking the king
bool Checked(ChessP chessboard[8][8], const position standing, Helper AnotherArray[8][8]);
void MovePiece(ChessP chessboard[8][8], const position standing, Helper AnotherArray[8][8], SavedMoves* history);
void MovePawn(ChessP chessboard[8][8], const position standing, Helper AnotherArray[8][8], SavedMoves* history);
void MoveKnight(ChessP chessboard[8][8], const position standing, Helper AnotherArray[8][8]);
void MoveBishop(ChessP chessboard[8][8], const position standing, Helper AnotherArray[8][8]);
void MoveRook(ChessP chessboard[8][8], const position standing, Helper AnotherArray[8][8]);
void MoveQueen(ChessP chessboard[8][8], const position standing, Helper AnotherArray[8][8]);
void MoveKing(ChessP chessboard[8][8], const position standing, Helper AnotherArray[8][8], SavedMoves* history);
bool CanCastle(SavedMoves* history);
bool CanCastleLeft(const Allegiance team, SavedMoves* history);
bool CanCastleRight(const Allegiance team, SavedMoves* history);


void InCognitoMode(SavedMoves** head);
void CleanHelper(Helper AnotherArray[8][8]);
void CleanUpBoard(ChessP chessboard[8][8]);