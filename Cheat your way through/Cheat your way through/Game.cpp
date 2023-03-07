/// <summary>
/// @author Matt
/// @date March 2023
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1200U, 900U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color{200, 173, 123});
	m_window.draw(m_welcomeMessage);
	m_window.draw(m_teacherSprite);
	m_window.draw(m_blockheadSprite);
	m_window.draw(m_playerSprite);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_clockFont.loadFromFile("ASSETS\\FONTS\\digital.ttf"))
	{
		std::cout << "problem loading digital font" << std::endl;
	}
	m_welcomeMessage.setFont(m_clockFont);
	m_welcomeMessage.setString("5:00");
	m_welcomeMessage.setStyle(sf::Text::Bold);
	m_welcomeMessage.setPosition(825, 125);
	m_welcomeMessage.setCharacterSize(50U);
	m_welcomeMessage.setFillColor(sf::Color::Red);

}

 
// setup function for all sprites and textures
void Game::setupSprite()
{
	//teacher sprite
	if (!m_teacherTexture.loadFromFile("ASSETS\\IMAGES\\Teacher-sprites-Final.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_teacherSprite.setTexture(m_teacherTexture);
	m_teacherSprite.setPosition(250, 440);
	m_teacherSprite.setTextureRect(sf::IntRect{0, 0, 80, 125});
	m_teacherSprite.setScale(2, 2);

	//student sprite
	if (!m_studentTexture.loadFromFile("ASSETS\\IMAGES\\students.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_blockheadSprite.setTexture(m_studentTexture);
	m_blockheadSprite.setPosition(800, 500);
	m_blockheadSprite.setTextureRect(sf::IntRect{ 0,0,96,96 });
	m_blockheadSprite.setScale(2, 2);

	//player sprite
	
	m_playerSprite.setTexture(m_studentTexture);
	m_playerSprite.setPosition(600, 500);
	m_playerSprite.setTextureRect(sf::IntRect{ 0,96,96,96 });
	m_playerSprite.setScale(2, 2);
}
