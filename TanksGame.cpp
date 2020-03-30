#define _CRT_SECURE_NO_WARNINGS

// TanksGame.cpp

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

#define GAME_MATRIX 11
#define GAME_MATRIX_WITH_WALLS 13

// Struct declaration
struct Location
{
	int nLine;
	int nCol;
};

struct Tank
{
	int nLine;
	int nCol;
};

// Function prototypes
Location* CreateLocationArry();
void CreateGameMatrix(int parrnGameBoard[][GAME_MATRIX_WITH_WALLS]);
void PrintGameMatrix(int iparrnGameBoard[][GAME_MATRIX_WITH_WALLS],
	Tank* iptnkFirstTank, Tank* iptnkSecondTank);
void InitGame(int ioparrnGameBoard[][GAME_MATRIX_WITH_WALLS],
	Tank* iotpnkFirstTank, Tank* ioptnkSecondTank);
void MoveTank(Location* iarrlctLocaion,
	int ioparrnGameBoard[][GAME_MATRIX_WITH_WALLS],
	Tank* iotpnkTank, Tank* iptnkSecondTank);
int RegularShot(Location* iarrlctLocaion,
	int ioparrnGameBoard[][GAME_MATRIX_WITH_WALLS],
	Tank* itpnkTank, Tank* iptnkSecondTank);
int TurningShot(Location* iarrlctLocaion,
	int ioparrnGameBoard[][GAME_MATRIX_WITH_WALLS],
	Tank* itpnkTank, Tank* iptnkSecondTank);
int AirBomb(Location* iarrlctLocaion,
	int ioparrnGameBoard[][GAME_MATRIX_WITH_WALLS],
	Tank* itpnkTank, Tank* iptnkSecondTank);
void StartGame(Location* iarrlctLocaion,
	int ioparrnGameBoard[][GAME_MATRIX_WITH_WALLS],
	Tank* itpnkTank, Tank* iptnkSecondTank);

//---------------------------------------------------------------------------------------
//								Tanks Game
//								----------
//
// General : Tank game for two persons.
//
// Input : The player insert numbers that represent a Functions that the player can do.
//
// Process : A game that you can move with your tank, shot or air bombing.
//
// Output : The winner player.
//
//---------------------------------------------------------------------------------------
// Programmer : Yuval Sarig
// Student No : 322875816
// Date : 29.11.2019
//---------------------------------------------------------------------------------------
void main()
{
	// Array definition
	Location* arrlctLocaion;
	int parrnGameBoard[GAME_MATRIX_WITH_WALLS][GAME_MATRIX_WITH_WALLS];
	int a;

	// Variable definition 
	Tank* tnkpFirstTank;
	Tank* tnkpSecondTank;

	// Code section

	arrlctLocaion = CreateLocationArry();
	tnkpFirstTank = (Tank*)malloc(sizeof(Tank));
	tnkpSecondTank = (Tank*)malloc(sizeof(Tank));

	StartGame(arrlctLocaion, parrnGameBoard, tnkpFirstTank, tnkpSecondTank);
	getchar();

}

//-----------------------------------------------------------------------------
//								Create Location Arry
//								--------------------
//
// General : Create the location arry.
//
// Parameters : None.
//		
// Return Value : Location arry.
//
//-----------------------------------------------------------------------------
Location* CreateLocationArry()
{
	// Array definition
	Location* arrlctLocaion;

	// Code section

	arrlctLocaion = (Location*)malloc(9 * sizeof(Location));

	// Location index 0 is no movment
	arrlctLocaion[0].nLine = 0;
	arrlctLocaion[0].nCol = 0;

	// Location index 1 is North - East
	arrlctLocaion[1].nLine = -1;
	arrlctLocaion[1].nCol = -1;

	// Location index 2 is North
	arrlctLocaion[2].nLine = -1;
	arrlctLocaion[2].nCol = 0;

	// Location index 3 is North-West
	arrlctLocaion[3].nLine = -1;
	arrlctLocaion[3].nCol = 1;

	// Location index 4 is West
	arrlctLocaion[4].nLine = 0;
	arrlctLocaion[4].nCol = 1;

	// Location index 5 is South-West
	arrlctLocaion[5].nLine = 1;
	arrlctLocaion[5].nCol = 1;

	// Location index 6 is South
	arrlctLocaion[6].nLine = 1;
	arrlctLocaion[6].nCol = 0;

	// Location index 7 is Southeast
	arrlctLocaion[7].nLine = 1;
	arrlctLocaion[7].nCol = -1;

	// Location index 8 is East
	arrlctLocaion[8].nLine = 0;
	arrlctLocaion[8].nCol = -1;

	return arrlctLocaion;
}

