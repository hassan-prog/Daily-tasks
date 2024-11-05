#include <iostream>
#include "Game.h"

void main(int argc, char** argv[]) {
	Game snakeGame;

	while (snakeGame.isRunning()) {
		//update
		snakeGame.update();

		//render
		snakeGame.render();
	}
}