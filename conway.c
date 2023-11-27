#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define BOARD_SIZE 80
#define BOARD_LIMIT BOARD_SIZE - 1
#define SLEEP_TIME 300000
#define SEED_VALUE 900
#define BOARD_CHAR "*"
#define DEAD 0
#define ALIVE 1
#define LOOP_VARS int x, y, r = 0
#define BOARD_ARG(boardName) int boardName[BOARD_SIZE][BOARD_SIZE]

typedef struct Neighbours
{
	int top;
	int topRight;
	int right;
	int bottomRight;
	int bottom;
	int bottomLeft;
	int left;
	int topLeft;
	int totalAlive;
} Neighbours;

int computeTop(int x, int y, BOARD_ARG(board))
{
	int computeX, computeY;

	computeX = x;
	computeY = y == 0 ? BOARD_LIMIT : y - 1;

	return board[computeX][computeY];
}

int computeTopRight(int x, int y, BOARD_ARG(board))
{
	int computeX, computeY;

	computeX = (x == BOARD_LIMIT) ? 0 : x + 1;
	computeY = (y == 0) ? BOARD_LIMIT : y - 1;

	return board[computeX][computeY];
}

int computeRight(int x, int y, BOARD_ARG(board))
{
	int computeX, computeY;

	computeX = (x == BOARD_LIMIT) ? 0 : x + 1;
	computeY = y;

	return board[computeX][computeY];
}

int computeBottomRight(int x, int y, BOARD_ARG(board))
{
	int computeX, computeY;

	computeX = (x == BOARD_LIMIT) ? 0 : x + 1;
	computeY = (y == BOARD_LIMIT) ? 0 : y + 1;

	return board[computeX][computeY];
}

int computeBottom(int x, int y, BOARD_ARG(board))
{
	int computeX, computeY;

	computeX = x;
	computeY = (y == BOARD_LIMIT) ? 0 : y + 1;

	return board[computeX][computeY];
}

int computeBottomLeft(int x, int y, BOARD_ARG(board))
{
	int computeX, computeY;

	computeX = (x == 0) ? BOARD_LIMIT : x - 1;
	computeY = (y == BOARD_LIMIT) ? 0 : y + 1;

	return board[computeX][computeY];
}

int computeLeft(int x, int y, BOARD_ARG(board))
{
	int computeX, computeY;

	computeX = (x == 0) ? BOARD_LIMIT : x - 1;
	computeY = y;

	return board[computeX][computeY];
}

int computeTopLeft(int x, int y, BOARD_ARG(board))
{
	int computeX, computeY;

	computeX = (x == 0) ? BOARD_LIMIT : x - 1;
	computeY = (y == BOARD_LIMIT) ? BOARD_LIMIT : y - 1;

	return board[computeX][computeY];
}

Neighbours computeNeighbours(int x, int y, BOARD_ARG(board))
{
	Neighbours neighbours;

	neighbours.top = computeTop(x, y, board);
	neighbours.topRight = computeTopRight(x, y, board);
	neighbours.right = computeRight(x, y, board);
	neighbours.bottomRight = computeBottomRight(x, y, board);
	neighbours.bottom = computeBottom(x, y, board);
	neighbours.bottomLeft = computeBottomLeft(x, y, board);
	neighbours.left = computeLeft(x, y, board);
	neighbours.topLeft = computeTopLeft(x, y, board);
	neighbours.totalAlive = neighbours.top + neighbours.topRight + neighbours.right + neighbours.bottomRight + neighbours.bottom + neighbours.bottomLeft + neighbours.left + neighbours.topLeft;

	return neighbours;
}

int computeCell(int cellState, int x, int y, BOARD_ARG(board))
{
	Neighbours neighbours;

	neighbours = computeNeighbours(x, y, board);

	if (cellState == ALIVE && (neighbours.totalAlive == 2 || neighbours.totalAlive == 3))
	{
		return ALIVE;
	}

	if (cellState == DEAD && (neighbours.totalAlive == 3))
	{
		return ALIVE;
	}

	return DEAD;
}

void copyBoard(BOARD_ARG(fromBoard), BOARD_ARG(toBoard))
{
	LOOP_VARS;
	for (x = 0; x < BOARD_SIZE; x++)
	{
		for (y = 0; y < BOARD_SIZE; y++)
		{
			toBoard[x][y] = fromBoard[x][y];
		}
	}
}

void computeNextGeneration(BOARD_ARG(board), BOARD_ARG(computeBoard))
{
	LOOP_VARS;
	for (x = 0; x < BOARD_SIZE; x++)
	{
		for (y = 0; y < BOARD_SIZE; y++)
		{
			board[x][y] = computeCell(computeBoard[x][y], x, y, computeBoard);
		}
	}
}

void initBoard(BOARD_ARG(board))
{
	LOOP_VARS;
	for (x = 0; x < BOARD_SIZE; x++)
	{
		for (y = 0; y < BOARD_SIZE; y++)
		{
			r = rand() % 1000;
			if (r > SEED_VALUE)
			{
				board[x][y] = 1;
			}
		}
		printf("\n");
	}
}

void printBoard(BOARD_ARG(board))
{
	LOOP_VARS;
	for (x = 0; x < BOARD_SIZE; x++)
	{
		for (y = 0; y < BOARD_SIZE; y++)
		{
			printf("  %s", board[x][y] == 1 ? BOARD_CHAR : " ");
		}
		printf("\n");
	}
}

int main()
{
	LOOP_VARS;
	int board[BOARD_SIZE][BOARD_SIZE] = {0};
	int computeBoard[BOARD_SIZE][BOARD_SIZE] = {0};

	srand(time(NULL));

	initBoard(board);
	copyBoard(board, computeBoard);

	while (1)
	{
		printBoard(board);
		computeNextGeneration(board, computeBoard);
		copyBoard(board, computeBoard);
		usleep(SLEEP_TIME);
		system("clear");
	}
}
