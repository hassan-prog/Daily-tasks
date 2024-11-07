#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


// Snake block
struct SnakeSegment {
	SnakeSegment(int x, int y) : position(x, y) {}
	sf::Vector2i position;
};

// The whole snake (Head + Body)
using SnakeContainer = std::vector<SnakeSegment>;

enum class Direction { None, Up, Down, Left, Right };

SnakeContainer snakeBody;


// private functions
void initObstacleVars();
void checkCollision();

// Snake-related functions
SnakeContainer& getSnakeBody();
Direction& getDirection();
sf::Vector2i getPosition();

void setDirection(Direction dir);
void increaseSpeed();
float getSpeed();
int getLives();
void increaseLives();
void loseLives();
int getScore();
void increaseScore();
void increaseScoreByHundred();
bool isLost();
void lose(); // handle losing
void toggleLost();
void resetScore();
void resetCoolDown();
void startCoolDown();
void resetPosition(); // reset to the original position
void cutSnake(int segments);

void moveSnake();
void decreaseSpeedTemporary(float duration);
void update(float deltaTime);
void render(sf::RenderWindow& window);

// Collectable-related functions
void generateRandomPosition(int& maxX, int& maxY, sf::Vector2i& item);

// Obstacle-related functions
void initVariables();

float speed = 10, speedReductionTimer = 0.0f, cooldownDuration = 2.0f, cooldownTimer = 0.0f, originalSpeed = 0.0f;
int lives = 3, score = 0, size = 16;
bool lost = false;
Direction direction;
sf::RectangleShape rectBody; // used in rendering the snake
sf::Vector2f snakeSize = sf::Vector2f(20.0f, 20.0f), headPos = sf::Vector2f(30.0f, 30.0f), bodyPos = sf::Vector2f(10.0f, 30.0f);
sf::Color headColor = sf::Color(33, 148, 72, 220), bodyColor = sf::Color(86, 102, 58, 180);

int objPositionX;
int objPositionY;

// Collectable variables
int extendPlayerCollectablePositionX, extendPlayerCollectablePositionY;
int slowSpeedCollectablePositionX, slowSpeedCollectablePositionY;
int increaseScoreCollectablePositionX, increaseScoreCollectablePositionY;

sf::Vector2i extendPlayerCollectableItem, slowSpeedCollectableItem, increaseScoreCollectableItem;

sf::Color extendPlayerCollectableColor = sf::Color::Red;
sf::Color slowSpeedCollectableColor = sf::Color::Green;
sf::Color increaseScoreCollectableColor = sf::Color::Blue;

sf::CircleShape extendPlayerCollectableShape, slowSpeedCollectableShape, increaseScoreCollectableShape;

// Window settings
const int windowHeight = 600;
const int windowWidth = 800;

// Other properties
const int collectableBlockSize = 16;



void initializeCollectable(int& posX, int& posY, sf::Vector2i& item, sf::CircleShape& shape, sf::Color color) {
	generateRandomPosition(posX, posY, item);
	shape.setRadius(collectableBlockSize / 2);
	shape.setPosition(item.x * collectableBlockSize, item.y * collectableBlockSize);
	shape.setFillColor(color);
}


void generateRandomPosition(int& posX, int& posY, sf::Vector2i& item) {
	int maxX = (windowWidth / collectableBlockSize) - 2;
	int maxY = (windowHeight / collectableBlockSize) - 2;
	item = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
	posX = item.x;
	posY = item.y;
}

void renderCollectable(sf::RenderWindow& window, const sf::CircleShape& shape) {
	window.draw(shape);
}

void slowPlayerSpeed() {
	if (getSpeed() <= 10) return;
	decreaseSpeedTemporary(8.0f);
}

void extendPlayer(Direction direction) {
	if (snakeBody.empty()) return;

	SnakeSegment& tailHead = snakeBody[snakeBody.size() - 1];

	if (snakeBody.size() > 1) {
		SnakeSegment& tailBone = snakeBody[snakeBody.size() - 2];

		if (tailHead.position.x == tailBone.position.x) {
			if (tailHead.position.y > tailBone.position.y) {
				snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y + 1));
			}
			else {
				snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y - 1));
			}
		}
		else if (tailHead.position.y == tailBone.position.y) {
			if (tailHead.position.x > tailBone.position.x) {
				snakeBody.push_back(SnakeSegment(tailHead.position.x + 1, tailHead.position.y));
			}
			else {
				snakeBody.push_back(SnakeSegment(tailHead.position.x - 1, tailHead.position.y));
			}
		}

	}
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
	increaseLives();
	increaseSpeed();
}

