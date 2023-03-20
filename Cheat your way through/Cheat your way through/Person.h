#pragma once

#ifndef PERSON_HPP
#define PERSON_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

class Person
{
private:
	sf::Clock m_frametime;
	sf::Clock m_swapTime;
	float m_animationLenght = 2; //total time for the animation
public:

	Person() {};

	bool lookingAway{ false };
	const int spriteHeight = 128;
	const int spriteWidth = 96;
	int positionTime = 0;
	bool generateRandom = true; //we need to declare this variable here because it needs to be set as something outside the function teacherCycle();
	bool canAnimateIdle = true;
	
	sf::Sprite Sprite;
	sf::Texture Texture;



	void animateIdle(int t_firstFrame, int t_secondFrame);
	void teacherCycle();
	void teacherSwap();
	
};





#endif 