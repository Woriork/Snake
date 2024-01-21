#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
class Player:public Snake
{
private:


public:
	sf::Vector2f lastDirection;
	sf::Vector2f lastMousePosition;
	float movementSpeed;
	Player();
	virtual ~Player();
	


	//Functions
	void updateInput();
	void update(const sf::RenderTarget* target) override;
	

};

