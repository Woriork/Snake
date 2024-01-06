#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
class Player
{
private:
	sf::RectangleShape shape;
	float movementSpeed;
	int hp;
	int hpMax;

	//functions
	void initVariables();
	void initShape();
public:
	Player();
	virtual ~Player();

	//Functions
	void update(const sf::RenderTarget* target);
	void updateInput();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);

};

