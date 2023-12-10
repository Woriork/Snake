#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
	Class that acts as the game angine.
	Wrapper class
*/

class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	void initVariables();
	void initWindow();

public:
	//constructors /destructors
	Game();
	virtual ~Game();
	//Accessors
	const bool running() const;

	//Functions
	void pollEvents();
	void update();
	void render();

};

