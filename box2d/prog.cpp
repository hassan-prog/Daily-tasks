#include <iostream>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Sun.h"
#include "Planet.h"
#include "Constants.h"

using namespace std;

int main() {
	sf::RenderWindow window(sf::VideoMode(SCREEN_WITDH, SCREEN_HEIGHT), "Solar System");
	window.setFramerateLimit(60);

	b2Vec2 gravity(0.0f, 0.0f);
	b2World world(gravity);

	Sun sun(&world);
	vector<Planet*> planets;
	vector<Planet*> destroyPlanets;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);

				b2Vec2 worldPos(mousePos.x / POS_SCALER, mousePos.y / POS_SCALER);

				Planet* newPlanet = new Planet(&world, worldPos, sun);
				planets.push_back(newPlanet);
			}
		}

		for (auto planet : planets) {
			b2Vec2 direction = sun.body->GetPosition() - planet->body->GetPosition();
			float distance = direction.Length();
			if (distance > 0.0f) {
				direction.Normalize();

				float forceMagnitude = G * sun.mass * planet->mass / (distance * distance);
				b2Vec2 force = forceMagnitude * direction;

				planet->body->ApplyForceToCenter(force, true);
				planet->Update();

				// Orbital decay
				b2Vec2 decay = -planet->body->GetLinearVelocity();
				decay = DECAY_MULTIPLIER * direction;
				planet->body->ApplyForceToCenter(decay, true);
			}
			if (distance * POS_SCALER <= sun.radius + planet->radius) {
				destroyPlanets.push_back(planet);
				planet->trail.clear();
				world.DestroyBody(planet->body);
			}
			destroyPlanets.clear();
		}

		world.Step(1.0f / 50.0f, 6, 2);

		window.clear();
		window.draw(sun.getSunShape());
		
		for (auto planet : planets) {
			window.draw(planet->trail);
			planet->trail.clear();
		}

		for (auto planet : planets) {
			window.draw(planet->planetShape);
		}
		window.display();
	}

	for (auto planet : planets) {
		delete planet;
	}

	return 0;
}
