#include <iostream>
#include "Game.h"


// private functions
void Game::initVariables() {
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

	// when i move these vars into the constructor it doesn't render the colors nor the player
	player = new Snake(BLOCK_SIZE);
	// Collectables
	extendPlayerCollectable = new Collectable(extendPlayerCollectableColor, 16);
	slowSpeedCollectable = new Collectable(slowSpeedCollectableColor, 16);
	increaseScoreCollectable = new Collectable(increaseScoreCollectableColor, 16);

	// Obstacles
	bigObstacleHorizontal = new Obstacle(sf::Vector2f(360.0f, 0.0f), sf::Vector2f(360.0f, 520.0f),
		sf::Color::Red, sf::Vector2f(80.0f, 80.0f), 20.0f);

	bigObstacleVertical = new Obstacle(sf::Vector2f(720.0f, 260.0f), sf::Vector2f(0.0f, 260.0f),
		sf::Color(190, 59, 62), sf::Vector2f(80.0f, 80.0f), 20.0f);

	loseHealthObstacle = new Obstacle(sf::Vector2f(750.0f, 575.0f), sf::Vector2f(50.0f, 50.0f),
		sf::Color::Yellow, sf::Vector2f(40.0f, 40.0f), 30.0f);
}

void Game::initWindow() {
	snakeWindow = new sf::RenderWindow(videoMode, "sssss-Snake", sf::Style::Titlebar | sf::Style::Close);
	snakeWindow->setFramerateLimit(60); // cap 60 FPS
}

void Game::initUI(const Snake& player) {
	if (!font.loadFromFile("resources/Fonts/Poppins-Bold.ttf")) {
		std::cerr << "Error loading font\n";
	}

	// Initialize the score text
	scoreText.setFont(font);
	scoreText.setCharacterSize(24); // Size of the text
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(10.f, 10.f); // Position at the top-left corner
	scoreText.setString("Score: " + std::to_string(player.getScore()));

	// Initialize the health text
	healthText.setString("Health: " + std::to_string(player.getLives()));
	healthText.setFont(font);
	healthText.setCharacterSize(24);
	healthText.setFillColor(sf::Color::White);
	healthText.setPosition(10.f, 40.f); // Positioned below the score
}

void Game::loseIfOutOfBoundries() {
	int grid_size_x = GRID_WIDTH / BLOCK_SIZE;
	int grid_size_y = GRID_HEIGHT / BLOCK_SIZE;

	// if player is out of bounderies make the player lose
	if ((*player).getPosition().x <= 0 || (*player).getPosition().y <= 0
		|| (*player).getPosition().x >= grid_size_x - 1
		|| (*player).getPosition().y >= grid_size_y - 1) {
		(*player).lose();
	}
}

// Constructors & Destructors
Game::Game() {
	this->initVariables();
	this->initWindow();
	this->initUI(*player);
}

Game::~Game() {
	delete snakeWindow;
	delete extendPlayerCollectable;
	delete slowSpeedCollectable;
	delete increaseScoreCollectable;
	delete bigObstacleHorizontal;
	delete bigObstacleVertical;
	delete loseHealthObstacle;
	delete player;
}


//public functions
void Game::restartClock() {
	timeElabsed += clock.restart();
}

void Game::handleUserInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		&& player->getDirection() != Direction::Down) {
		player->setDirection(Direction::Up);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		&& player->getDirection() != Direction::Up) {
		player->setDirection(Direction::Down);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		&& player->getDirection() != Direction::Left) {
		player->setDirection(Direction::Right);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		&& player->getDirection() != Direction::Right) {
		player->setDirection(Direction::Left);
	}
}

void Game::restartGame() {
	player->resetPosition();
	player->resetScore();
	player->resetCoolDown();
	updateUI(*player);

	extendPlayerCollectable->respawn();
	slowSpeedCollectableIsVisible = false;

	increaseScoreByHundredIsVisible = false;
	increaseScoreByHundredSpawnTimer = 0.0f;
	increaseScoreByHundredActiveDurationTimer = 0.0f;

	bigObstacleHorizontalIsVisible = false;
	bigObstacleHorizontal->respawn();

	bigObstacleVerticalIsVisible = false;
	bigObstacleVertical->respawn();

	loseHealthObstacle->respawn();

	timeElabsed.Zero;
}

// Accessors
const bool Game::isRunning() const {
	return snakeWindow->isOpen();
}

const int Game::getBlockSize() const {
	return BLOCK_SIZE;
}

const sf::Time Game::getElabsed() const {
	return timeElabsed;
}

