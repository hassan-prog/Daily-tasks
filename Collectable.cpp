#include "Collectable.h"
#include <iostream>


//private functions
void Collectable::initCollectable() {
	generateRandomPosition(objPositionX, objPositionY);
	shape.setRadius(8.0f);
	shape.setPosition(item.x * blockSize, item.y * blockSize);
	shape.setFillColor(sf::Color::Yellow);
}

void Collectable::initVars() {
	windowHeight = 600;
	windowWidth = 800;
	blockSize = 16;
}

void Collectable::generateRandomPosition(int& maxX, int& maxY) {
	maxX = (windowWidth / blockSize) - 2;
	maxY = (windowHeight / blockSize) - 2;
	item = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
}

//Constructors & Destructors
Collectable::Collectable() {
	initVars();
	initCollectable();
}

const sf::CircleShape& Collectable::getShape() const
{
	return shape;
}

//Functions
void Collectable::speed(Snake* snake) {

}

void Collectable::health(Snake* snake) {

}

void Collectable::score(Snake* snake) {

}

void Collectable::respawn() {
	generateRandomPosition(objPositionX, objPositionY);
	shape.setPosition(item.x * blockSize, item.y * blockSize);
}

void Collectable::render(sf::RenderWindow& window) {
	window.draw(shape);
}

