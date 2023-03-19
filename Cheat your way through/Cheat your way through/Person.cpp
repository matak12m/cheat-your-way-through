#include "Person.h"

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
	float tempClock = teacher.m_frametime.getElapsedTime().asSeconds();    
	int positionClock = tempClock;
	std::cout << std::to_string(positionTime) + "  " + std::to_string(positionClock);
	std::cout << std::endl;
	if (positionClock > positionTime)   //if the random number is equal to the time ticking up
	{	 
		teacher.m_frametime.restart();
		  //todo: change positions of the teacher after random intervals, between looking away or not. play animation between these states.
	}
	else if (positionClock == positionTime || !canAnimateIdle) {
		//play the appropriate animation, specific for the teacher
		canAnimateIdle = false;
		
			if (!lookingAway) {

				std::cout << "Teacher swapping positions";
				//play animation of 2 -> 6 ->idle, and set looking away to true.
				teacherSwap();

			}
			else {

				std::cout << "Teacher swapping positions";
				//play animation of 5 -> 6->idle, and set looking away to false.
				teacherSwap();
			}
		lookingAway = !lookingAway;
		teacher.m_frametime.restart();
		canAnimateIdle = true;
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
							//DOESNT WORK, need to fix. somehow, it doesn't execute even though it's called? test message isn't being sent out.
{


	float frameTime = m_teacherFrameTime.getElapsedTime().asSeconds();
	while (frameTime < 1.5) {

		std::cout << "Teacher swapping positions";
		if (lookingAway) {
			if (frameTime < 1) {
				teacher.Sprite.setTextureRect(sf::IntRect{ spriteWidth * 5, 0, spriteWidth, spriteHeight });
			}
			else if (frameTime < 1.5) {

				teacher.Sprite.setTextureRect(sf::IntRect{ spriteWidth * 6, 0, spriteWidth, spriteHeight });
			}
		}
		else {
			if (frameTime < 1) {

				teacher.Sprite.setTextureRect(sf::IntRect{ spriteWidth * 2, 0, spriteWidth, spriteHeight });
			}
			else if (frameTime < 1.5) {

				teacher.Sprite.setTextureRect(sf::IntRect{ spriteWidth * 6, 0, spriteWidth, spriteHeight });
			}
		}
	}
	
}




