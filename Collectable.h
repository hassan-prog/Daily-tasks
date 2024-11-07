#pragma once
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Collectable : private GameObject
{
private:
	int windowHeight;
	int windowWidth;
	int blockSize;
	sf::Color collectableColor;

	sf::CircleShape shape;

	//private functions
	void generateRandomPosition(int& x, int& y);
	void initCollectable(sf::Color color);
	void initVars();

public:
	sf::Vector2i item;

	const sf::CircleShape& getShape() const;
	void slowPlayerSpeed(Snake& snakeBody);
	void extendPlayer(Snake& snakeBody, Direction& direction);
	void respawn();
	void render(sf::RenderWindow& window); // render the collectable

	Collectable(sf::Color color, int blockSize);
};

