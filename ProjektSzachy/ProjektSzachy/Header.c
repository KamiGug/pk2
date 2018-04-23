#include "Header.h"

void AddPast(SavedMoves** head, ChessP moving, const position To, bool Capture)
{
	SavedMoves* tmp = malloc(sizeof(SavedMoves));
	tmp->Moving = moving->type;
	tmp->From.X = moving->standing.X;
	tmp->From.Y = moving->standing.Y;
	tmp->To.X = To.X;
	tmp->To.Y = To.Y;
	tmp->captured = Capture;
	tmp->next = *head;
	*head = tmp;
}

void setup(ChessP chessboard[8][8])
{
	//preparing for placing
	for (char y = 0; y < 2; y++)
	{
		for (char x = 0; x < 8; x++)
		{
			chessboard[x][y] = malloc(sizeof(ChessPiece));
		}
	}
	for (char y = 2; y < 6; y++)
	{
		for (char x = 0; x < 8; x++)
		{
			chessboard[x][y] = NULL;
		}
	}
	for (char y = 0; y < 2; y++)
	{
		for (char x = 0; x < 8; x++)
		{
			chessboard[x][y+6] = malloc(sizeof(ChessPiece));
		}
	}
	//placing white pieces 
	SetPiece(chessboard, 0, 0, white, rook);
	SetPiece(chessboard, 7, 0, white, rook);

	SetPiece(chessboard, 1, 0, white, knight);
	SetPiece(chessboard, 6, 0, white, knight);

	SetPiece(chessboard, 2, 0, white, bishop);
	SetPiece(chessboard, 5, 0, white, bishop);

	SetPiece(chessboard, 3, 0, white, queen);

	SetPiece(chessboard, 4, 0, white, king);

	for (char x = 0; x < 8; x++)
	{
		SetPiece(chessboard, x, 1, white, pawn);
	}

	//placing black pieces
	SetPiece(chessboard, 0, 7, black, rook);
	SetPiece(chessboard, 7, 7, black, rook);

	SetPiece(chessboard, 1, 7, black, knight);
	SetPiece(chessboard, 6, 7, black, knight);

	SetPiece(chessboard, 2, 7, black, bishop);
	SetPiece(chessboard, 5, 7, black, bishop);

	SetPiece(chessboard, 3, 7, black, queen);

	SetPiece(chessboard, 4, 7, black, king);

	for (char x = 0; x < 8; x++)
	{
		SetPiece(chessboard, x, 6, black, pawn);
	}
}

void SetPiece(ChessP chessboard[8][8], const char X, const char Y, const Allegiance team, const Piece type)
{
	chessboard[X][Y]->team = team;
	chessboard[X][Y]->type = type;
	chessboard[X][Y]->standing.X = X;
	chessboard[X][Y]->standing.Y = Y;
}

void ChooseAPiece(ChessP chessboard[8][8], Helper AnotherArray[8][8], const Allegiance team, SavedMoves* history)
{
	position tmp;
	char adress[2];
	if (chessboard[0][0]->team == white)
	{
		printf("huh");
	}
	do
	{
		do
		{
			do
			{
				printf("Choose piece you want to move(type in it's adress): ");
				scanf_s("%2c", adress);
			} while (((adress[0] < 'a'  || adress[0] > 'h') && (adress[0] < 'A' || adress[0] > 'I')) || (adress[1] < '1' && adress[1] > '8'));
			if (adress[0] > 'Z')
			{
				tmp.X = adress[0] - 'a';
			}
			else
			{
				tmp.X = adress[0] - 'A';
			}
			tmp.Y = 8 - adress[1] + '0';
		} while (chessboard[tmp.X][tmp.Y] == NULL || chessboard[tmp.X][tmp.Y]->team != team);
		AnotherArray[tmp.X][tmp.Y] = Cursor;
		MovePiece(chessboard[8][8], tmp, AnotherArray, history);
		PrintBoard(chessboard[8][8], AnotherArray);
	}while (ActualMoving(chessboard[8][8], tmp, AnotherArray, history));
}

