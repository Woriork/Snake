#pragma once
#include <SFML/Graphics.hpp>

class Object
{
private:
	//game objects
	sf::CircleShape object;
	//movement diriection
	sf::Vector2f movement;
	
	//Functions
	void initVariables();
	void initObject(const sf::RenderWindow& window);

public:


	Object(const sf::RenderWindow& window);
	virtual ~Object();

	//Accerssors
	const sf::FloatRect getBounds() const;
	const sf::CircleShape getShape() const;

	//Functions
	void update(sf::RenderTarget& target);

	void move(const sf::Vector2f& offset);
	void checkCollision(const sf::RenderWindow& window);
	void render(sf::RenderTarget& target);
};