void respawnCollectable(int& posX, int& posY, sf::Vector2i& item, sf::CircleShape& shape) {
	generateRandomPosition(posX, posY, item);
	shape.setPosition(item.x * collectableBlockSize, item.y * collectableBlockSize);
}




sf::RectangleShape bigObstacleHorizontalShape, bigObstacleVerticalShape, loseHealthObstacleShape;
sf::Vector2f bigObstacleHorizontalstartPosition = sf::Vector2f(360.0f, 0.0f);
sf::Vector2f bigObstacleHorizontalendPosition = sf::Vector2f(360.0f, 520.0f);
sf::Vector2f bigObstacleHorizontalSize = sf::Vector2f(80.0f, 80.0f);
sf::Color bigObstacleHorizontalColor = sf::Color::Red;

sf::Vector2f bigObstacleVerticalstartPosition = sf::Vector2f(720.0f, 260.0f);
sf::Vector2f bigObstacleVerticalendPosition = sf::Vector2f(0.0f, 260.0f);
sf::Vector2f bigObstacleVerticalSize = sf::Vector2f(80.0f, 80.0f);
sf::Color bigObstacleVerticalColor = sf::Color(190, 59, 62);

sf::Vector2f loseHealthObstaclestartPosition = sf::Vector2f(750.0f, 575.0f);
sf::Vector2f loseHealthObstacleendPosition = sf::Vector2f(50.0f, 50.0f);
sf::Vector2f loseHealthObstacleSize = sf::Vector2f(40.0f, 40.0f);
sf::Color loseHealthObstacleColor = sf::Color::Yellow;

sf::Vector2f obs1Direction;
sf::Vector2f obs2Direction;
sf::Vector2f obs3Direction;

float bigObstacleSpeed = 20.0f;
float normalObstacleSpeed = 30.0f;

void initObstacle()
{
	bigObstacleHorizontalShape.setPosition(bigObstacleHorizontalstartPosition);
	bigObstacleVerticalShape.setPosition(bigObstacleVerticalstartPosition);
	loseHealthObstacleShape.setPosition(loseHealthObstaclestartPosition);

	bigObstacleHorizontalShape.setSize(bigObstacleHorizontalSize);
	bigObstacleVerticalShape.setSize(bigObstacleVerticalSize);
	loseHealthObstacleShape.setSize(loseHealthObstacleSize);

	bigObstacleHorizontalShape.setFillColor(bigObstacleHorizontalColor);
	bigObstacleVerticalShape.setFillColor(bigObstacleVerticalColor);
	loseHealthObstacleShape.setFillColor(loseHealthObstacleColor);

	bigObstacleHorizontalShape.setOutlineColor(sf::Color::White);
	bigObstacleVerticalShape.setOutlineColor(sf::Color::White);
	loseHealthObstacleShape.setOutlineColor(sf::Color::White);

	bigObstacleHorizontalShape.setOutlineThickness(1.0f);
	bigObstacleVerticalShape.setOutlineThickness(1.0f);
	loseHealthObstacleShape.setOutlineThickness(1.0f);
}

void initObstacleVars() {
	speed = 20.0f;

	// setting the direction
	obs1Direction = bigObstacleHorizontalendPosition - bigObstacleHorizontalstartPosition;
	obs2Direction = bigObstacleVerticalendPosition - bigObstacleVerticalstartPosition;
	obs3Direction = loseHealthObstacleendPosition - loseHealthObstaclestartPosition;

	/*
		- control movement speed independently of the vector’s length
		- Without normalization, the speed would vary depending on
		the distance between startPosition and endPosition.
	*/
	float length1 = std::sqrt(obs1Direction.x * obs1Direction.x + obs1Direction.y * obs1Direction.y);
	float length2 = std::sqrt(obs2Direction.x * obs2Direction.x + obs2Direction.y * obs2Direction.y);
	float length3 = std::sqrt(obs3Direction.x * obs3Direction.x + obs3Direction.y * obs3Direction.y);
	if (length1 != 0)
		obs1Direction /= length1;
	if (length2 != 0)
		obs2Direction /= length2;
	if (length3 != 0)
		obs3Direction /= length3;
}


void initializeObstacle() {
	initObstacleVars();
	initObstacle();
}

