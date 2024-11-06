#include "Collectable.h"
#include <iostream>


//private functions
void Collectable::initCollectable() {
	generateRandomPosition(objPositionX, objPositionY);
	shape.setRadius(40.0f);
	shape.setPosition(objPositionX, objPositionY);
	shape.setFillColor(sf::Color::Yellow);
}

void Collectable::initVars() {
	windowHeight = 720;
	windowWidth = 1080;
	objPositionX = 30;
	objPositionY = 30;
}

void Collectable::generateRandomPosition(float& maxX, float& maxY) {
	maxX = rand() % ((windowWidth / 16) - 2) + 1;
	maxY = rand() % ((windowHeight / 16) - 2) + 1;
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
	shape.setPosition(objPositionX, objPositionY);
}

void Collectable::render(sf::RenderWindow& window) {
	window.draw(shape);
}