bool ActualMoving(ChessP chessboard[8][8], const position From, Helper AnotherArray[8][8], SavedMoves* history)
{
	position tmp;
	char adress[2];
	do
	{
		printf("Where do you want to move the piece(type in an adress): ");
		scanf_s("%2s", adress);
		if (adress[0] > 'Z')
		{
			tmp.X = adress[0] - 'a';
		}
		else
		{
			tmp.X = adress[0] - 'A';
		}
		tmp.Y = 8 - adress[1] + '1';
	} while (tmp.X < 0 || tmp.X > 7 || tmp.Y < 0 || tmp.Y > 7 || (AnotherArray[tmp.X][tmp.Y] != MayGo && AnotherArray[tmp.X][tmp.Y] != Cursor));
	if (AnotherArray[tmp.X][tmp.Y] == Cursor) return true;
	ChessP moving = chessboard[tmp.X][tmp.Y];
	bool capture;
	if (moving->type = pawn && tmp.X != From.X)
	{
		capture = true;
		if (chessboard[tmp.X][tmp.Y] != NULL)
		{
			free(chessboard[tmp.X][tmp.Y]);
		}
		else
		{
			free(chessboard[tmp.X][tmp.Y - 1]);
			chessboard[tmp.X][tmp.Y - 1] == NULL;
		}
	}
	else
	{
		if (chessboard[tmp.X][tmp.Y] != NULL)
		{
			capture = true;
			free(chessboard[tmp.X][tmp.Y]);
		}
		else
		{
			capture = false;
		}
	}
	AddPast(&history, moving, tmp, capture);
	chessboard[tmp.X][tmp.Y] = moving;
	moving->standing.X = tmp.X;
	moving->standing.Y = tmp.Y;
	chessboard[From.X][From.Y] = NULL;
	return false;
}

void PrintBoard(ChessP chessboard[8][8], Helper AnotherArray[8][8])
{
	printf(" abcdefgh\n");
	for (char y = 0; y < 8; y++)
	{
		printf("%d", 8 - y);
		for (char x = 0; x < 8; x++)
		{
			switch (AnotherArray[x][y]) 
			{
			case blank:
				if (chessboard[x][y] != NULL)
				{
					if (chessboard[x][y]->team == white)
					{
						switch (chessboard[x][y]->type)
						{
						case pawn:
							printf("P");
							break;

						case rook:
							printf("R");
							break;

						case knight:
							printf("N");
							break;

						case bishop:
							printf("B");
							break;

						case queen:
							printf("Q");
							break;

						case king:
							printf("K");
							break;
						}
					}
					else
					{
						switch (chessboard[x][y]->type)
						{
						case pawn:
							printf("p");
							break;

						case rook:
							printf("r");
							break;

						case knight:
							printf("n");
							break;

						case bishop:
							printf("b");
							break;

						case queen:
							printf("q");
							break;

						case king:
							printf("k");
							break;
						}
					}
				}
				else
				{
					if ((x + y) % 2)
					{
						printf(" "); //white, where the piece can move
					}
					else
					{
						printf(" "); //black, where the piece can move
					}
				}
				break;

			
			case MayGo:
				if (chessboard[x][y] != NULL)
				{
					if (chessboard[x][y]->team == white)
					{
						switch (chessboard[x][y]->type)
						{
						case pawn:
							printf("P");
							break;

						case rook:
							printf("R");
							break;

						case knight:
							printf("N");
							break;

						case bishop:
							printf("B");
							break;

						case queen:
							printf("Q");
							break;

						case king:
							printf("K");
							break;
						}
					}
					else
					{
						switch (chessboard[x][y]->type)
						{
						case pawn:
							printf("p");
							break;

						case rook:
							printf("r");
							break;

						case knight:
							printf("n");
							break;

						case bishop:
							printf("b");
							break;

						case queen:
							printf("q");
							break;

						case king:
							printf("k");
							break;
						}
					}
				}
				else
				{
					if ((x + y) % 2)
					{
						printf(" "); //white, where the piece can move
					}
					else
					{
						printf(" "); //black, where the piece can move
					}
				}
				break;

			case Cursor:
				if (chessboard[x][y] != NULL)
				{
					if (chessboard[x][y]->team == white)
					{
						switch (chessboard[x][y]->type)
						{
						case pawn:
							printf("P");
							break;

						case rook:
							printf("R");
							break;

						case knight:
							printf("N");
							break;

						case bishop:
							printf("B");
							break;

						case queen:
							printf("Q");
							break;

						case king:
							printf("K");
							break;
						}
					}
					else
					{
						switch (chessboard[x][y]->type)
						{
						case pawn:
							printf("p");
							break;

						case rook:
							printf("r");
							break;

						case knight:
							printf("n");
							break;

						case bishop:
							printf("b");
							break;

						case queen:
							printf("q");
							break;

						case king:
							printf("k");
							break;
						}
					}
				}
				else
				{
					if ((x + y) % 2)
					{
						printf(" "); //white, where the piece can move
					}
					else
					{
						printf(" "); //black, where the piece can move
					}
				}
				break;

			}
		}
		printf("%d\n", 8-y);
	}
	printf(" abcdefgh\n");
}

