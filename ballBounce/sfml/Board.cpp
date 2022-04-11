#include "Board.h"

Board::Board(int nLayers, sf::Vector2f pos, sf::Vector2f size, float pointRadius) {
	int nPointsLastLayer = N_FIRS_LAYER_POINTS + nLayers - 1;
	this->xShift = (size.x - 2 * pointRadius) / float(nPointsLastLayer - 1);
	this->yShift = (size.y - 2 * pointRadius) / float(nLayers - 1);
	this->pointRadius = pointRadius;
	this->nLayers = nLayers;
	this->pos = pos;
	this->size = size;
	this->initializePoints();
}
std::vector<sf::Vector2f> Board::getPositions() {
	std::vector<sf::Vector2f> positions;
	for (unsigned int i = 0; i < points.size(); i++) {
		positions.push_back(points[i].getPosition());
	}
	return positions;
}

void Board::updateLights() {
	this->lights.clear();
	for (unsigned int i = 0; i < this->lighting.size(); i++) {
		if (this->lighting[i] > 0) {
			float factor = ((float)this->lighting[i] / (float)NUM_FRAME);
			sf::CircleShape light(this->pointRadius + factor * 2.f * this->pointRadius);
			light.setOrigin(sf::Vector2f(light.getRadius(), light.getRadius()));
			light.setPosition(this->points[i].getPosition());
			light.setFillColor(sf::Color(255, 255, 255, 127 * factor));
			this->lights.push_back(light);
			this->lighting[i] = this->lighting[i] - 1;
		}
	}
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (unsigned int i = 0; i < this->lights.size(); i++) {
		target.draw(this->lights[i], states);
	}
	for (unsigned int i = 0; i < this->points.size(); i++) {
		target.draw(this->points[i], states);
	}
}
void Board::initializePoints(){
	this->points.clear();
	this->lighting.clear();
	int numPoints = N_FIRS_LAYER_POINTS + nLayers - 1;
	sf::Vector2f initPos = this->pos + this->size - sf::Vector2f(pointRadius, pointRadius);
	for (int i = 0; i < this->nLayers; i++) {
		for (int j = 0; j < numPoints; j++) {
			sf::CircleShape point(this->pointRadius);
			point.setOrigin(sf::Vector2f(this->pointRadius, this->pointRadius));
			point.setPosition(initPos - sf::Vector2f((float)j * this->xShift + (float)i * this->xShift/2.f, (float)i * this->yShift));
			points.push_back(point);
			lighting.push_back(0);
		}
		numPoints--;
	}
}
void Board::lightUpPoint(sf::Vector2f pointPos) {
	for (unsigned int i = 0; i < this->points.size(); i++) {
		if (this->points[i].getPosition() == pointPos) {
			lighting[i] = NUM_FRAME;
			break;
		}
	}
}