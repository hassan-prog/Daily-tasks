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

	void initObstacle(sf::Vector2f startPosition, sf::Vector2f endPosition);
	void initVars();

public:
	Obstacle(sf::Vector2f startPosition, sf::Vector2f endPosition);
	
	const sf::RectangleShape& getObstacle() const;
	void respawn();
	void updatePosition(float deltaTime);
	void render(sf::RenderWindow& window); // render the obstacle
};

