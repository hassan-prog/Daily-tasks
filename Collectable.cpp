#include "Collectable.h"
#include <iostream>


//private functions
void Collectable::initCollectable() {
	this->generateRandomPosition(objPositionX, objPositionY);
	this->shape.setRadius(40.0f);
	this->shape.setPosition(sf::Vector2f(this->objPositionX, this->objPositionY));
	this->shape.setFillColor(sf::Color::Yellow);
}

void Collectable::initVars() {
	this->windowHeight = 720;
	this->windowWidth = 1080;
	this->objPositionX = 30;
	this->objPositionY = 30;
}

void Collectable::generateRandomPosition(float& x, float& y) {
		x = rand() % (windowWidth - 2) + 1;
		y = rand() % (windowHeight - 2) + 1;
}

//Constructors & Destructors
Collectable::Collectable() {
	this->initVars();
	this->initCollectable();
}

const sf::CircleShape& Collectable::getShape() const
{
	return this->shape;
}

//Functions
void Collectable::speed(Snake* snake) {

}

void Collectable::health(Snake* snake) {

}

void Collectable::score(Snake* snake) {

}

