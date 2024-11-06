#include <iostream>
#include "Game.h"


// private functions
void Game::initVariables() {
	this->snakeWindow = nullptr;
	this->videoMode.height = 720;
	this->videoMode.width = 1080;

	this->collectable1 = new Collectable();
	this->obstacle1 = new Obstacle();
	this->player = new Snake();
}

void Game::initWindow() {
	this->snakeWindow->setFramerateLimit(60); // cap 60 FPS

	this->snakeWindow = new sf::RenderWindow(this->videoMode, "sssss-Snake", sf::Style::Titlebar | sf::Style::Close);
}

// Constructors & Destructors
Game::Game() {
	this->initVariables();
	this->initWindow();
}

Game::~Game() {
	delete this->snakeWindow;
	delete this->collectable1;
	delete this->obstacle1;
	delete this->player;
}

//Accessors
const bool Game::isRunning() const
{
	return this->snakeWindow->isOpen();
}



//public functions
void Game::pollEvent() {
	while (this->snakeWindow->pollEvent(this->userEvent)) {
		switch (this->userEvent.type)
		{
		case sf::Event::Closed: {
			this->snakeWindow->close();
			break;
		}
		case sf::Event::KeyPressed: {
			if (Game::Game::userEvent.key.code == sf::Keyboard::Escape) {
				this->snakeWindow->close();
				break;
			}
		}
		default:
			break;
		}
	}
}

void Game::updateMousePositions() {
	/*
		@ returns void

		- gets mouse position relative to the window
	*/
	this->windowMousePos = sf::Mouse::getPosition(*this->snakeWindow);
}

void Game::update() {
	this->pollEvent();
	this->updateMousePositions();

	// Calculate delta time for smooth movement
	float deltaTime = clock.restart().asSeconds();

	this->obstacle1->updatePosition(deltaTime);
}

void Game::render() {
	/*
		- Clear window contents
		- Render objects in window
		- Display the frame in window
	*/
	this->snakeWindow->clear(sf::Color(23, 23, 23, 255));

	for(const auto& part: player->getPlayer()){
		snakeWindow->draw(part);
	}
	this->snakeWindow->draw(collectable1->getShape());
	this->snakeWindow->draw(obstacle1->getObstacle());
	// Draw stuff here

	this->snakeWindow->display();
}

