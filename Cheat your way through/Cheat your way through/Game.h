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
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_clockFont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	
	bool m_exitGame; // control exiting game

	sf::Texture
		m_teacherTexture,
		m_studentTexture;
	sf::Sprite
		m_teacherSprite,  //teacher sprites
		m_blockheadSprite, //student sprites
		m_playerSprite;  //sprites for player
};

#endif // !GAME_HPP

