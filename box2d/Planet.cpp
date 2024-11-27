#include "Planet.h"

Planet::Planet(b2World* world, b2Vec2 mousePos, Sun sun) {
	mass = 20.f;
	radius = 8.f;

	float distance = b2Vec2(mousePos.x - sun.position.x, mousePos.y - sun.position.y).Length();

	float velocityMagnitude = sqrt(G * sun.mass / distance) * 25;

	b2Vec2 direction = b2Vec2(-(mousePos.y - sun.position.y), mousePos.x - sun.position.x);
	direction.Normalize();

	b2Vec2 initialVelocity(direction.x * velocityMagnitude, direction.y * velocityMagnitude);

	b2BodyDef bodyDef;
	bodyDef.position.Set(mousePos.x, mousePos.y);
	bodyDef.type = b2_dynamicBody;

	body = world->CreateBody(&bodyDef);

	circlePlanetShape.m_radius = radius / POS_SCALER;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circlePlanetShape;
	fixtureDef.density = mass / (3.14 * radius * radius);
	fixtureDef.friction = 0.0f;
	fixtureDef.restitution = 0.f;
	body->CreateFixture(&fixtureDef);

	body->SetLinearVelocity(initialVelocity);
	sf::Vertex v;
	v.position = sf::Vector2f(mousePos.x * POS_SCALER, mousePos.y * POS_SCALER);

	trailPos.push_back(sf::Vector2f(mousePos.x * POS_SCALER, mousePos.y * POS_SCALER));

	trail.append(v);
	trail.setPrimitiveType(sf::LinesStrip);

	planetShape.setPosition(mousePos.x * POS_SCALER, mousePos.y * POS_SCALER);
	planetShape.setRadius(radius);
	planetShape.setOrigin(radius, radius);
	planetShape.setFillColor(sf::Color::Green);
}

void Planet::Update() {
	b2Vec2 pos = body->GetPosition();
	planetShape.setPosition(pos.x * POS_SCALER, pos.y * POS_SCALER);
	trailPos.push_back(sf::Vector2f(pos.x * POS_SCALER, pos.y * POS_SCALER));

	for (auto trailPoint : trailPos) {
		sf::Vertex v;
		v.position = trailPoint;

		trail.append(v);
	}

	if (trailPos.size() >= 100) {
		trailPos.erase(trailPos.begin());
	};
}
