#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h" 
class Snake
{
private:

protected:
	//objects
	sf::CircleShape segment;
	std::vector<sf::CircleShape> segments;
	//functions
	void initVariables();
	void initShape();
public:
	Snake();
	virtual ~Snake();
	//objects
	const sf::CircleShape& getShape() const;
	const std::vector<sf::CircleShape>& getSegments() const; // Wersja const
	std::vector<sf::CircleShape>& getSegments(); // Wersja niestandardowa
	int size;
	//functions
	virtual void update(const sf::RenderTarget* target);
	// Metoda do dodawania nowego segmentu
	void grow();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void checkCollisionWithObjects(std::vector<Object>& objects);
	bool checkSelfCollision() const;
	void render(sf::RenderTarget* target);
};

