#include "Snake.h"
#include <iostream>

//private functions
void Snake::initVars() {
	score = 0;
	speed = 11;
	lives = 3;
	lost = false;
	cooldownTimer = 0.0f;

	snakeSize = sf::Vector2f(20.0f, 20.0f);

	//snake head variables
	headColor = sf::Color(33, 148, 72, 220);
	headPos = sf::Vector2f(30.0f, 30.0f);

	//snake body variables
	bodyColor = sf::Color(86, 102, 58, 180);
	bodyPos = sf::Vector2f(10.0f, 30.0f);
}

void Snake::checkCollision() {
	if (snakeBody.size() < 5) return;
	SnakeSegment& head = snakeBody.front();

	// begin() is of type Iterator
	for (auto iter = snakeBody.begin() + 1; iter != snakeBody.end(); ++iter) {
		if (iter->position == head.position) {
			int segments = static_cast<int>(snakeBody.end() - iter);
			cutSnake(segments);
			break;
		}
	}
}

// constructors & destructors
Snake::Snake(int blockSize) {
	initVars();
	size = blockSize;
	rectBody.setSize(sf::Vector2f(size - 1, size - 1));
	resetPosition();
}

Snake::~Snake() { }


// getters and setters
Direction& Snake::getDirection() { return direction; }
SnakeContainer& Snake::getSnakeBody() { return snakeBody; }
void Snake::setDirection(Direction dir) { direction = dir; }
void Snake::increaseSpeed() { if (speed <= 25) speed += 0.5; }
float Snake::getSpeed() { return speed; }
int Snake::getLives() const { return lives; }
void Snake::increaseLives() { ++lives; }
int Snake::getScore() const { return score; }
sf::Vector2i Snake::getPosition() {
	return (snakeBody.empty() ? sf::Vector2i(1, 1) : snakeBody.front().position);
}
bool Snake::isLost() { return lost; }
void Snake::lose() { lost = true; }
void Snake::toggleLost() { lost = !lost; }
void Snake::resetScore() { score = 0; }
void Snake::resetCoolDown() { cooldownTimer = 0.0f; }
void Snake::startCoolDown() { cooldownTimer = cooldownDuration; }
void Snake::increaseScore() { score += 10; }
void Snake::increaseScoreByHundred() { score += 100; }
void Snake::loseLives() {
	if (lives > 6) {
		lives -= 3;
		snakeBody.pop_back();
		snakeBody.pop_back();
		snakeBody.pop_back();
	}
	else {
		lose();
	}
	std::cout << lives << '\n';
}

// functions
void Snake::resetPosition() {
	snakeBody.clear();

	snakeBody.push_back(SnakeSegment(5, 7));
	snakeBody.push_back(SnakeSegment(5, 6));
	snakeBody.push_back(SnakeSegment(5, 5));

	setDirection(Direction::None);
	resetScore();
	speed = 11;
	lives = 3;
	lost = false;
}

void Snake::cutSnake(int segments) {
	for (int i = 0; i < segments; i++)
		snakeBody.pop_back();

	--lives;
	if (!lives) {
		lose();
		return;
	}
}

// player movement mechanics
void Snake::moveSnake() {
	for (int i = snakeBody.size() - 1; i > 0; --i) {
		snakeBody[i].position = snakeBody[i - 1].position;
	}
	if (direction == Direction::Up) {
		--snakeBody[0].position.y;
	}
	if (direction == Direction::Down) {
		++snakeBody[0].position.y;
	}
	if (direction == Direction::Right) {
		++snakeBody[0].position.x;
	}
	if (direction == Direction::Left) {
		--snakeBody[0].position.x;
	}
}

void Snake::decreaseSpeedTemporary(float duration) {
	if (speedReductionTimer <= 0.0f) {
		originalSpeed = speed;
		this->speed /= 2;
		speedReductionTimer = duration;
	}
}

// updates the state of the snake for a fixed time-step
void Snake::update(float deltaTime) {
	if (cooldownTimer > 0) {
		cooldownTimer -= deltaTime;
		return;
	}

	if (snakeBody.empty() || direction == Direction::None) return;

	if (speedReductionTimer > 0.0f) {
		speedReductionTimer -= deltaTime;

		if (speedReductionTimer <= 0.0f) {
			speed = originalSpeed;
		}
	}

	moveSnake();
	checkCollision();
}

// render the snake on the screen
void Snake::render(sf::RenderWindow& window) {
	if (snakeBody.empty()) return;

	// draws the head of the snake
	auto head = snakeBody.begin();
	rectBody.setFillColor(headColor);
	rectBody.setPosition(static_cast<float>(head->position.x * size), static_cast<float>(head->position.y * size));
	window.draw(rectBody);

	// draws the body of the snake; "iter" being each segment
	rectBody.setFillColor(bodyColor);
	for (auto iter = snakeBody.begin() + 1; iter != snakeBody.end(); ++iter) {
		rectBody.setPosition(static_cast<float>(iter->position.x * size), static_cast<float>(iter->position.y * size));
		window.draw(rectBody);
	}
}