//-----------------------------------------------------------------------------
//								Create Game Matrix
//								------------------
//
// General : Create the game board.
//
// Parameters : 
//			ioparrnGameBoard - Game Matrix to create (In/Out)
//		
// Return Value : game board.
//
//-----------------------------------------------------------------------------
void CreateGameMatrix(int ioparrnGameBoard[][GAME_MATRIX_WITH_WALLS])
{
	// Code section

	// Initializing the walls around the matrix
	for (int i = 0; i < GAME_MATRIX_WITH_WALLS; i++)
	{
		ioparrnGameBoard[i][0] = -1;
		ioparrnGameBoard[0][i] = -1;
		ioparrnGameBoard[i][GAME_MATRIX_WITH_WALLS - 1] = -1;
		ioparrnGameBoard[GAME_MATRIX_WITH_WALLS - 1][i] = -1;
	}

	// Initializing the game board
	for (int i = 0; i < GAME_MATRIX; i++)
	{
		for (int j = 0; j < GAME_MATRIX; j++)
		{
			// Checking if the cell is a odd  number
			if (i % 2 != 0 && j % 2 != 0)
			{
				// Set breakable wall
				ioparrnGameBoard[i + 1][j + 1] = 1;
			}
			else
			{
				// Set a regular square
				ioparrnGameBoard[i + 1][j + 1] = 0;
			}
		}
	}
}

//-----------------------------------------------------------------------------
//									Print Game Matrix
//									-----------------
//
// General : Print the game matrix.
//
// Parameters : 
//		iparrnGameBoard - Game board (In)
//		iptnkFirstTank  - First Tank (In)
//		iptnkSecondTank - SecondTank (In)
//
// Return Value : None.
//
//-----------------------------------------------------------------------------
void PrintGameMatrix(int iparrnGameBoard[][GAME_MATRIX_WITH_WALLS],
	Tank* iptnkFirstTank, Tank* iptnkSecondTank)
{
	// Code section

	system("cls");
	for (int i = 0; i < GAME_MATRIX_WITH_WALLS; i++)
	{
		for (int j = 0; j < GAME_MATRIX_WITH_WALLS; j++)
		{
			if (iptnkFirstTank->nCol == j && iptnkFirstTank->nLine == i ||
				iptnkSecondTank->nCol == j && iptnkSecondTank->nLine == i)
			{
				printf(" o ");
			}
			else if (!iparrnGameBoard[i][j])
			{
				printf("   ");
			}
			else if (iparrnGameBoard[i][j] > 0)
			{
				printf("|x|");
			}
			else if (iparrnGameBoard[i][j] < 0)
			{
				if (j == 0)
				{
					if (i / 10 > 0)
					{
						printf(" %d", i);
					}
					else
					{
						printf(" %d ", i);
					}
				}
				else if (i == 0)
				{
					if (j / 10 > 0)
					{
						printf(" %d", j);
					}
					else
					{
						printf(" %d ", j);
					}
				}
				else if (j == GAME_MATRIX_WITH_WALLS - 1)
				{
					if (i / 10 > 0)
					{
						printf(" %d", i);
					}
					else
					{
						printf(" %d ", i);
					}
				}
				else if (i == GAME_MATRIX_WITH_WALLS - 1)
				{
					if (j / 10 > 0)
					{
						printf("%d ", j);
					}
					else
					{
						printf(" %d ", j);
					}
				}
			}
		}
		printf("\n");
	}
}

