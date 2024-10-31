#include "Maze.h"
#include <conio.h> 
#include <cstdlib>
#include <string>


void Maze::generateRandomPosition(int& x, int& y) {
	x = rand() % (Maze::WIDTH - 2) + 1;
	y = rand() % (Maze::HEIGHT - 2) + 1;
}

void Maze::displayGrid(char grid[HEIGHT][WIDTH], int playerX, int playerY) {
	system("CLS");

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (i == playerY && j == playerX) {
				std::cout << 'P';
			}
			else {
				std::cout << grid[i][j];
			}
		}
		std::cout << std::endl;
	}
}

char Maze::handleInput() {
	char move = _getch();
	return tolower(move);
}

void Maze::movePlayer(int& playerX, int& playerY, char move, const char grid[HEIGHT][WIDTH]) {
	if (move == 'w' && grid[playerY - 1][playerX] != 'x') {
		playerY--;
	}
	else if (move == 's' && grid[playerY + 1][playerX] != 'x') {
		playerY++;
	}
	else if (move == 'a' && grid[playerY][playerX - 1] != 'x') {
		playerX--;
	}
	else if (move == 'd' && grid[playerY][playerX + 1] != 'x') {
		playerX++;
	}
}

bool Maze::checkWinCondition(int playerX, int playerY, int treasureX, int treasureY) {
	return playerX == treasureX && playerY == treasureY;
}
