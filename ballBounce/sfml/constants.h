#pragma once
#ifndef CONSTANTS
#define CONSTANTS
#include <map>
#include <vector>
#include "SFML/Graphics.hpp"

const float WINDOW_X = 1200.f, WINDOW_Y = 800.f;

const std::map<int, std::vector<float>> LOW_ODDS{
	{8, {5.6f, 2.1f, 1.1f, 1.f, 0.5f, 1.f, 1.1f, 2.1f, 5.6f}},
	{9, {5.6f, 2.f, 1.6f, 1.f, 0.7f, 0.7f, 1.f, 1.6f, 2.f, 5.6f}},
	{10, {8.9f, 3.f, 1.4f, 1.1f, 1.f, 0.5f, 1.f, 1.1f, 1.4f, 3.f, 8.9f}},
	{11, {8.4f, 3.f, 1.9f, 1.3f, 1.f, 0.7f, 0.7f, 1.f, 1.3f, 1.9f, 3.f, 8.4f}},
	{12, {10.f, 3.f, 1.6f, 1.4f, 1.1f, 1.f, 0.5f, 1.f, 1.1f, 1.4f, 1.6f, 3.f, 10.f}},
	{13, {8.1f, 4.f, 3.f, 1.9f, 1.2f, 0.9f, 0.7f, 0.7f, 0.9f, 1.2f, 1.9f, 3.f, 4.f, 8.1f}},
	{14, {7.1f, 4.f, 1.9f, 1.4f, 1.3f, 1.1f, 1.f, 0.5f, 1.f, 1.1f, 1.3f, 1.4f, 1.9f, 4.f, 7.1f}},
	{15, {15.f, 8.f, 3.f, 2.f, 1.5f, 1.1f, 1.f, 0.7f, 0.7f, 1.f, 1.1f, 1.5f, 2.f, 3.f, 8.f, 15.f}},
	{16, {16.f, 9.f, 2.f, 1.4f, 1.4f, 1.2f, 1.1f, 1.f, 0.5f, 1.f, 1.1f, 1.2f, 1.4f, 1.4f, 2.f, 9.f, 16.f}},
};

const std::vector<sf::Color> BOX_COLORS = {
	sf::Color(240, 224, 45),
	sf::Color(244, 205, 17),
	sf::Color(247, 185, 0),
	sf::Color(248, 165, 0),
	sf::Color(249, 144, 0),
	sf::Color(247, 123, 0),
	sf::Color(245, 99, 0),
	sf::Color(241, 74, 18),
	sf::Color(235, 40, 30)
};

const sf::Color BACKGROUND_COLOR = sf::Color(15, 33, 47);
const sf::Color BALL_COLOR = sf::Color(254, 112, 1);
#endif // !CONSTANTS