void MovePiece(ChessP chessboard[8][8], const position standing, Helper AnotherArray[8][8], SavedMoves* history)
{
	switch (chessboard[standing.X][standing.Y]->type)
	{
	case pawn:
		MovePawn(chessboard[8][8], standing, AnotherArray, history);
		break;

	case rook:
		MoveRook(chessboard[8][8], standing, AnotherArray);
		break;

	case knight:
		MoveKnight(chessboard[8][8], standing, AnotherArray);
		break;

	case bishop:
		MoveBishop(chessboard[8][8], standing, AnotherArray);
		break;

	case queen:
		MoveQueen(chessboard[8][8], standing, AnotherArray);
		break;

	case king:
		MoveKing(chessboard[8][8], standing, AnotherArray, history);
		break;
	}
}

void MovePawn(ChessP chessboard[8][8], const position standing, Helper AnotherArray[8][8], SavedMoves* history)
{
	Allegiance team = chessboard[standing.X][standing.Y]->team;
	char DependantOnTeam;
	if (team == white)
	{
		DependantOnTeam = 1;
	}
	else
	{
		DependantOnTeam = -1;
	}
	position tmp = { standing.X, standing.Y + DependantOnTeam };
	if (chessboard[standing.X][standing.Y + DependantOnTeam] == NULL)
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
		if (((team == white && standing.Y == 1) || (team == black && standing.Y == 6)) && (chessboard[standing.X][standing.Y + DependantOnTeam] == NULL && chessboard[standing.X][standing.Y + 2 * DependantOnTeam] == NULL))
		{
			tmp.Y++;
			AnotherArray[tmp.X][tmp.Y] = MayGo;
		}

	}

	if (standing.X != 0 && chessboard[standing.X - 1][standing.Y + DependantOnTeam]!=NULL && chessboard[standing.X - 1][standing.Y + DependantOnTeam]->team != team)
	{
		tmp.X = standing.X - 1;
		tmp.Y = standing.Y + DependantOnTeam;
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}

	if (standing.X != 7 && chessboard[standing.X + 1][standing.Y + DependantOnTeam] != NULL && chessboard[standing.X + 1][standing.Y + DependantOnTeam]->team != team)
	{
		tmp.X = standing.X + 1;
		tmp.Y = standing.Y + DependantOnTeam;
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}

	if ((team == white && standing.Y == 4) || (team == black && standing.Y == 3)) //En passant
	{
		tmp.X = standing.X - 1;
		tmp.Y = standing.Y;
		if (standing.X != 0 && chessboard[standing.X - 1][standing.Y]!=NULL && chessboard[standing.X - 1][standing.Y]->team != team && chessboard[standing.X - 1][standing.Y]->type == pawn && history->To.X == standing.X - 1 && history->From.Y == standing.Y + 2* DependantOnTeam)//ostatni na liscie ruchow jest pionek stajacy po lewej tego pionka 
		{
			tmp.Y += DependantOnTeam;
			AnotherArray[tmp.X][tmp.Y] = MayGo;
		}
		else
		{
			tmp.X = standing.X + 1;
			if (standing.X != 7 && chessboard[standing.X + 1][standing.Y] != NULL && chessboard[standing.X + 1][standing.Y]->team != team && chessboard[standing.X + 1][standing.Y]->type == pawn && history->To.X == standing.X + 1 && history->From.Y == standing.Y + 2 * DependantOnTeam)//ostatni na liscie ruchow jest pionek stajacy po prawej tego pionka 
			{
				tmp.Y += DependantOnTeam;
				AnotherArray[tmp.X][tmp.Y] = MayGo;
			}
		}

	}
}

