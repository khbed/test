#pragma once
#ifndef BOARD
#define BOARD

#include "SFML/Graphics.hpp"

class Board : public sf::Drawable
{
	const int N_FIRS_LAYER_POINTS = 3, NUM_FRAME = 30;
public:
	Board() = default;
	Board(int nLayers, sf::Vector2f pos, sf::Vector2f size, float pointRadius);
	std::vector<sf::Vector2f> getPositions();
	sf::Vector2f getShift() {
		return sf::Vector2f(this->xShift, this->yShift);
	}
	void lightUpPoint(sf::Vector2f pointPos);
	void updateLights();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void initializePoints();
	float xShift, yShift, pointRadius;
	int nLayers;
	sf::Vector2f pos, size;
	std::vector<sf::CircleShape> points;
	std::vector<int> lighting;
	std::vector<sf::CircleShape> lights;
};

#endif // !BALL