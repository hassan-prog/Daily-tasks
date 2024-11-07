#include <iostream>
#include "Game.h"
#include "Snake.h"

int main(int argc, char** argv[]) {
	srand(static_cast<unsigned int>(time(0)));
	Game snakeGame;

	while (snakeGame.isRunning()) {
		// update
		snakeGame.update();

		// render
		snakeGame.render();

		// restarting the clock each iteration
		snakeGame.restartClock();
	}
	return 0;
}