void MoveRook(ChessP chessboard[8][8], const position standing, Helper AnotherArray[8][8])
{
	position tmp = { standing.X+1, standing.Y };

	while (tmp.X < 8 && chessboard[tmp.X][tmp.Y] == NULL)
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
		tmp.X++;
	}
	if (tmp.X < 8 && chessboard[tmp.X][tmp.Y] != NULL && chessboard[tmp.X][tmp.Y]->team != chessboard[standing.X][standing.Y]->team)
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}
	tmp.X = standing.X-1;

	while (tmp.X > -1 && chessboard[tmp.X][tmp.Y] == NULL)
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
		tmp.X--;
	}
	if (tmp.X > -1 && chessboard[tmp.X][tmp.Y] != NULL && chessboard[tmp.X][tmp.Y]->team != chessboard[standing.X][standing.Y]->team)
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}
	tmp.X = standing.X;

	tmp.Y++;
	while (tmp.Y < 8 && chessboard[tmp.X][tmp.Y] == NULL)
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
		tmp.Y++;
	}
	if (tmp.Y < 8 && chessboard[tmp.X][tmp.Y] != NULL && chessboard[tmp.X][tmp.Y]->team != chessboard[standing.X][standing.Y]->team)
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}
	tmp.Y = standing.Y-1;

	while (tmp.Y > -1 && chessboard[tmp.X][tmp.Y] == NULL)
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
		tmp.Y--;
	}
	if (tmp.Y > -1 && chessboard[tmp.X][tmp.Y] != NULL && chessboard[tmp.X][tmp.Y]->team != chessboard[standing.X][standing.Y]->team)
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}
}

void MoveKnight(ChessP chessboard[8][8], const position standing, Helper AnotherArray[8][8])
{
	position tmp;

	tmp.X = standing.X + 2;
	tmp.Y = standing.Y + 1;
	if (tmp.X < 8 && tmp.Y < 8 && (chessboard[tmp.X][tmp.Y] == NULL || (chessboard[tmp.X][tmp.Y] != NULL && chessboard[tmp.X][tmp.Y]->team != chessboard[standing.X][standing.Y]->team)))
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}

	tmp.Y = standing.Y - 1;
	if (tmp.X < 8 && tmp.Y > -1 && (chessboard[tmp.X][tmp.Y] == NULL || (chessboard[tmp.X][tmp.Y] != NULL && chessboard[tmp.X][tmp.Y]->team != chessboard[standing.X][standing.Y]->team)))
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}

	tmp.X = standing.X + 1;
	tmp.Y = standing.Y - 2;
	if (tmp.X < 8 && tmp.Y > -1 && (chessboard[tmp.X][tmp.Y] == NULL || (chessboard[tmp.X][tmp.Y] != NULL && chessboard[tmp.X][tmp.Y]->team != chessboard[standing.X][standing.Y]->team)))
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}

	tmp.Y = standing.Y + 2;
	if (tmp.X < 8 && tmp.Y < 8 && (chessboard[tmp.X][tmp.Y] == NULL || (chessboard[tmp.X][tmp.Y] != NULL && chessboard[tmp.X][tmp.Y]->team != chessboard[standing.X][standing.Y]->team)))
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}

	tmp.X = standing.X - 1;
	if (tmp.X > -1 && tmp.Y < 8 && (chessboard[tmp.X][tmp.Y] == NULL || (chessboard[tmp.X][tmp.Y] != NULL && chessboard[tmp.X][tmp.Y]->team != chessboard[standing.X][standing.Y]->team)))
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}

	tmp.Y = standing.Y - 2;
	if (tmp.X > -1 && tmp.Y > -1 && (chessboard[tmp.X][tmp.Y] == NULL || (chessboard[tmp.X][tmp.Y] != NULL && chessboard[tmp.X][tmp.Y]->team != chessboard[standing.X][standing.Y]->team)))
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}

	tmp.X = standing.X - 2;
	tmp.Y = standing.Y - 1;
	if (tmp.X > -1 && tmp.Y > -1 && (chessboard[tmp.X][tmp.Y] == NULL || (chessboard[tmp.X][tmp.Y] != NULL && chessboard[tmp.X][tmp.Y]->team != chessboard[standing.X][standing.Y]->team)))
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}

	tmp.Y = standing.Y + 1;
	if (tmp.X > -1 && tmp.Y < 8 && (chessboard[tmp.X][tmp.Y] == NULL || (chessboard[tmp.X][tmp.Y] != NULL && chessboard[tmp.X][tmp.Y]->team != chessboard[standing.X][standing.Y]->team)))
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}
}