bool checkCollision(const std::vector<SnakeSegment>& player, int segmentSize) {
	sf::FloatRect obstacle3Bounds = loseHealthObstacleShape.getGlobalBounds();

	for (const auto& segment : player) {
		sf::FloatRect segmentBounds(
			segment.position.x * segmentSize,
			segment.position.y * segmentSize,
			segmentSize,
			segmentSize
		);

		if (obstacle3Bounds.intersects(segmentBounds)) {
			return true;
		}
	}
	return false;
}
void respawnObstacles() {
	bigObstacleHorizontalShape.setPosition(bigObstacleHorizontalstartPosition);
	bigObstacleVerticalShape.setPosition(bigObstacleVerticalstartPosition);
	loseHealthObstacleShape.setPosition(loseHealthObstaclestartPosition);
}
void updatePosition(float deltaTime) {
	sf::Vector2f currentHorizontalObstaclePosition = bigObstacleHorizontalShape.getPosition();
	sf::Vector2f currentVerticalObstaclePosition = bigObstacleVerticalShape.getPosition();
	sf::Vector2f currentloseHealthObstaclePosition = loseHealthObstacleShape.getPosition();

	float horizontalDistanceToStart = std::sqrt(
		std::pow(currentHorizontalObstaclePosition.x - bigObstacleHorizontalstartPosition.x, 2) +
		std::pow(currentHorizontalObstaclePosition.y - bigObstacleHorizontalstartPosition.y, 2));

	float horizontalDistanceToEnd = std::sqrt(
		std::pow(currentHorizontalObstaclePosition.x - bigObstacleHorizontalendPosition.x, 2) +
		std::pow(currentHorizontalObstaclePosition.y - bigObstacleHorizontalendPosition.y, 2));

	float verticalDistanceToStart = std::sqrt(
		std::pow(currentVerticalObstaclePosition.x - bigObstacleVerticalstartPosition.x, 2) +
		std::pow(currentVerticalObstaclePosition.y - bigObstacleVerticalstartPosition.y, 2));

	float verticalDistanceToEnd = std::sqrt(
		std::pow(currentVerticalObstaclePosition.x - bigObstacleVerticalendPosition.x, 2) +
		std::pow(currentVerticalObstaclePosition.y - bigObstacleVerticalendPosition.y, 2));

	float loseHealthDistanceToStart = std::sqrt(
		std::pow(currentloseHealthObstaclePosition.x - loseHealthObstaclestartPosition.x, 2) +
		std::pow(currentloseHealthObstaclePosition.y - loseHealthObstaclestartPosition.y, 2));

	float loseHealthDistanceToEnd = std::sqrt(
		std::pow(currentloseHealthObstaclePosition.x - loseHealthObstacleendPosition.x, 2) +
		std::pow(currentloseHealthObstaclePosition.y - loseHealthObstacleendPosition.y, 2));

	if (horizontalDistanceToEnd < 1.0f) {
		obs1Direction = bigObstacleHorizontalstartPosition - bigObstacleHorizontalendPosition;
	}
	else if (horizontalDistanceToStart < 1.0f) {
		obs1Direction = bigObstacleHorizontalendPosition - bigObstacleHorizontalstartPosition;
	}

	if (verticalDistanceToEnd < 1.0f) {
		obs2Direction = bigObstacleVerticalstartPosition - bigObstacleVerticalendPosition;
	}
	else if (verticalDistanceToStart < 1.0f) {
		obs2Direction = bigObstacleVerticalendPosition - bigObstacleVerticalstartPosition;
	}

	if (loseHealthDistanceToEnd < 1.0f) {
		obs3Direction = loseHealthObstaclestartPosition - loseHealthObstacleendPosition;
	}
	else if (loseHealthDistanceToStart < 1.0f) {
		obs3Direction = loseHealthObstacleendPosition - loseHealthObstaclestartPosition;
	}

	float horizontalLength = std::sqrt(obs1Direction.x * obs1Direction.x + obs1Direction.y * obs1Direction.y);
	float verticalLength = std::sqrt(obs2Direction.x * obs2Direction.x + obs2Direction.y * obs2Direction.y);
	float loseHealthLength = std::sqrt(obs3Direction.x * obs3Direction.x + obs3Direction.y * obs3Direction.y);

	if (horizontalLength != 0)
		obs1Direction /= horizontalLength;

	if (verticalLength != 0)
		obs2Direction /= verticalLength;

	if (loseHealthLength != 0)
		obs3Direction /= loseHealthLength;

	bigObstacleHorizontalShape.move(obs1Direction * bigObstacleSpeed * deltaTime);
	bigObstacleVerticalShape.move(obs2Direction * bigObstacleSpeed * deltaTime);
	loseHealthObstacleShape.move(obs3Direction * normalObstacleSpeed * deltaTime);
}
void renderbigObstacleHorizontalShape(sf::RenderWindow& window) {
	window.draw(bigObstacleHorizontalShape);
} // render the obstacle