void Game::updateUI(const Snake& player) {
	scoreText.setString("Score: " + std::to_string(player.getScore()));

	healthText.setString("Health: " + std::to_string(player.getLives()));
}

void Game::pollEvent() {
	while (snakeWindow->pollEvent(userEvent)) {
		switch (userEvent.type)
		{
		case sf::Event::Closed: {
			snakeWindow->close();
			break;
		}
		case sf::Event::KeyPressed: {
			if (Game::userEvent.key.code == sf::Keyboard::Escape) {
				snakeWindow->close();
				break;
			}
		}
		default:
			break;
		}
	}
}

void Game::updateWorld() {
	/*
		- Collectable to grow the player
		- Collectable to slow the speed of the player without making it grow
		- Collectable to increase the score by 100 instead of normally 10
	*/
	if ((*player).getPosition() == (*extendPlayerCollectable).item) {
		player->increaseScore();
		extendPlayerCollectable->extendPlayer(*player, player->getDirection());
		updateUI(*player);
		extendPlayerCollectable->respawn();
	};

	if (player->getScore() % 50 == 0 && player->getScore() != 0) {
		slowSpeedCollectableIsVisible = true;
	}
	else {
		slowSpeedCollectableIsVisible = false;
	}
	if (slowSpeedCollectableIsVisible) {
		if ((*player).getPosition() == (*slowSpeedCollectable).item) {
			player->increaseScore();
			slowSpeedCollectable->slowPlayerSpeed(*player);
			updateUI(*player);
			slowSpeedCollectable->respawn();
			slowSpeedCollectableIsVisible = false;
		};
	}


	if (increaseScoreByHundredIsVisible) {
		// counts down from 5 to despawn the collectable
		increaseScoreByHundredActiveDurationTimer -= deltaTime;

		// if the player touches the collectable make it disappear
		if ((*player).getPosition() == (*increaseScoreCollectable).item) {
			increaseScoreCollectable->respawn();
			player->increaseScoreByHundred();
			increaseScoreCollectable->extendPlayer(*player, player->getDirection());
			updateUI(*player);
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
			increaseScoreCollectable->respawn();
			increaseScoreByHundredActiveDurationTimer = 5.0f;
			increaseScoreByHundredIsVisible = true;
		}
	}

	/*
		- Big obstacles that appears once the player gets different scores
		the purpose of it is just a distraction
	*/

	// Horizontal obstacle
	if (player->getScore() >= 300) {
		bigObstacleHorizontalIsVisible = true;
	}
	// Vertical obstacle
	if (player->getScore() >= 500) {
		bigObstacleVerticalIsVisible = true;
	}

	// Lose health obstacle
	if (loseHealthObstacle->checkCollision(player->getSnakeBody(), BLOCK_SIZE)) {
		if (!hasCollidedWithObstacle) {
			player->loseLives();
			updateUI(*player);
			player->startCoolDown();
			hasCollidedWithObstacle = true;
		}
	} else {
		hasCollidedWithObstacle = false;
	}

	this->loseIfOutOfBoundries();
}

void Game::update() {
	pollEvent();
	handleUserInput();

	float timestep = 1.0f / player->getSpeed();
	// Calculate delta time for smooth movement
	deltaTime = static_cast<float>(timeElabsed.asSeconds());

	if (timeElabsed.asSeconds() >= timestep) {
		player->update(deltaTime);
		updateUI(*player);
		updateWorld();
		timeElabsed -= sf::seconds(timestep);
		if (player->isLost()) {
			restartGame();
		}
	};

	this->bigObstacleHorizontal->updatePosition(deltaTime);
	this->bigObstacleVertical->updatePosition(deltaTime);
	this->loseHealthObstacle->updatePosition(deltaTime);
}

void Game::render() {
	/*
		- Clear window contents
		- Render objects in window
		- Display the frame in window
	*/
	this->snakeWindow->clear(sf::Color(23, 23, 23, 255));


	player->render(*snakeWindow);
	extendPlayerCollectable->render(*snakeWindow);
	if (slowSpeedCollectableIsVisible) {
		slowSpeedCollectable->render(*snakeWindow);
	}
	if (increaseScoreByHundredIsVisible) {
		increaseScoreCollectable->render(*snakeWindow);
	}

	if (bigObstacleHorizontalIsVisible) {
		bigObstacleHorizontal->render(*snakeWindow);
	}
	if (bigObstacleVerticalIsVisible) {
		bigObstacleVertical->render(*snakeWindow);
	}
	loseHealthObstacle->render(*snakeWindow);
	snakeWindow->draw(scoreText);
	snakeWindow->draw(healthText);
	// Draw stuff here

	this->snakeWindow->display();
}