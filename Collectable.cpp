#include "Collectable.h"
#include <iostream>


//private functions
void Collectable::initCollectable(sf::Color color) {
	this->collectableColor = color;
	generateRandomPosition(objPositionX, objPositionY);
	shape.setRadius(this->blockSize / 2);
	shape.setPosition(item.x * this->blockSize, item.y * this->blockSize);
	shape.setFillColor(collectableColor);
}

void Collectable::initVars() {
	windowHeight = 600;
	windowWidth = 800;
}

void Collectable::generateRandomPosition(int& maxX, int& maxY) {
	maxX = (windowWidth / this->blockSize) - 2;
	maxY = (windowHeight / this->blockSize) - 2;
	item = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
}

//Constructors & Destructors
Collectable::Collectable(sf::Color color, int blockSize) {
	this->blockSize = blockSize;
	initVars();
	initCollectable(color);
}

const sf::CircleShape& Collectable::getShape() const
{
	return shape;
}

//Functions

void Collectable::slowPlayerSpeed(Snake& player) {
	if (player.getSpeed() <= 10) return;
	player.decreaseSpeedTemporary(8.0f);
}

// extend snake tail
void Collectable::extendPlayer(Snake& player, Direction& direction) {
	SnakeContainer& snakeBody = player.getSnakeBody();
	if (snakeBody.empty())
		return;
	// last snake segment
	SnakeSegment& tailHead = snakeBody[snakeBody.size() - 1];

	// if there are more than 1 segment in the snake
	if (snakeBody.size() > 1) {
		// the segment right before the tailHead
		SnakeSegment& tailBone = snakeBody[snakeBody.size() - 2];

		// grows vertically (because they are on the same x line)
		if (tailHead.position.x == tailBone.position.x) {
			if (tailHead.position.y > tailBone.position.y) {
				snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y + 1));
			}
			else {
				snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y - 1));
			}
		}
		// grows horizontally (because they are on the same y line)
		else if (tailHead.position.y == tailBone.position.y) {
			if (tailHead.position.x > tailBone.position.x) {
				snakeBody.push_back(SnakeSegment(tailHead.position.x + 1, tailHead.position.y));
			}
			else {
				snakeBody.push_back(SnakeSegment(tailHead.position.x - 1, tailHead.position.y));
			}
		}
		player.increaseSpeed();

	}
	// if there's only 1 segment in the snake
	else {
		if (direction == Direction::Up) {
			snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y + 1));
		}
		else if (direction == Direction::Down) {
			snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y - 1));
		}
		else if (direction == Direction::Left) {
			snakeBody.push_back(SnakeSegment(tailHead.position.x + 1, tailHead.position.y));
		}
		else if (direction == Direction::Right) {
			snakeBody.push_back(SnakeSegment(tailHead.position.x - 1, tailHead.position.y));
		}
		player.increaseSpeed();

	}
}

void Collectable::respawn() {
	generateRandomPosition(objPositionX, objPositionY);
	shape.setPosition(item.x * this->blockSize, item.y * this->blockSize);
}

void Collectable::render(sf::RenderWindow& window) {
	window.draw(shape);
}

