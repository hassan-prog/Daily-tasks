#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Constants.h"

class Sun {
    b2CircleShape circleShape;
    sf::CircleShape shape;
    

public:
    b2Body* body;
    b2Vec2 position; 

    float radius;
    float mass;

    Sun(b2World* world);
    sf::CircleShape getSunShape();
    void Update();
};

