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
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	//game objects
	std::vector<sf::RectangleShape> enemies;
	//sf::Sprite
	sf::RectangleShape enemy;

	//Objects
	Player player;
	std::vector <Object> objects;
	float spawnTimerMax;
	float spawnTimer;
	int maxObjects;

	//private functions
	void initVariables();
	void initWindow();
	void initEnemies();

public:
	//constructors /destructors
	Game();
	virtual ~Game();
	//Accessors
	const bool running() const;
	const bool getEndGame() const;

	//Functions
	void spawnEnemies();
	void spawnObjects();
	void pollEvents();
	void updateMousePositions();
	void updateEnemies();
	void update();
	void renderEnemies();
	void render();

};

