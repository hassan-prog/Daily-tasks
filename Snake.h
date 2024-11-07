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
	// this is used to store the original speed value in the decreaseSpeed()
	float originalSpeed;
	float speedReductionTimer = 0.0f;  // Duration left for reduced speed

	float speed;
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

public:
	// constructors
	Snake(int blockSize);
	~Snake();

	// getters and setters
	SnakeContainer& getSnakeBody();
	Direction& getDirection();
	sf::Vector2i getPosition();

	void setDirection(Direction dir);
	void increaseSpeed();
	float getSpeed();
	int getLives();
	int getScore();
	void increaseScore();
	void increaseScoreByHundred();
	bool isLost();

	// functions
	void lose(); // handle losing
	void toggleLost();

	void resetPosition(); // reset to the original position
	void cutSnake(int segments);

	void moveSnake();
	void decreaseSpeedTemporary(float duration);
	void update(float deltaTime);
	void render(sf::RenderWindow& window); // render the snake
};