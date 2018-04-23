#include "Header.h"

int main()
{
	ChessP chessboard[8][8];
	Helper AnotherArray[8][8];
	CleanHelper(AnotherArray);
	SavedMoves* history = NULL;
	
	Allegiance Turn = white;

	

	setup(chessboard);

	PrintBoard(chessboard, AnotherArray);
	while (true)
	{
		ChooseAPiece(chessboard[8][8], AnotherArray, Turn, history);
		Turn = (Turn + 1) % 2;
	}
	CleanUpBoard(chessboard);
	return 0;
}