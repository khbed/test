#include "Ball.h"

Ball::Ball(sf::Vector2f pos, float radius) {
	this->shape = sf::CircleShape(radius);
	this->shape.setOrigin(sf::Vector2f(radius, radius));
	this->shape.setPosition(pos);
	this->shape.setFillColor(BALL_COLOR);
	this->speed = sf::Vector2f(0.f, 0.f);
}
void Ball::update(float deltaTime){
	this->speed += deltaTime * gravity;
	this->shape.move(deltaTime * this->speed);
}
void Ball::setSpeed(sf::Vector2f speed){
	if (speed.x == 0) {
		speed += rand() % 2 == 0 ? sf::Vector2f(0.1f, 0.f) : sf::Vector2f(-0.1f, 0.f);
	}
	this->speed = speed;
}
sf::Vector2f Ball::getPosition(){
	return this->shape.getPosition();
}
void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(this->shape, states);
}
