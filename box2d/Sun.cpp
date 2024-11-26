#include "Sun.h"

Sun::Sun(b2World* world) {
	position = b2Vec2(10.f, 7.5f);
	mass = 1000.f;
	radius = 30.f;

	b2BodyDef bodyDef;

	bodyDef.position.Set(position.x, position.y);
	bodyDef.type = b2_staticBody;

	body = world->CreateBody(&bodyDef);

	circleShape.m_radius = radius / POS_SCALER;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 0.0f;

	body->CreateFixture(&fixtureDef);

	shape.setPosition(position.x * POS_SCALER, position.y * POS_SCALER);
	shape.setRadius(radius);
	shape.setOrigin(radius, radius);
	shape.setFillColor(sf::Color::Yellow);
}

sf::CircleShape Sun::getSunShape() {
	return shape;
}
