#pragma once

#include <SFML/Graphics.hpp>
#include "Obstacle.h"
#include "Collectable.h"
#include "Snake.h"

class Game
{
private:
	sf::Event userEvent;
	sf::RenderWindow* snakeWindow;
	sf::VideoMode videoMode;
	sf::Clock clock;
	sf::Time timeElabsed;

	int GRID_HEIGHT;
	int GRID_WIDTH;
	int BLOCK_SIZE;

	//Game objects
	Collectable* extendPlayerCollectable;
	sf::Color extendPlayerCollectableColor;

	Collectable* slowSpeedCollectable;
	sf::Color slowSpeedCollectableColor;

	//Collectable* extendPlayerCollectable;
	Obstacle* obstacle1;
	Snake* player;


	//Mouse positions
	sf::Vector2i windowMousePos;

	void initVariables();
	void initWindow();
	void loseIfOutOfBoundries();

public:
	Game();
	~Game();

	const bool isRunning() const;

	const int getBlockSize() const;
	const sf::Time getElabsed() const;

	// Functions
	void pollEvent();
	void update();
	void updateWorld();
	void render();
	void restartClock();
	void handleUserInput();
};

