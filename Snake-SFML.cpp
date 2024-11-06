#include <iostream>
#include "Game.h"
#include "Snake.h"

void main(int argc, char** argv[]) {
	srand(time(0));
	Game snakeGame; 

	while (snakeGame.isRunning()) {
		// update
		snakeGame.update();

		// render
		snakeGame.render();

		// restarting the clock each iteration
		snakeGame.restartClock();
	}
}