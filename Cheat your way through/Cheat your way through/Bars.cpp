#include "Bars.h"
#include "Game.h"



void Bar::writeAndCopy(bool isRestricted, std::string &message, bool &endGame )  //code for 2 bars, one fills out before the other and effectively sets a maximum for the other.
{
	int speed = 15; //speed at which the bars progress.

	if (!isRestricted)
	{
		
			copyBar.lenght += speed;
			barBody.setSize(sf::Vector2f{ copyBar.lenght, copyBar.height });
			writeBar.maximum = copyBar.lenght;
		
	}
	else if (writeBar.lenght < writeBar.maximum) //effectively: if isRestricted == true AND lenght < maximum
	{
		writeBar.lenght += speed;
		barBody.setSize(sf::Vector2f{ writeBar.lenght, writeBar.height });
		if (writeBar.lenght >= 725) {
			message = "You succesfully\n copied the\n whole exam!";
			endGame = true;
		}

	}

}

void Bar::setupBars(bool t_blueColor) //sets up the objects
{
	
	barBody.setSize(sf::Vector2f{writeBar.lenght, writeBar.height });
	barBody.setPosition(writeBar.X_COORDINATE, writeBar.Y_COORDINATE);
	if (t_blueColor) {
		barBody.setFillColor(sf::Color::Blue);
	}
	else {
		barBody.setFillColor(sf::Color::White);
	}
}
