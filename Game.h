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
	float deltaTime;

	int GRID_HEIGHT;
	int GRID_WIDTH;
	int BLOCK_SIZE;

	//Game objects
	Collectable* extendPlayerCollectable;
	sf::Color extendPlayerCollectableColor;

	Collectable* slowSpeedCollectable;
	sf::Color slowSpeedCollectableColor;
	bool slowSpeedCollectableIsVisible;

	Collectable* increaseScoreCollectable;
	sf::Color increaseScoreCollectableColor;
	float increaseScoreByHundredSpawnTimer;          // Counts up to 15 seconds
	float increaseScoreByHundredActiveDurationTimer; // Counts down from 5 seconds when spawned
	bool increaseScoreByHundredIsVisible;            // Tracks if the item is currently active

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

