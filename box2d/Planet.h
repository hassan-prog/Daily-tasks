#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Sun.h"
#include "Orbit.h"
#include "Constants.h"

class Planet {
    b2CircleShape circlePlanetShape;
    b2Vec2 initialVelocity;


public:
    b2Body* body;
    b2Vec2 position;
	Orbit orbit;
    sf::VertexArray trail;
    std::vector<sf::Vector2f> trailPos;
    sf::CircleShape planetShape;

    float radius;
    float mass;

    Planet(b2World* world, b2Vec2 mousePos, Sun sun);
    void Update();
};