void renderbigObstacleVerticalShape(sf::RenderWindow& window) {
	window.draw(bigObstacleVerticalShape);
}

void renderloseHealthObstacleShape(sf::RenderWindow& window) {
	window.draw(loseHealthObstacleShape);
}

// DECLARING VARIABLES
sf::Event userEvent;
sf::RenderWindow* snakeWindow;
sf::VideoMode videoMode;
sf::Clock worldClock;
sf::Time timeElabsed;
float deltaTime;

int GRID_HEIGHT, GRID_WIDTH, BLOCK_SIZE;
sf::Text healthText, scoreText;
sf::Font font;

float increaseScoreByHundredSpawnTimer, increaseScoreByHundredActiveDurationTimer;          // Counts up to 15 seconds
bool increaseScoreByHundredIsVisible, slowSpeedCollectableIsVisible;            // Tracks if the item is currently active

bool bigObstacleHorizontalIsVisible;

bool bigObstacleVerticalIsVisible;

bool hasCollidedWithObstacle;

void initVariables() {
	snakeWindow = nullptr;
	GRID_HEIGHT = 600;
	GRID_WIDTH = 800;
	BLOCK_SIZE = 16;
	videoMode.height = GRID_HEIGHT;
	videoMode.width = GRID_WIDTH;

	// Collectables
	extendPlayerCollectableColor = sf::Color::Green;

	slowSpeedCollectableColor = sf::Color::Cyan;
	slowSpeedCollectableIsVisible = false;

	increaseScoreCollectableColor = sf::Color::Magenta;
	increaseScoreByHundredSpawnTimer = 0.0f;          // Counts up to 15 seconds
	increaseScoreByHundredActiveDurationTimer = 0.0f; // Counts down from 5 seconds when spawned
	increaseScoreByHundredIsVisible = false;            // Tracks if the item is currently visible

	// Obstacles
	bigObstacleHorizontalIsVisible = false;
	bigObstacleVerticalIsVisible = false;

	hasCollidedWithObstacle = false;
};

void initWindow() {
	snakeWindow = new sf::RenderWindow(videoMode, "sssss-Snake", sf::Style::Titlebar | sf::Style::Close);
	snakeWindow->setFramerateLimit(60); // cap 60 FPS
};

void loseIfOutOfBoundries() {
	int grid_size_x = GRID_WIDTH / BLOCK_SIZE;
	int grid_size_y = GRID_HEIGHT / BLOCK_SIZE;

	// if player is out of bounderies make the player lose
	if (getPosition().x <= 0 || getPosition().y <= 0
		|| getPosition().x >= grid_size_x - 1
		|| getPosition().y >= grid_size_y - 1) {
		lose();
	}
}

void initUI() {
	if (!font.loadFromFile("resources/Fonts/Poppins-Bold.ttf")) {
		std::cerr << "Error loading font\n";
	}

	// Initialize the score text
	scoreText.setFont(font);
	scoreText.setCharacterSize(24); // Size of the text
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(10.f, 10.f); // Position at the top-left corner
	scoreText.setString("Score: " + std::to_string(getScore()));

	// Initialize the health text
	healthText.setString("Health: " + std::to_string(getLives()));
	healthText.setFont(font);
	healthText.setCharacterSize(24);
	healthText.setFillColor(sf::Color::White);
	healthText.setPosition(10.f, 40.f); // Positioned below the score
}

void beginGame() {
	rectBody.setSize(sf::Vector2f(BLOCK_SIZE - 1, BLOCK_SIZE - 1));
	resetPosition();
	initVariables();
	initializeObstacle();
	initWindow();
	initUI();
}

void endGame() {
	delete snakeWindow;
}

// Functions
void updateUI();
void pollEvent();
void updateWorld();
void restartGame();
void handleUserInput();


void checkCollision() {
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
};

