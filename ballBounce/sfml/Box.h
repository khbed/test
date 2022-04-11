#pragma once
#ifndef BOX
#define BOX

#include "SFML/Graphics.hpp"

class Box : public sf::Drawable
{
	const unsigned int CHAR_SIZE = 15;
public:
	Box() = default;
	virtual ~Box() = default;
	Box(sf::Vector2f pos, sf::Vector2f size, float value, const sf::Font& font, sf::Color color);
	sf::Vector2f getPos() {
		return this->pos;
	}
	sf::Vector2f getSize() {
		return this->size;
	}
	void bounce();
	void update();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setString();
	int frame = 0;
	int count_digit(int number);
	sf::RectangleShape rect;
	sf::Text text;
	sf::Vector2f pos, size;
	float value;
};

#endif // !BOX
