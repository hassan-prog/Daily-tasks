#include <iostream>
#include "Game.h"
#include "Snake.h"

void main(int argc, char** argv[]) {
	Game snakeGame; 

	while (snakeGame.isRunning()) {
		snakeGame.handleUserInput();
		// update
		snakeGame.update();

		// render
		snakeGame.render();

		// restarting the clock each iteration
		snakeGame.restartClock();
	}
}