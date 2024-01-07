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

	//Functions
	void initVariables();
	void initObject(const sf::RenderWindow& window);

public:

	Object(const sf::RenderWindow& window);
	virtual ~Object();

	//Functions
	void update(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

