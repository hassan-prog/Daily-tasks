#include "Snake.h"


//private functions
void Snake::initVars() {
	this->snakeSize = sf::Vector2f(20.0f, 20.0f);
	this->headColor = sf::Color(33, 148, 72, 220);
	this->headPos = sf::Vector2f(30.0f, 30.0f);

	this->bodyColor = sf::Color(86, 102, 58, 180);
	this->bodyPos = sf::Vector2f(10.0f, 30.0f);
}

void Snake::initSnake() {
	//snake head variables
	this->snakeHead.setSize(this->snakeSize);
	this->snakeHead.setPosition(this->headPos);
	this->snakeHead.setFillColor(this->headColor);

	//snake body variables
	this->snakeBody.setSize(this->snakeSize);
	this->snakeBody.setPosition(this->bodyPos);
	this->snakeBody.setFillColor(this->bodyColor);
}

// constructors
Snake::Snake() {
	this->initVars();
	this->initSnake();
}

// functions
const std::vector<sf::RectangleShape> Snake::getPlayer() const {
	return { snakeHead, snakeBody };
}

// functions
void Snake::moveSnake() {

}
