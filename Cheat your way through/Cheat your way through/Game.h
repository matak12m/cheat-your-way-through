/// <summary>
/// author Matt March 2023
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void processMouse(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();
	void turnToMouse(int t_recX, int t_rectY, int t_width, int t_height);

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_clockFont; // font used by message
	sf::Text m_clock; // text used for message on screen
	
	bool m_exitGame; // control exiting game
	bool isSuspicious = false;  //todo: replace these booleans with a single integer instead
	bool isCopying = false;
	bool isWriting = false;
	sf::Texture
		m_HUDTexture; 
		
	sf::Sprite
		m_progressBarSprite,  //part of hud
		m_bellSprite,   //part of hud
		m_clockSprite;   //part of hud
	
	
	const int    //values of the textureRect for player
		PLAYER_RECT_X = 0,
		PLAYER_RECT_Y = 0,
		PLAYER_WIDTH = 96,
		PLAYER_HEIGHT = 105;

	const int spriteHeight = 128;
	const int spriteWidth = 96;

};
#endif // !GAME_HPP

