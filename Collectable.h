#pragma once
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Collectable : private GameObject
{
private:
	int windowHeight = 0;
	int windowWidth = 0;

	sf::CircleShape shape;

	//private functions
	void generateRandomPosition(float& x, float& y);
	void initCollectable();
	void initVars();

public:
	const sf::CircleShape& getShape() const;
	void speed(Snake* snake);
	void health(Snake* snake);
	void score(Snake* snake);
	void respawn();
	void render(sf::RenderWindow& window); // render the collectable

	Collectable();
};

