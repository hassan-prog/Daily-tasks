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

	sf::CircleShape shape;

	//private functions
	void generateRandomPosition(int& x, int& y);
	void initCollectable();
	void initVars();

public:
	sf::Vector2i item;

	const sf::CircleShape& getShape() const;
	void speed(Snake* snake);
	void health(Snake* snake);
	void score(Snake* snake);
	void respawn();
	void render(sf::RenderWindow& window); // render the collectable

	Collectable();
};

