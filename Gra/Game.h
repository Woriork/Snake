#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <cmath>
#include "Player.h"
#include "Object.h"
#include "Enemies.h"

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

	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Game LOGIC
	bool endgame;
	unsigned points;
	bool mouseHeld;


	//Objects
	Player player;
	//Enemies
	Enemies enemies;
	//food
	std::vector <Object> objects;
	float spawnTimerMax;
	float spawnTimer;
	int maxObjects;

	//private functions
	void initVariables();
	void initWindow();

public:
	//constructors /destructors
	Game();
	virtual ~Game();
	//Accessors
	const bool running() const;
	const bool getEndGame() const;

	//Functions
	void spawnObjects();
	void pollEvents();
	void updateMousePositions();
	void updateObjects();
	void updateCollision();
	void update();
	void render();

};

