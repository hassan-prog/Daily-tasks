#include "Snake.h"

//private functions
void Snake::initVars() {
	snakeSize = sf::Vector2f(20.0f, 20.0f);

	//snake head variables
	headColor = sf::Color(33, 148, 72, 220);
	headPos = sf::Vector2f(30.0f, 30.0f);

	//snake body variables
	bodyColor = sf::Color(86, 102, 58, 180);
	bodyPos = sf::Vector2f(10.0f, 30.0f);
}

//void Snake::initSnake() {
//	// snake head
//	this->snakeHead.setSize(this->snakeSize);
//	this->snakeHead.setPosition(this->headPos);
//	this->snakeHead.setFillColor(this->headColor);
//
//	// snake body
//	this->snakeBody.setSize(this->snakeSize);
//	this->snakeBody.setPosition(this->bodyPos);
//	this->snakeBody.setFillColor(this->bodyColor);
//}

void Snake::checkCollision() {
	if (snakeBody.size() < 5) return;
	SnakeSegment& head = snakeBody.front();

	// begin is of type Iterator
	for (auto iter = snakeBody.begin() + 1; iter != snakeBody.end(); ++iter) {
		if (iter->position == head.position) {
			int segments = snakeBody.end() - iter;
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
Direction Snake::getDirection() { return direction; }

void Snake::setDirection(Direction dir) { direction = dir; }

int Snake::getSpeed() { return speed; }

int Snake::getLives() { return lives; }

int Snake::getScore() { return score; }

sf::Vector2i Snake::getPosition() {
	return (snakeBody.empty() ? sf::Vector2i(1, 1) : snakeBody.front().position);
}

bool Snake::isLost() { return lost; }

void Snake::lose() { lost = true; }

void Snake::toggleLost() { lost = !lost; }

void Snake::increaseScore() { score += 10; }

// functions
void Snake::resetPosition() {
	snakeBody.clear();

	snakeBody.push_back(SnakeSegment(5, 7));
	snakeBody.push_back(SnakeSegment(5, 6));
	snakeBody.push_back(SnakeSegment(5, 5));

	setDirection(Direction::None);
	speed = 15;
	score = 0;
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

// updates the state of the snake for a fixed time-step
void Snake::update() {
	if (snakeBody.empty()) return;
	if (direction == Direction::None) return;
	moveSnake();
	checkCollision();
}

// render the snake on the screen
void Snake::render(sf::RenderWindow& window) {
	if (snakeBody.empty()) return;

	// draws the head of the snake
	auto head = snakeBody.begin();
	rectBody.setFillColor(headColor);
	rectBody.setPosition(head->position.x * size, head->position.y * size);
	window.draw(rectBody);

	// draws the body of the snake; "iter" being each segment
	rectBody.setFillColor(bodyColor);
	for (auto iter = snakeBody.begin() + 1; iter != snakeBody.end(); ++iter) {
		rectBody.setPosition(iter->position.x * size, iter->position.y * size);
		window.draw(rectBody);
	}
}

// extend snake tail
void Snake::grow() {
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
	}

}
