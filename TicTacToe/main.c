#include <stdio.h>

enum shapes {
	CROSS,
	CIRCLE,
	EMPTY
};

void getPlayerPosition(enum shapes shape, enum shapes gameBoard[3][3],int *x,int *y);
void printBoard(enum shapes gameBoard[3][3]);
int checkWin(enum shapes gameBoard[3][3], int *gameWon, enum shapes shape);


int main() {

	enum shapes gameBoard[3][3] = {
		{EMPTY, EMPTY, EMPTY},
		{EMPTY, EMPTY, EMPTY},
		{EMPTY, EMPTY, EMPTY}
	};

	int gameWon = 0;
	int x, y;
	enum shapes currentShape = CIRCLE;


	printf("----TIC TAC TOE----\n");
	do{

		printBoard(gameBoard);

		getPlayerPosition(currentShape, gameBoard, &x, &y);

		gameWon = checkWin(gameBoard, &gameWon, currentShape);

		if (!gameWon) {
			currentShape = (currentShape == CIRCLE) ? CROSS : CIRCLE;
		}
	} while (!gameWon);

	printf("\n");
	printBoard(gameBoard);
	printf("%s wins!\n", (currentShape == CIRCLE) ? "CIRCLE" : "CROSS");

	return 0;
}

void getPlayerPosition(enum shapes shape, enum shapes gameBoard[3][3], int *x, int *y) {
	enum shapes currentShape;
	switch(shape) {
		case CIRCLE:
			currentShape = CIRCLE;
			printf("----CIRCLE'S TURN----\n");
			break;
		case CROSS:
			currentShape = CROSS;
			printf("----CROSS's TURN----\n");
			break;
		default:
			printf("Unknown.");
			return;
	}

	while (1) {
		printf("What x and y would you like?\n");
		int result = scanf("%d %d", x, y);

		if (result != 2) {
			printf("Please enter two integers. \n");
			while (getchar() != '\n');
			continue;
		}

		if (*x < 0 || *x > 2 || *y < 0 || *y > 2) {
			printf("Invalid coordinates entered. \n");
			continue;
		}

		if (gameBoard[*x][*y] != EMPTY) {
			printf("Position is taken. please pick a different location. \n");
		}

		gameBoard[*x][*y] = currentShape;
		break;
	}
}

void printBoard(enum shapes gameBoard[3][3]) {

	printf("\n  0 1 2 \n");

	for (int i = 0; i < 3; i++) {

		printf("%d ", i);

		for (int j = 0; j < 3; j++) {
			char cell;
			switch (gameBoard[i][j]) {
				case CIRCLE:
					cell = 'O';
					break;
				case CROSS:
					cell = 'X';
					break;
				case EMPTY:
					cell = '.';
					break;
				default:
					cell = '?';
					break;
			}
			printf("%c ", cell);
		}
		printf("\n");
	}
	printf("\n");
}

int checkWin(enum shapes gameBoard[3][3], int* gameWon, enum shapes shape) {
	for (int i = 0; i < 3; i++) {
		if ((gameBoard[i][0] == shape && gameBoard[i][1] == shape && gameBoard[i][2] == shape) ||
			(gameBoard[0][i] == shape && gameBoard[1][i] == shape && gameBoard[2][i] == shape)) {
			return 1;
		}
	}

	if ((gameBoard[0][0] == shape && gameBoard[1][1] == shape && gameBoard[2][2] == shape) ||
		(gameBoard[0][2] == shape && gameBoard[0][1] == shape && gameBoard[2][0] == shape)) {
		return 1;
	}

	return 0;
}