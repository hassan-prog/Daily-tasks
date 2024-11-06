#pragma once
#include <SFML/Graphics.hpp>


struct SnakeSegment {
	SnakeSegment(int x, int y) : position(x, y) {}
	sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;

enum class Direction { None, Up, Down, Left, Right };

class Snake
{
private:
	int speed;
	int lives;
	int score;
	int size;
	bool lost;

	SnakeContainer snakeBody;

	Direction direction;
	sf::RectangleShape rectBody; // used in rendering the snake


	sf::Vector2f snakeSize;

	// head
	sf::Color headColor;
	sf::Vector2f headPos;

	// body
	sf::Color bodyColor;
	sf::Vector2f bodyPos;

	// private functions
	void initVars();
	void checkCollision();
	//void initSnake();

public:
	// constructors
	Snake(int blockSize);
	~Snake();

	// getters and setters
	Direction getDirection();
	void setDirection(Direction dir);
	int getSpeed();
	int getLives();
	int getScore();
	sf::Vector2i getPosition();
	void increaseScore();
	bool isLost();

	// functions
	void lose(); // handle losing
	void toggleLost();

	void grow(); 
	void resetPosition(); // reset to the original position
	void cutSnake(int segments);

	void moveSnake();
	void update();
	void render(sf::RenderWindow window); // render the snake
};