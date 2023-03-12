/// <summary>
/// @author Matt
/// @date March 2023
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>
#include "Bars.h"


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
	copyBar.isRestricted = false;
	writeBar.isRestricted = true;
	writeBar.setupBars(writeBar.isRestricted);
	copyBar.setupBars(copyBar.isRestricted);
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
		if ((isCopying || isWriting) && sf::Event::MouseButtonPressed == newEvent.type)
		{
			processMouse(newEvent);
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

void Game::processMouse(sf::Event t_event) {
	if (isCopying && sf::Mouse::Left== t_event.key.code)   //currentl doesnt support holding down left click
	{
		copyBar.increase(copyBar.isRestricted);
		std::cout << "copying";
	}
	if (isWriting && sf::Mouse::Left == t_event.key.code)
	{
		writeBar.increase(writeBar.isRestricted);
		std::cout << "writing";
	}
}


/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	turnToMouse(PLAYER_RECT_X, PLAYER_RECT_Y, PLAYER_WIDTH, PLAYER_HEIGHT);
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
	m_window.draw(copyBar.barBody);
	m_window.draw(writeBar.barBody);
	m_window.draw(m_teacherSprite);
	m_window.draw(m_blockheadSprite);
	m_window.draw(m_playerSprite);
	m_window.draw(m_progressBarSprite);
	m_window.draw(m_clockSprite);
	m_window.draw(m_clock);
	m_window.draw(m_bellSprite);
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
	m_clock.setFont(m_clockFont);
	m_clock.setString("5:00");
	m_clock.setStyle(sf::Text::Bold);
	m_clock.setPosition(825, 125);
	m_clock.setCharacterSize(50U);
	m_clock.setFillColor(sf::Color::Red);

}

 
// setup function for all sprites and textures
void Game::setupSprite()
{
	//teacher sprite
	if (!m_teacherTexture.loadFromFile("ASSETS\\IMAGES\\Teacher-sprites-Final.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading teacher" << std::endl;
	}
	m_teacherSprite.setTexture(m_teacherTexture);
	m_teacherSprite.setPosition(250, 440);
	m_teacherSprite.setTextureRect(sf::IntRect{0, 0, 80, 125});
	m_teacherSprite.setScale(2, 2);

	//student sprite
	if (!m_studentTexture.loadFromFile("ASSETS\\IMAGES\\students.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading students" << std::endl;
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

	//HUD sprites
	if (!m_HUDTexture.loadFromFile("ASSETS\\IMAGES\\HUD.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading HUD" << std::endl;
	}

	//progress bar
	m_progressBarSprite.setTexture(m_HUDTexture);
	m_progressBarSprite.setPosition(95, 125);
	m_progressBarSprite.setTextureRect(sf::IntRect{ 0, 0, 900, 80 });
	m_progressBarSprite.setScale(0.8, 1);

	//clock background
	m_clockSprite.setTexture(m_HUDTexture);
	m_clockSprite.setPosition(810, 120);
	m_clockSprite.setTextureRect(sf::IntRect{ 0, 80,224 ,80 });
	m_clockSprite.setScale(0.85, 1);
	//bell sprite
	m_bellSprite.setTexture(m_HUDTexture);
	m_bellSprite.setPosition(1000, 110);
	m_bellSprite.setTextureRect(sf::IntRect{ 240, 80, 128, 128 });


	
}

void Game::animateIdle(int t_height, int t_width)
{
	//todo: general animation script for teacher, player and blockhead.

}


void Game::turnToMouse(int t_rectX, int t_rectY, int t_width, int t_height)   //animates the player sporite to change depending on mouse position
{
//x = 1200
//y = 900
//xdesktop = 1920
//ydesktop = 1080
	const int
		LOOKUP_THRESHOLD_Y = 583,
		MIDDLE_THRESHOLD_X = 700,
		MIDDLE_THRESHOLD_Y = 500,
		COPY_THRESHOLD_X = 800,
		COPY_THRESHOLD_Y = 600;

	sf::Vector2f MousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window));  //getPosition(m_window) returns a position relative to the game window rather than the desktop.

	if (MousePosition.y >= COPY_THRESHOLD_Y && MousePosition.x >= COPY_THRESHOLD_X) {   //mousePosition > COPY instead of MousePosition < COPY, setting the sprite once the mouse is in the bottom right section of the screen 
		m_playerSprite.setTextureRect(sf::IntRect(t_rectX + t_width * 4, t_rectY, t_width, t_height));
		isSuspicious = true;
		isCopying = true;
		isWriting = false;

	}
	else if (MousePosition.x > MIDDLE_THRESHOLD_X) {
		m_playerSprite.setTextureRect(sf::IntRect(t_rectX + t_width * 3, t_rectY, t_width, t_height));  //sets the sprite to look at middle
		isSuspicious = true;
		isCopying = false;
		isWriting = false;
	}
	else if (MousePosition.y < LOOKUP_THRESHOLD_Y) {
		m_playerSprite.setTextureRect(sf::IntRect(t_rectX + t_width * 2, t_rectY, t_width, t_height));    //sets the sprite to looking up from desk if mouse is in the right location
		isSuspicious = false;
		isCopying = false;
		isWriting = false;
	}
	else {
		m_playerSprite.setTextureRect(sf::IntRect(t_rectX, t_rectY, t_width, t_height));  //temporary line until animateIdle is finished.
		isSuspicious = false;
		isCopying = false;
		isWriting = true;
		animateIdle(PLAYER_WIDTH, PLAYER_HEIGHT);  //plays the idle animation of player
		// writeDown();   (affect progress bar)

	}
}
