#include <iostream>
#include <conio.h> 
#include <cstdlib>
#include <string>
#include <cctype>

#include "ComplexNum.h"
#include "Maze.h"

void addTwoCompNums(ComplexNum n1, ComplexNum n2) {
	float realResult = n1.getReal() + n2.getReal();
	float imagResult = n1.getImag() + n2.getImag();
	ComplexNum result(realResult, imagResult);

	result.Display();
}

void subtractTwoCompNums(ComplexNum n1, ComplexNum n2) {
	float realResult = n1.getReal() - n2.getReal();
	float imagResult = n1.getImag() - n2.getImag();
	ComplexNum result(realResult, imagResult);

	result.Display();
}

int main()
{
	char choice;
	do
	{
		std::cout << "Select one of the below or enter q to quit\n";
		std::cout << "1- add 2 complex numbers\n";
		std::cout << "2- subtract 2 complex numbers\n";
		std::cout << "3- Maze game using OOP\n";
		std::cin >> choice;

		switch (choice)
		{
		case '1': {
			system("CLS");
			std::cout << "Counter: " << ComplexNum::counter << '\n';

			ComplexNum firstNum(3, 2);
			ComplexNum secondNum(2, 0);

			std::cout << "adding: ";
			firstNum.Display();
			std::cout << "to: ";
			secondNum.Display();
			std::cout << "Counter: " << ComplexNum::counter << '\n';
			std::cout << "Result : ";
			addTwoCompNums(firstNum, secondNum);
			std::cout << "Counter: " << ComplexNum::counter << '\n';
			std::cout << '\n';

			break;
		}

		case '2': {
			system("CLS");
			std::cout << "Counter: " << ComplexNum::counter << '\n';
			ComplexNum thirdNum(5, 1);
			ComplexNum forthNum(2, 6);

			std::cout << "subtracting: ";
			thirdNum.Display();
			std::cout << "from: ";
			forthNum.Display();
			std::cout << "Counter: " << ComplexNum::counter << '\n';
			std::cout << "Result : ";
			subtractTwoCompNums(thirdNum, forthNum);
			std::cout << "Counter: " << ComplexNum::counter << '\n';
			break;
		}
		case '3': {
			system("CLS");
			srand(time(0));
			Maze maze;
			char grid[maze.HEIGHT][maze.WIDTH];

			for (int i = 0; i < maze.HEIGHT; i++) {
				for (int j = 0; j < maze.WIDTH; j++) {
					if (i == 0 || i == maze.HEIGHT - 1 || j == 0 || j == maze.WIDTH - 1) {
						grid[i][j] = 'x';  // Borders of the grid
					}
					else {
						grid[i][j] = ' ';  // Empty space inside the grid
					}
				}
			}

			int playerX, playerY, treasureX, treasureY;

			maze.generateRandomPosition(playerX, playerY);
			do {
				maze.generateRandomPosition(treasureX, treasureY);
			} while (playerX == treasureX && playerY == treasureY);

			grid[treasureY][treasureX] = 'X';

			while (true) {
				maze.displayGrid(grid, playerX, playerY);
				if (maze.checkWinCondition(playerX, playerY, treasureX, treasureY)) {
					std::cout << "Congratulations! You found the treasure 'X'!" << std::endl;
					break;
				}

				char move = maze.handleInput();
				maze.movePlayer(playerX, playerY, move, grid);
			};
		}
		default:
			break;
		}
	} while (tolower(choice) != 'q');

}