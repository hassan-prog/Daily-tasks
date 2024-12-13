#ifndef GAME_H
#define GAME_H

#include "GameLevel.h"

#include <SFML/Graphics.hpp>
#include "Brick-Breaker/PowerUp.h"

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

typedef std::tuple<bool, Direction, glm::vec2> Collision; // <collision?, what direction?, difference vector center - closest point>

const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
const float PLAYER_VELOCITY(500.0f);
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
const float BALL_RADIUS = 12.5f;

class Game
{
public:
    GameState               State;
    bool                    Keys[1024];
    unsigned int            Width, Height;
    std::vector<GameLevel>  Levels;
    std::vector<PowerUp>  PowerUps;
    unsigned int            Level;

    Game(unsigned int width, unsigned int height);
    ~Game();

    void Init();

    void ProcessInput(sf::RenderWindow& window, float dt);
    void Update(float dt);
    void Render(float dt);
    void DoCollisions();
    
    void SpawnPowerUps(GameObject& block);
    void UpdatePowerUps(float dt);
    
    void ResetLevel();
    void ResetPlayer();
};

#endif