//-----------------------------------------------------------------------------
//									Init Game
//									---------
//
// General : Initializing all game parameters.
//
// Parameters : 
//		ioarrlctLocaion  - Location Arry (In/Out)
//		ioparrnGameBoard - Game board (In/Out)
//		ioptnkFirstTank  - First Tank (In/Out)
//		ioptnkSecondTank - Second Tank (In/Out)
//
// Return Value : None.
//
//-----------------------------------------------------------------------------
void InitGame(int ioparrnGameBoard[][GAME_MATRIX_WITH_WALLS],
	Tank* ioptnkFirstTank, Tank* ioptnkSecondTank)
{
	// Code section

	CreateGameMatrix(ioparrnGameBoard);
	ioptnkFirstTank->nCol = 1;
	ioptnkFirstTank->nLine = 6;
	ioptnkSecondTank->nCol = GAME_MATRIX;
	ioptnkSecondTank->nLine = 6;
}

//-----------------------------------------------------------------------------
//									Move Tank
//									---------
//
// General : Move a Tank.
//
// Parameters : 
//		iarrlctLocaion  - Location Arry (In)
//		ioparrnGameBoard - Game board (In/Out)
//		iotpnkTank  - Tank to move (In/Out)
//		ioptnkSecondTank - Second Tank (In)
//
// Return Value : None.
//
//-----------------------------------------------------------------------------
void MoveTank(Location* iarrlctLocaion,
	int ioparrnGameBoard[][GAME_MATRIX_WITH_WALLS],
	Tank* iotpnkTank, Tank* iptnkSecondTank)
{
	// Variable definition 
	int nMoveDirection;
	int nNumberOfSteps;
	int nLine;
	int nCol;

	// Code section

	printf("Enter move direction: 1 - Up, 2 - Right, 3 - Down, 4 - Left\n");
	scanf("%d", &nMoveDirection);
	nMoveDirection *= 2;
	printf("Enter number of step to go\n");
	scanf("%d", &nNumberOfSteps);
	for (int i = 1; i <= nNumberOfSteps; i++)
	{
		nLine = iarrlctLocaion[nMoveDirection].nLine + iotpnkTank->nLine;
		nCol = iarrlctLocaion[nMoveDirection].nCol + iotpnkTank->nCol;
		if (iptnkSecondTank->nLine == nLine && iptnkSecondTank->nCol == nCol)
		{
			break;
		}
		else if (!ioparrnGameBoard[nLine][nCol])
		{
			iotpnkTank->nLine = nLine;
			iotpnkTank->nCol = nCol;
		}
		else if (ioparrnGameBoard[nLine][nCol] > 0)
		{
			ioparrnGameBoard[nLine][nCol] = 0;
			iotpnkTank->nLine = nLine;
			iotpnkTank->nCol = nCol;
			break;
		}
		else
		{
			break;
		}

	}
}

//-----------------------------------------------------------------------------
//								Regular Shot
//								------------
//
// General : Make a regular shot by a tank.
//
// Parameters : 
//		iarrlctLocaion  - Location Arry (In)
//		ioparrnGameBoard - Game board (In/Out)
//		itpnkTank  - The shooter tank (In)
//		ioptnkSecondTank - Second Tank (In)
//
// Return Value : If the shooter tank killed the second tank return 1.
//
//-----------------------------------------------------------------------------
int RegularShot(Location* iarrlctLocaion,
	int ioparrnGameBoard[][GAME_MATRIX_WITH_WALLS],
	Tank* itpnkTank, Tank* iptnkSecondTank)
{
	// Variable definition 
	int nMoveDirection;
	int nLine;
	int nCol;

	// Code section

	printf("Enter shot direction: 1 - Up, 2 - Right, 3 - Down, 4 - Left\n");
	scanf("%d", &nMoveDirection);
	nMoveDirection *= 2;
	nLine = iarrlctLocaion[nMoveDirection].nLine + itpnkTank->nLine;
	nCol = iarrlctLocaion[nMoveDirection].nCol + itpnkTank->nCol;
	while (1)
	{
		if (iptnkSecondTank->nLine == nLine && iptnkSecondTank->nCol == nCol)
		{
			return 1;
		}
		else if (!ioparrnGameBoard[nLine][nCol])
		{
			nLine += iarrlctLocaion[nMoveDirection].nLine;
			nCol += iarrlctLocaion[nMoveDirection].nCol;
		}
		else if (ioparrnGameBoard[nLine][nCol] > 0)
		{
			ioparrnGameBoard[nLine][nCol] = 0;
			return 0;
		}
		else
		{
			return 0;
		}
	}

}

