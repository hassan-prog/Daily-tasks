#include <iostream>

#include <SFML/Graphics.hpp>
#include "../Game.h"

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

Game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);

int main()
{
    sf::ContextSettings context;
    context.depthBits = 24;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Brick Breaker", sf::Style::Close, context);


    sf::Clock clock;

    Breakout.Init();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
            {
                window.close();
                break;
            }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        Breakout.ProcessInput(window, deltaTime);
        Breakout.Update(deltaTime);
        Breakout.Render(deltaTime);
        window.display();
    }

    return 0;
}