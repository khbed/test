#include "SFML/Graphics.hpp"
#include <iostream>
#include "Game.h"

sf::RectangleShape getBackground();

int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 10;

	sf::RenderWindow window(sf::VideoMode((unsigned int)WINDOW_X, (unsigned int)WINDOW_Y), "Plinko", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	sf::Event event;

	float deltaTime = 0.0f;
	sf::Clock clock;

	Game game;
	bool clicked = false;

	sf::RectangleShape background = getBackground();
	
	while (window.isOpen()) {
		deltaTime = clock.restart().asSeconds();

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			if (!clicked) {
				game.addBall();
			}
			clicked = true;
		}
		else {
			clicked = false;
		}
		game.update(deltaTime);
		
		window.clear();
		window.draw(background);
		window.draw(game);
		window.display();
	}
	return 0;
}

sf::RectangleShape getBackground() {
	sf::RectangleShape background(sf::Vector2f(WINDOW_X, WINDOW_Y));
	background.setPosition(sf::Vector2f(0.f, 0.f));
	background.setFillColor(BACKGROUND_COLOR);
	return background;
}