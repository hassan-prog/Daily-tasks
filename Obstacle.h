#pragma once
#include <SFML/Graphics.hpp>

class Obstacle
{
private:
	sf::RectangleShape obstacle;
	sf::Vector2f startPosition;
	sf::Vector2f endPosition;
	sf::Vector2f direction;
	float speed;

	void initObstacle();
	void initVars();

public:
	Obstacle();
	
	const sf::RectangleShape& getObstacle() const;
	void updatePosition(float deltaTime);
	void render(sf::RenderWindow& window); // render the obstacle
};

