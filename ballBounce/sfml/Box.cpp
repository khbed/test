#include "Box.h"

Box::Box(sf::Vector2f pos, sf::Vector2f size, float value, const sf::Font& font, sf::Color color) {
	this->pos = pos;
	this->size = size;
	this->value = value;
	this->rect.setPosition(this->pos);
	this->rect.setSize(this->size);
	this->rect.setFillColor(color);
	
	this->text.setFont(font);
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(CHAR_SIZE);
	this->setString();
}

void Box::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(this->rect);
	target.draw(this->text);
}

int Box::count_digit(int number) {
	return int(log10(number) + 1);
}

void Box::setString() {
	std::string strValue = std::to_string(value);
	int numChars = this->count_digit(int(floorf(this->value)));
	if (int(floorf(this->value)) == 0) numChars = this->count_digit(int(ceilf(this->value)));
	if (this->value != floorf(value)) numChars += 2;
	strValue = strValue.substr(0, numChars);
	this->text.setString(strValue);

	sf::FloatRect textRect = this->text.getLocalBounds();
	this->text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	this->text.setPosition(this->pos + this->size/2.f);
}

void Box::bounce() {
	if (this->frame == 0) {
		this->frame = 20;
	}
}
void Box::update() {
	if (this->frame > 10) {
		this->rect.move(sf::Vector2f(0.f, 1.f));
		this->text.move(sf::Vector2f(0.f, 1.f));
		this->frame--;
	}
	else if (this->frame > 0) {
		this->rect.move(sf::Vector2f(0.f, -1.f));
		this->text.move(sf::Vector2f(0.f, -1.f));
		this->frame--;
	}
}