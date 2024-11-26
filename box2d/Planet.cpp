#include "Planet.h"

Planet::Planet(b2World* world, b2Vec2 mousePos, Sun sun) {
	mass = 1.f;  // Earth-like mass
	radius = 8.f;  // Earth-like radius in meters

	// Calculate distance from the sun in world coordinates
	float distance = b2Vec2(mousePos.x - sun.position.x, mousePos.y - sun.position.y).Length();

	// Correct orbital velocity calculation
	float velocityMagnitude = sqrt(G * sun.mass / distance);

	// Perpendicular direction for tangential velocity
	b2Vec2 direction = b2Vec2(-(mousePos.y - sun.position.y), mousePos.x - sun.position.x);
	direction.Normalize();
	b2Vec2 initialVelocity(0.f, 0.f);

	// Define the Box2D body
	b2BodyDef bodyDef;
	bodyDef.position.Set(mousePos.x, mousePos.y);
	bodyDef.type = b2_dynamicBody;

	body = world->CreateBody(&bodyDef);

	circlePlanetShape.m_radius = radius;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circlePlanetShape;
	fixtureDef.density = mass / (3.14 * radius * radius);  // Set density for physical simulation
	fixtureDef.friction = 0.0f;  // No friction in space
	body->CreateFixture(&fixtureDef);

	// Set the initial velocity
	body->SetLinearVelocity(initialVelocity);

	// Set the SFML shape
	planetShape.setPosition(mousePos.x * POS_SCALER, mousePos.y * POS_SCALER);
	planetShape.setRadius(radius);
	planetShape.setOrigin(radius, radius);
	planetShape.setFillColor(sf::Color::Green);
}


sf::CircleShape Planet::getPlanetShape() {
	return planetShape;
}

void Planet::Update() {
	b2Vec2 pos = body->GetPosition();
	planetShape.setPosition(pos.x * POS_SCALER, pos.y * POS_SCALER);
}
