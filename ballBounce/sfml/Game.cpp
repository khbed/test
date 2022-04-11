#include "Game.h"

Game::Game() {
	this->board = new Board(DEFAULT_N_LAYERS, BOARD_POS, BOARD_SIZE, POINT_RADIUS);
	srand(time(NULL));
	this->font.loadFromFile("assets/Roboto/Roboto-Bold.ttf");
	this->initializeBoxes();
}
Game::~Game() {
	delete this->board;
	for (auto ball : this->balls) {
		delete ball;
	}
	balls.clear();
}
void Game::update(float deltaTime) {
	for (unsigned int i = 0; i < this->balls.size(); i++) {
		this->balls[i]->update(deltaTime);
	}
	for (unsigned int i = 0; i < this->balls.size(); i++) {
		for (auto pos : this->board->getPositions()) {
			float xDist = balls[i]->getPosition().x - pos.x;
			float yDist = balls[i]->getPosition().y - pos.y;
			float distance = (float)sqrt(pow(xDist, 2) + pow(yDist, 2));
			if (distance < BALL_RADIUS + POINT_RADIUS) {
				this->balls[i]->setSpeed(sf::Vector2f(SPEED_FACT_X * xDist / distance, SPEED_FACT_Y * yDist / distance));
				this->board->lightUpPoint(pos);
			}
		}
	}

	for (unsigned int i = 0; i < this->balls.size(); i++) {
		for (unsigned int j = 0; j < this->boxes.size(); j++) {
			sf::Vector2f coord = balls[i]->getPosition() + sf::Vector2f(0, BALL_RADIUS);
			if (coord.x > this->boxes[j]->getPos().x && coord.x < this->boxes[j]->getPos().x + this->boxes[j]->getSize().x) {
				if (coord.y > this->boxes[j]->getPos().y) {
					this->balls.erase(this->balls.begin() + i);
					this->boxes[j]->bounce();
					break;
				}
			}
		}
	}
	for (unsigned int i = 0; i < this->boxes.size(); i++) {
		boxes[i]->update();
	}

	this->board->updateLights();                                      

	for (unsigned int i = 0; i < this->balls.size(); i++) {
		if (this->balls[i]->getPosition().y > WINDOW_Y) {
			this->balls.erase(this->balls.begin() + i);
			break;
		}
	}
}
void Game::addBall() {
	float shift = 0;
	do {
		shift = float(rand() % int(this->board->getShift().x) * 100) / 100.f;
	} while (shift == 0);
	if (rand() % 2 == 0) shift = -shift;
	sf::Vector2f pos(BOARD_POS.x + BOARD_SIZE.x / 2.f + shift, 2.f * BALL_RADIUS);
	this->balls.push_back(new Ball(pos, BALL_RADIUS));
}
void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(*this->board, states);
	for (unsigned int i = 0; i < this->balls.size(); i++) {
		target.draw(*this->balls[i], states);
	}
	for (unsigned int i = 0; i < this->boxes.size(); i++) {
		target.draw(*this->boxes[i], states);
	}
}
void Game::initializeBoxes() {
	int nBoxes = this->nLayers + 1;
	const sf::Vector2f initialPos = BOARD_POS + sf::Vector2f(POINT_RADIUS * 2, BOARD_SIZE.y + this->board->getShift().x / 2.f);
	const sf::Vector2f size = sf::Vector2f(this->board->getShift().x - 2 * POINT_RADIUS, this->board->getShift().x / 2.f);
	for (int i = 0; i < nBoxes; i++) {
		float val = LOW_ODDS.at(this->nLayers)[i];
		float shift = this->board->getShift().x;

		sf::Vector2f pos = initialPos + sf::Vector2f(i * this->board->getShift().x, 0);

		sf::Color color;
		if (nBoxes % 2 == 0) {
			if (i <= nBoxes / 2 - 1) color = BOX_COLORS[(nBoxes / 2 - 1) - i];
			else color = BOX_COLORS[i - nBoxes / 2];
		}
		else {
			color = BOX_COLORS[abs(nBoxes / 2 - i)];
		}
		this->boxes.push_back(new Box(pos, size, val, this->font, color));
	}
}