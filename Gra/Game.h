#pragma once

#include <iostream>
#include <vector>
#include <ctime>
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

	void pollEvents();
	void updateMousePositions();
	void updateEnemies();
	void update();
	void renderEnemies();
	void render();

};

