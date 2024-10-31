#include <iostream>

#pragma once
class Maze
{
public:
	static const int HEIGHT = 20;
	static const int WIDTH = 80;

	void generateRandomPosition(int& x, int& y);
	void displayGrid(char grid[HEIGHT][WIDTH], int playerX, int playerY);
	char handleInput();
	void movePlayer(int& playerX, int& playerY, char move, const char grid[HEIGHT][WIDTH]);
	bool checkWinCondition(int playerX, int playerY, int treasureX, int treasureY);

};

