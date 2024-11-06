#include "Obstacle.h"

// Private functions
void Obstacle::initObstacle() {
	this->obstacle.setPosition(this->startPosition);
	this->obstacle.setSize(sf::Vector2f(100.0f, 100.0f));
	this->obstacle.setFillColor(sf::Color::Red);
	this->obstacle.setOutlineColor(sf::Color::White);
	this->obstacle.setOutlineThickness(2.0f);
	this->obstacle.setOrigin(this->obstacle.getSize().x / 2, this->obstacle.getSize().y / 2);
}

void Obstacle::initVars()
{
	// start and end position for back and forth movement
	this->startPosition = sf::Vector2f(360.f, 540.f);
	this->endPosition = sf::Vector2f(280.f, 400.f);
	this->speed = 50.f;

	// setting the direction
	this->direction = endPosition - startPosition;

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
Obstacle::Obstacle() {
	this->initVars();
	this->initObstacle();
}

const sf::RectangleShape& Obstacle::getObstacle() const {
	return this->obstacle;
}


// Functions
void Obstacle::updatePosition(float deltaTime) {
	sf::Vector2f currentPosition = this->obstacle.getPosition();

	if (std::abs(currentPosition.x - endPosition.x) < 1.0f
		&& std::abs(currentPosition.y - endPosition.y) < 1.0f)
	{
		this->direction = startPosition - endPosition;
	}
	else if (std::abs(currentPosition.x - startPosition.x) < 1.0f
		&& std::abs(currentPosition.y - startPosition.y) < 1.0f)
	{
		this->direction = endPosition - startPosition;
	}

	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0)
		direction /= length;

	this->obstacle.move(direction * speed * deltaTime);
}

void Obstacle::render(sf::RenderWindow& window) {
	window.draw(obstacle);
}