Direction& getDirection() { return direction; }
SnakeContainer& getSnakeBody() { return snakeBody; }
void setDirection(Direction dir) { direction = dir; }
void increaseSpeed() { if (speed <= 25) speed += 0.5; }
float getSpeed() { return speed; }
int getLives() {
	const int health = lives;
	return health;
}
void increaseLives() { ++lives; }
int getScore() {
	const int playerScore = score;
	return playerScore;
}
sf::Vector2i getPosition() {
	return (snakeBody.empty() ? sf::Vector2i(1, 1) : snakeBody.front().position);
}
void updateUI() {
	scoreText.setString("Score: " + std::to_string(getScore()));

	healthText.setString("Health: " + std::to_string(getLives()));
}
void pollEvent() {
	while (snakeWindow->pollEvent(userEvent)) {
		switch (userEvent.type)
		{
		case sf::Event::Closed: {
			snakeWindow->close();
			break;
		}
		case sf::Event::KeyPressed: {
			if (userEvent.key.code == sf::Keyboard::Escape) {
				snakeWindow->close();
				break;
			}
		}
		default:
			break;
		}
	}
}
void updateWorld() {
	/*
		- Collectable to grow the player
		- Collectable to slow the speed of the player without making it grow
		- Collectable to increase the score by 100 instead of normally 10
	*/
	if (getPosition() == extendPlayerCollectableItem) {
		increaseScore();
		extendPlayer(getDirection());
		updateUI();
		respawnCollectable(extendPlayerCollectablePositionX, extendPlayerCollectablePositionY, extendPlayerCollectableItem, extendPlayerCollectableShape);
	};

	if (getScore() % 50 == 0 && getScore() != 0) {
		slowSpeedCollectableIsVisible = true;
	}
	else {
		slowSpeedCollectableIsVisible = false;
	}
	if (slowSpeedCollectableIsVisible) {
		if (getPosition() == slowSpeedCollectableItem) {
			increaseScore();
			slowPlayerSpeed();
			updateUI();
			respawnCollectable(slowSpeedCollectablePositionX, slowSpeedCollectablePositionY, slowSpeedCollectableItem, slowSpeedCollectableShape);
			slowSpeedCollectableIsVisible = false;
		};
	}


	if (increaseScoreByHundredIsVisible) {
		// counts down from 5 to despawn the collectable
		increaseScoreByHundredActiveDurationTimer -= deltaTime;

		// if the player touches the collectable make it disappear
		if (getPosition() == increaseScoreCollectableItem) {
			respawnCollectable(increaseScoreCollectablePositionX, increaseScoreCollectablePositionY, increaseScoreCollectableItem, increaseScoreCollectableShape);
			increaseScoreByHundred();
			extendPlayer(getDirection());
			updateUI();
			increaseScoreByHundredActiveDurationTimer = 0.0f;
			increaseScoreByHundredSpawnTimer = 0.0f;
			increaseScoreByHundredIsVisible = false;
		};

		if (increaseScoreByHundredActiveDurationTimer <= 0.0f) {
			increaseScoreByHundredIsVisible = false;
			increaseScoreByHundredSpawnTimer = 0.0f;
		}
	}
	else {
		// counts up to 15 seconds to spawn the collectable
		increaseScoreByHundredSpawnTimer += deltaTime;

		if (increaseScoreByHundredSpawnTimer >= 15.0f) {
			respawnCollectable(increaseScoreCollectablePositionX, increaseScoreCollectablePositionY, increaseScoreCollectableItem, increaseScoreCollectableShape);
			increaseScoreByHundredActiveDurationTimer = 5.0f;
			increaseScoreByHundredIsVisible = true;
		}
	}

	/*
		- Big obstacles that appears once the player gets different scores
		the purpose of it is just a distraction
	*/

	// Horizontal obstacle
	if (getScore() >= 300) {
		bigObstacleHorizontalIsVisible = true;
	}
	// Vertical obstacle
	if (getScore() >= 500) {
		bigObstacleVerticalIsVisible = true;
	}

	// Lose health obstacle
	if (checkCollision(getSnakeBody(), BLOCK_SIZE)) {
		if (!hasCollidedWithObstacle) {
			loseLives();
			updateUI();
			startCoolDown();
			hasCollidedWithObstacle = true;
		}
	}
	else {
		hasCollidedWithObstacle = false;
	}


	loseIfOutOfBoundries();
}
void restartGame() {
	resetPosition();
	resetScore();
	resetCoolDown();
	updateUI();

	respawnCollectable(extendPlayerCollectablePositionX, extendPlayerCollectablePositionY, extendPlayerCollectableItem, extendPlayerCollectableShape);
	slowSpeedCollectableIsVisible = false;

	increaseScoreByHundredIsVisible = false;
	increaseScoreByHundredSpawnTimer = 0.0f;
	increaseScoreByHundredActiveDurationTimer = 0.0f;

	bigObstacleHorizontalIsVisible = false;
	bigObstacleVerticalIsVisible = false;
	respawnObstacles();


	timeElabsed.Zero;
}

void handleUserInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		&& getDirection() != Direction::Down) {
		setDirection(Direction::Up);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		&& getDirection() != Direction::Up) {
		setDirection(Direction::Down);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		&& getDirection() != Direction::Left) {
		setDirection(Direction::Right);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		&& getDirection() != Direction::Right) {
		setDirection(Direction::Left);
	}
}
bool isLost() { return lost; }
void lose() { lost = true; }
void toggleLost() { lost = !lost; }
void resetScore() { score = 0; }
void resetCoolDown() { cooldownTimer = 0.0f; }
void startCoolDown() { cooldownTimer = cooldownDuration; }
void increaseScore() { score += 10; }
void increaseScoreByHundred() { score += 100; }
void loseLives() {
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
// reset to the original position
void resetPosition() {
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
void cutSnake(int segments) {
	for (int i = 0; i < segments; i++)
		snakeBody.pop_back();

	--lives;
	if (!lives) {
		lose();
		return;
	}
}

void moveSnake() {
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
};
void decreaseSpeedTemporary(float duration) {
	if (speedReductionTimer <= 0.0f) {
		originalSpeed = speed;
		speed /= 2;
		speedReductionTimer = duration;
	}
};

void restartClock() {
	timeElabsed += worldClock.restart();
};

const int getBlockSize() { return BLOCK_SIZE; }
bool isRunning() { return (*snakeWindow).isOpen(); }

void snakeUpdate(float deltaTime) {
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
};

void gameUpdate() {
	pollEvent();
	handleUserInput();

	float timestep = 1.0f / getSpeed();
	// Calculate delta time for smooth movement
	deltaTime = static_cast<float>(timeElabsed.asSeconds());

	if (timeElabsed.asSeconds() >= timestep) {
		snakeUpdate(deltaTime);
		updateUI();
		updateWorld();
		timeElabsed -= sf::seconds(timestep);
		if (isLost()) {
			restartGame();
		}
	};

	updatePosition(deltaTime);
}

void snakeRender(sf::RenderWindow& window) {
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
}; // render the snake



bool checkPlayerPos() {
	return false;
};

void initSnakeGame() {
	beginGame();
	initializeCollectable(extendPlayerCollectablePositionX, extendPlayerCollectablePositionY, extendPlayerCollectableItem, extendPlayerCollectableShape, extendPlayerCollectableColor);
	initializeCollectable(increaseScoreCollectablePositionX, increaseScoreCollectablePositionY, increaseScoreCollectableItem, increaseScoreCollectableShape, increaseScoreCollectableColor);
	initializeCollectable(slowSpeedCollectablePositionX, slowSpeedCollectablePositionY, slowSpeedCollectableItem, slowSpeedCollectableShape, slowSpeedCollectableColor);
}


void gameRender() {
	/*
		- Clear window contents
		- Render objects in window
		- Display the frame in window
	*/
	snakeWindow->clear(sf::Color(23, 23, 23, 255));

	snakeRender(*snakeWindow);

	renderCollectable(*snakeWindow, extendPlayerCollectableShape);
	if (slowSpeedCollectableIsVisible) {
		renderCollectable(*snakeWindow, slowSpeedCollectableShape);
	}
	if (increaseScoreByHundredIsVisible) {
		renderCollectable(*snakeWindow, increaseScoreCollectableShape);
	}

	if (bigObstacleHorizontalIsVisible) {
		renderbigObstacleHorizontalShape(*snakeWindow);
	}
	if (bigObstacleVerticalIsVisible) {
		renderbigObstacleVerticalShape(*snakeWindow);
	}
	renderloseHealthObstacleShape(*snakeWindow);
	snakeWindow->draw(scoreText);
	snakeWindow->draw(healthText);
	// Draw stuff here

	snakeWindow->display();
}

int main(int argc, char** argv[]) {
	srand(static_cast<unsigned int>(time(0)));
	initSnakeGame();
	rectBody.setSize(sf::Vector2f(size - 1, size - 1));
	videoMode.height = GRID_HEIGHT;
	videoMode.width = GRID_WIDTH;
	//initSnakeGame();

	while (isRunning()) {
		// update
		gameUpdate();

		// render
		gameRender();

		// restarting the clock each iteration
		restartClock();
	}
	endGame();
	return 0;
}