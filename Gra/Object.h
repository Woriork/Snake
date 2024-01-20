#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <cmath>
class Object
{
private:
	//game objects
	std::vector<sf::RectangleShape> objects;
	//sf::Sprite
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

