
#ifndef BAR_HPP
#define BAR_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

class Bar
{
private:

public:
	



	const int X_COORDINATE = 100;
	const int Y_COORDINATE = 155;
	float height = 20;
	float lenght = 10;
	int maximum = 11;
	bool isRestricted = false;

	sf::Color Colour;
	sf::CircleShape barEnd;
	sf::RectangleShape barBody;
	
	void increase(bool isRestricted);
	void setupBars(bool blueColor);
};
Bar  static copyBar;
Bar static writeBar;






#endif 