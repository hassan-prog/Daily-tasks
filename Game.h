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
	sf::Text healthText;
	sf::Text scoreText;
	sf::Font font;

	// Game objects
	Snake* player;

	// Collectables
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

	// Obstacles
	Obstacle* bigObstacleHorizontal;
	bool bigObstacleHorizontalIsVisible;

	Obstacle* bigObstacleVertical;
	bool bigObstacleVerticalIsVisible;

	bool hasCollidedWithObstacle;
	
	Obstacle* loseHealthObstacle;

	void initVariables();
	void initWindow();
	void loseIfOutOfBoundries();
	void initUI(const Snake& player);

	const sf::Time getElabsed() const;

	// Functions
	void updateUI(const Snake& player);
	void pollEvent();
	void updateWorld();
	void restartGame();
	void handleUserInput();

public:
	Game();
	~Game();

	const int getBlockSize() const;
	const bool isRunning() const;

	void restartClock();
	void update();
	void render();
};

