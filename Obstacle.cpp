#include "Obstacle.h"

// Private functions
void Obstacle::initObstacle(
	sf::Vector2f startPosition, sf::Vector2f endPosition,
	sf::Color color, sf::Vector2f size, int speed
) 
{
	this->startPosition = startPosition;
	this->endPosition = endPosition;

	obstacle.setPosition(startPosition);
	obstacle.setSize(size);
	obstacle.setFillColor(color);
	obstacle.setOutlineColor(sf::Color::White);
	obstacle.setOutlineThickness(1.0f);
}

void Obstacle::initVars()
{
	speed = 20.0f;

	// setting the direction
	direction = endPosition - startPosition;

	/*
		- control movement speed independently of the vector’s length
		- Without normalization, the speed would vary depending on
		the distance between startPosition and endPosition.
	*/
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0)
		direction /= length;
}


// Constructors & Destructors
Obstacle::Obstacle(sf::Vector2f startPosition, sf::Vector2f endPosition, sf::Color color, sf::Vector2f size, int speed) {
	initVars();
	initObstacle(startPosition, endPosition, color, size, speed);
}

const sf::RectangleShape& Obstacle::getObstacle() const {
	return obstacle;
}

bool Obstacle::checkCollision(const std::vector<SnakeSegment>& player, int segmentSize) const {
	sf::FloatRect obstacleBounds = obstacle.getGlobalBounds();

	for (const auto& segment : player) {
		sf::FloatRect segmentBounds(
			segment.position.x * segmentSize,
			segment.position.y * segmentSize,
			segmentSize,
			segmentSize
		);

		if (obstacleBounds.intersects(segmentBounds)) {
			return true;
		}
	}
	return false;
}

void Obstacle::respawn() {
	obstacle.setPosition(startPosition);
}


// Functions
void Obstacle::updatePosition(float deltaTime) {
	sf::Vector2f currentPosition = this->obstacle.getPosition();

	float distanceToStart = std::sqrt(
		std::pow(currentPosition.x - startPosition.x, 2) +
		std::pow(currentPosition.y - startPosition.y, 2));

	float distanceToEnd = std::sqrt(
		std::pow(currentPosition.x - endPosition.x, 2) +
		std::pow(currentPosition.y - endPosition.y, 2));

	if (distanceToEnd < 1.0f) {
		this->direction = startPosition - endPosition;
	}
	else if (distanceToStart < 1.0f) {
		this->direction = endPosition - startPosition;
	}

	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0)
		direction /= length;

	this->obstacle.move(direction * speed * deltaTime);
}

void Obstacle::render(sf::RenderWindow& window) {
	window.draw(this->obstacle);
}
