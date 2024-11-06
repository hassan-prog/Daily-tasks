#pragma once
#include <SFML/Graphics.hpp>

class Snake
{
private:
	sf::Vector2f snakeSize;
	// head
	sf::Color headColor;
	sf::RectangleShape snakeHead;
	sf::Vector2f headPos;
	// body
	sf::Color bodyColor;
	sf::RectangleShape snakeBody;
	sf::Vector2f bodyPos;

	// private functions
	void initVars();
	void initSnake();

public:
	// constructors
	Snake();

	// getters
	const std::vector<sf::RectangleShape> getPlayer() const;
	const sf::RectangleShape getSnakeBody() const;
	// functions
	void moveSnake();
};