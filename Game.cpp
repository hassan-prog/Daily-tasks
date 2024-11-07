#include <iostream>
#include "Game.h"


// private functions
void Game::initVariables() {
	snakeWindow = nullptr;
	GRID_HEIGHT = 600;
	GRID_WIDTH = 800;
	BLOCK_SIZE = 16;
	videoMode.height = GRID_HEIGHT;
	videoMode.width = GRID_WIDTH;
	extendPlayerCollectableColor = sf::Color::Green;
	slowSpeedCollectableColor = sf::Color::Cyan;

	// when i move these 4 vars into the constructor it doesn't render the colors nor the player
	extendPlayerCollectable = new Collectable(extendPlayerCollectableColor);
	slowSpeedCollectable = new Collectable(slowSpeedCollectableColor);
	obstacle1 = new Obstacle();
	player = new Snake(BLOCK_SIZE);
}

void Game::initWindow() {
	snakeWindow = new sf::RenderWindow(videoMode, "sssss-Snake", sf::Style::Titlebar | sf::Style::Close);

	//snakeWindow->setFramerateLimit(60); // cap 60 FPS
}

void Game::loseIfOutOfBoundries() {
	int grid_size_x = GRID_WIDTH / BLOCK_SIZE;
	int grid_size_y = GRID_HEIGHT / BLOCK_SIZE;

	// if player is out of bounderies make the player lose
	if ((*player).getPosition().x <= 0 || (*player).getPosition().y <= 0
		|| (*player).getPosition().x >= grid_size_x - 1
		|| (*player).getPosition().y >= grid_size_y - 1) {
		(*player).lose();
	}
}

// Constructors & Destructors
Game::Game() {
	this->initVariables();
	this->initWindow();
}

Game::~Game() {
	delete snakeWindow;
	delete extendPlayerCollectable;
	delete slowSpeedCollectable;
	delete obstacle1;
	delete player;
}


//public functions
void Game::restartClock() {
	timeElabsed += clock.restart();
}

void Game::handleUserInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		&& player->getDirection() != Direction::Down) {
		player->setDirection(Direction::Up);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		&& player->getDirection() != Direction::Up) {
		player->setDirection(Direction::Down);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		&& player->getDirection() != Direction::Left) {
		player->setDirection(Direction::Right);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		&& player->getDirection() != Direction::Right) {
		player->setDirection(Direction::Left);
	}
}

// Accessors
const bool Game::isRunning() const {
	return snakeWindow->isOpen();
}

const int Game::getBlockSize() const {
	return BLOCK_SIZE;
}

const sf::Time Game::getElabsed() const {
	return timeElabsed;
}

void Game::pollEvent() {
	while (snakeWindow->pollEvent(userEvent)) {
		switch (userEvent.type)
		{
		case sf::Event::Closed: {
			snakeWindow->close();
			break;
		}
		case sf::Event::KeyPressed: {
			if (Game::userEvent.key.code == sf::Keyboard::Escape) {
				snakeWindow->close();
				break;
			}
		}
		default:
			break;
		}
	}
}

void Game::updateWorld() {
	/*
		@ returns void

		- gets mouse position relative to the window
	*/
	if ((*player).getPosition() == (*extendPlayerCollectable).item) {
		extendPlayerCollectable->extendPlayer(*player, player->getDirection());
		player->increaseScore();
		extendPlayerCollectable->respawn();
	};

	if ((*player).getPosition() == (*slowSpeedCollectable).item) {
		slowSpeedCollectable->extendPlayer(*player, player->getDirection());
		slowSpeedCollectable->slowPlayerSpeed(*player);
		player->increaseScore();
		slowSpeedCollectable->respawn();
	};

	this->loseIfOutOfBoundries();

}

void Game::update() {
	pollEvent();
	handleUserInput();

	float timestep = 1.0f / player->getSpeed();
	float deltaTime = static_cast<float>(timeElabsed.asSeconds());

	if (timeElabsed.asSeconds() >= timestep) {
		player->update(deltaTime);
		updateWorld();
		timeElabsed -= sf::seconds(timestep);
		if (player->isLost()) {
			player->resetPosition();
		}
	};
	// Calculate delta time for smooth movement

	this->obstacle1->updatePosition(deltaTime);
}

void Game::render() {
	/*
		- Clear window contents
		- Render objects in window
		- Display the frame in window
	*/
	this->snakeWindow->clear(sf::Color(23, 23, 23, 255));

	player->render(*snakeWindow);
	extendPlayerCollectable->render(*snakeWindow);
	if (player->getScore() % 50 == 0 && player->getScore() != 0) {
		slowSpeedCollectable->render(*snakeWindow);
	}
	obstacle1->render(*snakeWindow);
	// Draw stuff here

	this->snakeWindow->display();
}