void MoveBishop(ChessP chessboard[8][8], const position standing, Helper AnotherArray[8][8])
{
	position tmp = { standing.X + 1, standing.Y+1 };

	while (tmp.X < 8 && tmp.Y < 8 && chessboard[tmp.X][tmp.Y] == NULL)
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
		tmp.X++;
		tmp.Y++;
	}
	if (tmp.X < 8 && tmp.Y < 8 && chessboard[tmp.X][tmp.Y] != NULL && chessboard[tmp.X][tmp.Y]->team != chessboard[standing.X][standing.Y]->team)
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}

	tmp.X = standing.X + 1;
	tmp.Y = standing.Y - 1;
	while (tmp.X < 8 && tmp.Y > -1 && chessboard[tmp.X][tmp.Y] == NULL)
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
		tmp.X++;
		tmp.Y--;
	}
	if (tmp.X < 8 && tmp.Y > -1 && chessboard[tmp.X][tmp.Y] != NULL && chessboard[tmp.X][tmp.Y]->team != chessboard[standing.X][standing.Y]->team)
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}

	tmp.X = standing.X - 1;
	tmp.Y = standing.Y - 1;
	while (tmp.X > -1 && tmp.Y > -1 && chessboard[tmp.X][tmp.Y] == NULL)
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
		tmp.X--;
		tmp.Y--;
	}
	if (tmp.X > -1 && tmp.Y > -1 && chessboard[tmp.X][tmp.Y] != NULL && chessboard[tmp.X][tmp.Y]->team != chessboard[standing.X][standing.Y]->team)
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}

	tmp.X = standing.X - 1;
	tmp.Y = standing.Y + 1;
	while (tmp.X > -1 && tmp.Y < 8 && chessboard[tmp.X][tmp.Y] == NULL)
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
		tmp.X--;
		tmp.Y++;
	}
	if (tmp.X > -1 && tmp.Y < 8 && chessboard[tmp.X][tmp.Y] != NULL && chessboard[tmp.X][tmp.Y]->team != chessboard[standing.X][standing.Y]->team)
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}
}

void MoveQueen(ChessP chessboard[8][8], const position standing, Helper AnotherArray[8][8])
{
	MoveRook(chessboard[8][8], standing, AnotherArray);
	MoveBishop(chessboard[8][8], standing, AnotherArray);
}

