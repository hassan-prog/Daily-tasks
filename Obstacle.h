#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"

class Obstacle
{
private:
	sf::RectangleShape obstacle;
	sf::Vector2f startPosition;
	sf::Vector2f endPosition;
	sf::Vector2f direction;
	float speed;

	void initObstacle(sf::Vector2f startPosition, sf::Vector2f endPosition, sf::Color color, sf::Vector2f size, int speed);
	void initVars();

public:
	Obstacle(sf::Vector2f startPosition, sf::Vector2f endPosition, sf::Color color, sf::Vector2f size, int speed);
	
	const sf::RectangleShape& getObstacle() const;

	bool checkCollision(const std::vector<SnakeSegment>& player, int segmentSize) const;
	void respawn();
	void updatePosition(float deltaTime);
	void render(sf::RenderWindow& window); // render the obstacle
};

