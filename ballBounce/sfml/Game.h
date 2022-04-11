#pragma once
#ifndef GAME
#define GAME

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Board.h"
#include "Ball.h"
#include "Box.h"
#include "constants.h"

class Game : public sf::Drawable
{
	const int DEFAULT_N_LAYERS = 10;
	const float POINT_RADIUS = 5.f, BALL_RADIUS = 10.f;
	const float SPEED_FACT_X = 80.f, SPEED_FACT_Y = 100.f;
	const sf::Vector2f BOARD_POS = sf::Vector2f(300.f, 100.f), BOARD_SIZE = sf::Vector2f(600.f, 500.f);

public:
	Game();
	virtual ~Game();
	void update(float deltaTime);
	void addBall();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void initializeBoxes();
	Board* board;
	sf::Font font;
	int nLayers = DEFAULT_N_LAYERS;
	std::vector<Ball*> balls;
	std::vector<Box*> boxes;
};
#endif // !GAME