void MoveKing(ChessP chessboard[8][8], const position standing, Helper AnotherArray[8][8], SavedMoves* history)
{
	position tmp;
	Allegiance team = chessboard[standing.X][standing.Y]->team;
	tmp.X = standing.X + 1;
	tmp.Y = standing.Y + 1;
	if (tmp.X < 8 && tmp.Y < 8 && (chessboard[tmp.X][tmp.Y] == NULL || (chessboard[tmp.X][tmp.Y] != NULL && chessboard[tmp.X][tmp.Y]->team != team)))
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}

	tmp.Y = standing.Y - 1;
	if (tmp.X < 8 && tmp.Y > -1 && (chessboard[tmp.X][tmp.Y] == NULL || (chessboard[tmp.X][tmp.Y] != NULL && chessboard[tmp.X][tmp.Y]->team != team)))
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}

	tmp.X = standing.X - 1;
	if (tmp.X > -1 && tmp.Y < 8 && (chessboard[tmp.X][tmp.Y] == NULL || (chessboard[tmp.X][tmp.Y] != NULL && chessboard[tmp.X][tmp.Y]->team != team)))
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}

	tmp.Y = standing.Y + 1;
	if (tmp.X > -1 && tmp.Y < 8 && (chessboard[tmp.X][tmp.Y] == NULL || (chessboard[tmp.X][tmp.Y] != NULL && chessboard[tmp.X][tmp.Y]->team != team)))
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}

	tmp.X = standing.X;
	tmp.Y = standing.Y - 1;
	if (tmp.Y > -1 && (chessboard[tmp.X][tmp.Y] == NULL || (chessboard[tmp.X][tmp.Y] != NULL && chessboard[tmp.X][tmp.Y]->team != team)))
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}

	tmp.Y = standing.Y + 1;
	if (tmp.Y < 8 && (chessboard[tmp.X][tmp.Y] == NULL || (chessboard[tmp.X][tmp.Y] != NULL && chessboard[tmp.X][tmp.Y]->team != team)))
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}

	tmp.X = standing.X + 1;
	tmp.Y = standing.Y;
	if (tmp.X < 8 && (chessboard[tmp.X][tmp.Y] == NULL || (chessboard[tmp.X][tmp.Y] != NULL && chessboard[tmp.X][tmp.Y]->team != team)))
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}

	tmp.X = standing.X - 1;
	if (tmp.X > -1 && (chessboard[tmp.X][tmp.Y] == NULL || (chessboard[tmp.X][tmp.Y] != NULL && chessboard[tmp.X][tmp.Y]->team != team)))
	{
		AnotherArray[tmp.X][tmp.Y] = MayGo;
	}

	if (CanCastle(history)) //castling
	{
		if (CanCastleLeft(history))
		{
			if (team == white && chessboard[1][0] == NULL && chessboard[2][0] == NULL && chessboard[3][0] == NULL)
			{
				AnotherArray[standing.X - 2][standing.Y] = MayGo;
			}
			else
			{
				if (team == black && chessboard[1][7] == NULL && chessboard[2][7] == NULL && chessboard[3][7] == NULL)
				{
					AnotherArray[standing.X - 2][standing.Y] = MayGo;
				}
			}
		}
		if (CanCastleRight(history) && !Checked(chessboard[8][8], standing, AnotherArray))
		{
			if (team == white && chessboard[5][0] == NULL && chessboard[6][0] == NULL)
			{
				AnotherArray[standing.X + 2][standing.Y] = MayGo;
			}
			else
			{
				if (team == black && chessboard[5][7] == NULL && chessboard[6][7] == NULL)
				{
					AnotherArray[standing.X + 2][standing.Y] = MayGo;
				}
			}
		}
	}
}

bool CanCastle(SavedMoves* history)
{
	if (history = NULL || history->next == NULL) return true;
	history = history->next;
	if (history->Moving == king)
	{
		return false;
	}
	while (history->next!=NULL && history->next->next != NULL)
	{
		history = history->next->next;
		if (history->Moving == king)
		{
			return false;
		}
	}
	return true;
}

bool CanCastleLeft(SavedMoves* history)
{
	if (history = NULL || history->next == NULL) return true;
	history = history->next;
	if (history->Moving == rook && history->From.X == 0)
	{
		return false;
	}
	while (history->next != NULL && history->next->next != NULL)
	{
		history = history->next->next;
		if (history->Moving == rook && history->From.X == 0)
		{
			return false;
		}
	}
	return true;
}

bool CanCastleRight(SavedMoves* history)
{
	if (history = NULL || history->next == NULL) return true;
	history = history->next;
	if (history->Moving == rook && history->From.X == 7)
	{
		return false;
	}
	while (history->next != NULL && history->next->next != NULL)
	{
		history = history->next->next;
		if (history->Moving == rook && history->From.X == 7)
		{
			return false;
		}
	}
	return true;
}

void InCognitoMode(SavedMoves** head)
{
	if (*head != NULL)
	{
		SavedMoves* tmp;
		while (*head != NULL)
		{
			tmp = *head;
			*head = (*head)->next;
			free(tmp);
		}
		*head = NULL;
	}
}

void CleanHelper(Helper AnotherArray[8][8])
{
	for (char X = 0; X < 8; X++)
	{
		for (char Y = 0; Y < 8; Y++)
		{
			if (AnotherArray[X][Y] != Cursor)
			{
				AnotherArray[X][Y] = blank;
			}
		}
	}
}

void CleanUpBoard(ChessP chessboard[8][8])
{
	for (char y = 0; y < 8; y++)
	{
		for (char x = 0; x < 8; x++)
		{
			free(chessboard[x][y]);
			chessboard[x][y] = NULL;
		}
	}
}