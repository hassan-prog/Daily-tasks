#include <iostream>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Sun.h"
#include "Planet.h"
#include "Constants.h"

using namespace std;


int main() {
	// SFML Setup
	sf::RenderWindow window(sf::VideoMode(SCREEN_WITDH, SCREEN_HEIGHT), "Solar System");
	window.setFramerateLimit(60);

	// Box2D World Setup
	b2Vec2 gravity(0.0f, 0.0f);
	b2World world(gravity);

	Sun sun(&world);
	vector<Planet*> planets;

	// Main Loop
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
			direction.Normalize();

			float forceMagnitude = G * sun.mass * planet->mass / (distance * distance);
			b2Vec2 force = forceMagnitude * direction;

			planet->body->ApplyForceToCenter(force, true);
			planet->Update();
			/*std::cout << "Planet velocity: " << planet->body->GetLinearVelocity().x << ", "
				<< planet->body->GetLinearVelocity().y << std::endl;*/
			std::cout << "Planet POS: " << planet->body->GetPosition().x << ", "
				<< planet->body->GetPosition().y << std::endl;
			std::cout << "Shape POS: " << planet->getPlanetShape().getPosition().x << ", "
				<< planet->getPlanetShape().getPosition().y << std::endl;

		}

		world.Step(1.0f / 60.0f, 6, 2);

		// Rendering
		window.clear();
		window.draw(sun.getSunShape());
		for (auto planet : planets) {
			window.draw(planet->getPlanetShape());
		}
		//window.draw(boxRect);
		window.display();
	}

	for (auto planet : planets) {
		delete planet;
	}

	return 0;
}