//-----------------------------------------------------------------------------
//								Turning Shot
//								------------
//
// General : Make a turning shot by hitting a wall and turning right.
//
// Parameters : 
//		iarrlctLocaion  - Location Arry (In)
//		ioparrnGameBoard - Game board (In/Out)
//		itpnkTank  - The shooter tank (In)
//		ioptnkSecondTank - Second Tank (In)
//
// Return Value : If the shooter tank killed the second tank return 1.
//
//-----------------------------------------------------------------------------
int TurningShot(Location* iarrlctLocaion,
	int ioparrnGameBoard[][GAME_MATRIX_WITH_WALLS],
	Tank* itpnkTank, Tank* iptnkSecondTank)
{
	// Variable definition 
	int nMoveDirection;
	int nLine;
	int nCol;
	int nCounterHitWall = 0;

	// Code section

	printf("Enter shot direction: 1 - Up, 2 - Right, 3 - Down, 4 - Left\n");
	scanf("%d", &nMoveDirection);
	nMoveDirection *= 2;
	nLine = iarrlctLocaion[nMoveDirection].nLine + itpnkTank->nLine;
	nCol = iarrlctLocaion[nMoveDirection].nCol + itpnkTank->nCol;
	while (1)
	{
		if (iptnkSecondTank->nLine == nLine && iptnkSecondTank->nCol == nCol)
		{
			return 1;
		}
		else if (itpnkTank->nLine == nLine && itpnkTank->nCol == nCol)
		{
			return 2;
		}
		else if (!ioparrnGameBoard[nLine][nCol])
		{
			nLine += iarrlctLocaion[nMoveDirection].nLine;
			nCol += iarrlctLocaion[nMoveDirection].nCol;
		}
		else if (ioparrnGameBoard[nLine][nCol] > 0)
		{
			ioparrnGameBoard[nLine][nCol] = 0;
			return 0;
		}
		else if (nCounterHitWall < 5)
		{
			nLine -= iarrlctLocaion[nMoveDirection].nLine;
			nCol -= iarrlctLocaion[nMoveDirection].nCol;
			if (nMoveDirection < 8)
			{
				nMoveDirection += 2;
			}
			else
			{
				nMoveDirection = 2;
			}
			nCounterHitWall++;
		}
		else
		{
			return 0;
		}
	}
}

//-----------------------------------------------------------------------------
//								Air Bomb
//								--------
//
// General : Make an air bomb hitting a random 3X3 cells.
//
// Parameters : 
//		iarrlctLocaion  - Location Arry (In)
//		ioparrnGameBoard - Game board (In/Out)
//		itpnkTank  - The shooter tank (In)
//		ioptnkSecondTank - Second Tank (In)
//
// Return Value : If the shooter tank killed the second tank return 1.
//
//-----------------------------------------------------------------------------
int AirBomb(Location* iarrlctLocaion,
	int ioparrnGameBoard[][GAME_MATRIX_WITH_WALLS],
	Tank* itpnkTank, Tank* iptnkSecondTank)
{
	// Variable definition 
	int nLine;
	int nCol;
	int nBombDamage[9];

	// Code section

	printf("Enter bomb index line, column\n");
	scanf("%d %d", &nLine, &nCol);
	srand(time(0));
	for (int i = 0; i < 9; i++)
	{
		nBombDamage[i] = rand() % 2;
	}
	for (int i = 0; i < 9; i++)
	{
		if (nBombDamage[i])
		{
			if (iptnkSecondTank->nLine == (nLine + iarrlctLocaion[i].nLine) &&
				iptnkSecondTank->nCol == (nCol + iarrlctLocaion[i].nCol))
			{
				return 1;
			}
			else if (ioparrnGameBoard[nLine + iarrlctLocaion[i].nLine][nCol +
				iarrlctLocaion[i].nCol] > 0)
			{
				ioparrnGameBoard[nLine + iarrlctLocaion[i].nLine][nCol + iarrlctLocaion[i].nCol] = 0;
			}
			else if (itpnkTank->nLine == nLine + iarrlctLocaion[i].nLine
				&& itpnkTank->nCol == nCol + iarrlctLocaion[i].nCol)
			{
				return 2;
			}
		}
	}
	return 0;
}

