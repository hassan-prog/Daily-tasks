#pragma once

#include <SFML/Graphics.hpp>
#include "Obstacle.h"
#include "Collectable.h"

class Game
{
private:
	sf::Event userEvent;
	sf::RenderWindow* snakeWindow;
	sf::VideoMode videoMode;
	sf::Clock clock;

	//Game objects
	Obstacle* obstacle1;
	Collectable* collectable1;

	//Mouse positions
	sf::Vector2i windowMousePos;

	void initVariables();
	void initWindow();

public:
	Game();
	~Game();

	const bool isRunning() const;

	// Functions
	void pollEvent();
	void update();
	void updateMousePositions();
	void render();
};

