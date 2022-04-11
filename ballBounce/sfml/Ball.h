#pragma once
#ifndef BALL
#define BALL

#include "SFML/Graphics.hpp"
#include <iostream>
#include "constants.h"

class Ball : public sf::Drawable
{
	const sf::Vector2f gravity = sf::Vector2f(0.f, 400.f);

public:
	Ball() = default;
	Ball(sf::Vector2f pos, float radius);
	virtual ~Ball() = default;
	void update(float deltaTime);
	void setSpeed(sf::Vector2f speed);
	sf::Vector2f getPosition();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2f speed;
	sf::CircleShape shape;
};

#endif // !BALL