//-----------------------------------------------------------------------------
//								Start Game
//								----------
//
// General : Start the game, all functions are enabled for this function.
//
// Parameters : 
//		iarrlctLocaion   - Location Arry (In)
//		ioparrnGameBoard - Game board (In/Out)
//		iotpnkFirstTank  - The shooter tank (In/Out)
//		ioptnkSecondTank - Second Tank (In/Out)
//
// Return Value : None.
//
//-----------------------------------------------------------------------------
void StartGame(Location* iarrlctLocaion,
	int ioparrnGameBoard[][GAME_MATRIX_WITH_WALLS],
	Tank* iotpnkFirstTank, Tank* ioptnkSecondTank)
{
	// Variable definition 
	int nTankTurn = 1;
	int nDeadTank = 0;
	int nOption;

	// Code section

	InitGame(ioparrnGameBoard, iotpnkFirstTank, ioptnkSecondTank);
	while (!nDeadTank)
	{
		PrintGameMatrix(ioparrnGameBoard, iotpnkFirstTank, ioptnkSecondTank);
		printf("Player number %d Turn\n", nTankTurn);
		printf("Enter a game option: 1 - Move, 2 - Regular Shot, 3 - Turning Shot, 4 - Air Bomb\n");
		scanf("%d", &nOption);
		if (nTankTurn == 1)
		{
			switch (nOption)
			{
			case 1:
				MoveTank(iarrlctLocaion, ioparrnGameBoard, iotpnkFirstTank, ioptnkSecondTank);
				break;
			case 2:
				nDeadTank = RegularShot(iarrlctLocaion, ioparrnGameBoard, iotpnkFirstTank, ioptnkSecondTank);
				break;
			case 3:
				nDeadTank = TurningShot(iarrlctLocaion, ioparrnGameBoard, iotpnkFirstTank, ioptnkSecondTank);
				break;
			case 4:
				nDeadTank = AirBomb(iarrlctLocaion, ioparrnGameBoard, iotpnkFirstTank, ioptnkSecondTank);
				break;
			default:
				break;
			}
			nTankTurn = 2;
		}
		else
		{
			switch (nOption)
			{
			case 1:
				MoveTank(iarrlctLocaion, ioparrnGameBoard, ioptnkSecondTank, iotpnkFirstTank);
				break;
			case 2:
				nDeadTank = RegularShot(iarrlctLocaion, ioparrnGameBoard, ioptnkSecondTank, iotpnkFirstTank);
				break;
			case 3:
				nDeadTank = TurningShot(iarrlctLocaion, ioparrnGameBoard, ioptnkSecondTank, iotpnkFirstTank);
				break;
			case 4:
				nDeadTank = AirBomb(iarrlctLocaion, ioparrnGameBoard, ioptnkSecondTank, iotpnkFirstTank);
				break;
			default:
				break;
			}
			nTankTurn = 1;
		}
	}
	if (nDeadTank == 1)
	{
		if (nTankTurn == 1)
		{
			printf("Player 2 is win\nGame Over");
		}
		else
		{
			printf("Player 1 is win\nGame Over");
		}
	}
	else
	{
		if (nTankTurn == 1)
		{
			printf("Player 1 is win\nGame Over");
		}
		else
		{
			printf("Player 2 is win\nGame Over");
		}
	}



}