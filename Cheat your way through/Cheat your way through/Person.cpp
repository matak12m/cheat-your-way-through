#include "Person.h"
#include "Game.h"
#include <iostream>

void Person::animateIdle(int t_firstFrame, int t_secondFrame) // animates the sprites when they aren't doing anything
{
	
	float frameTime = m_frametime.getElapsedTime().asSeconds();  //counts up, then restarts once progress is above 2
	
	if (frameTime >= m_animationLenght)
	{
		m_frametime.restart();
	}
	else
	{
		int index = frameTime; //truncates into integer
		if (index == 0) {
			Sprite.setTextureRect(sf::IntRect{ t_firstFrame * spriteWidth, 0, spriteWidth, spriteHeight });
		}
		else {
			Sprite.setTextureRect(sf::IntRect{ spriteWidth * t_secondFrame, 0, spriteWidth, spriteHeight });
		}
	}
}


void Person::teacherCycle() //handles the behavious of the teacher, ready to be plugged into the main logic of the game.
{
	
	if (generateRandom) {
		srand(time(0));
		generateRandom = false;

		positionTime = rand() % 5 + 5;  //get a random number between 5 and 15
	}
	float tempClock = m_swapTime.getElapsedTime().asSeconds();    
	int positionClock = tempClock;
	std::cout << std::to_string(positionTime) + "  " + std::to_string(positionClock);
	std::cout << std::endl;
	
		  //todo: change positions of the teacher after random intervals, between looking away or not. play animation between these states.
	if (positionClock == positionTime) {

		canAnimateIdle = false;
		m_swapTime.restart();
		generateRandom = true;

	}
	else if (canAnimateIdle) {
		if (!lookingAway) {
			animateIdle(0, 1);
		}
		else {
			animateIdle(3, 4);
		}
	}
}

void Person::teacherSwap()  //handles the teacher's animation and logic of changing his positions between looing away and not
							//DOESNT WORK, need to fix. Is only being called once even though it should be called continuously while animation plays
{

	float frameTime = m_swapTime.getElapsedTime().asSeconds();
	std::cout << frameTime;
	std::cout << std::endl;
	if (lookingAway) {
		if (frameTime < 1) {
			Sprite.setTextureRect(sf::IntRect{ spriteWidth * 5, 0, spriteWidth, spriteHeight });
		}
		else if (frameTime < 1.5) {
			Sprite.setTextureRect(sf::IntRect{ spriteWidth * 6, 0, spriteWidth, spriteHeight });
		}
	}
	else {
		if (frameTime < 1) {
			Sprite.setTextureRect(sf::IntRect{ spriteWidth * 2, 0, spriteWidth, spriteHeight });
		}
		else if (frameTime < 1.5) {
			Sprite.setTextureRect(sf::IntRect{ spriteWidth * 6, 0, spriteWidth, spriteHeight });
		}
	}
	
	if (frameTime >= 1.5) {
		lookingAway = !lookingAway;
		canAnimateIdle = true;
		m_frametime.restart();
	}
}




