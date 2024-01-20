#pragma once
#include <SFML/Graphics.hpp>

class Player
{
private:
	sf::CircleShape shape;
	std::vector<sf::CircleShape> segments;
	//functions
	void initVariables();
	void initShape();
	sf::Vector2f lastDirection;
	sf::Vector2f lastMousePosition;
public:
	Player();
	virtual ~Player();

	const sf::CircleShape& getShape() const;
	const std::vector<sf::CircleShape>getSegments() const;
	int size;
	float movementSpeed;
	int hp;
	int hpMax;


	//Functions
	void update(const sf::RenderTarget* target);
	void updateInput();
	// Metoda do dodawania nowego segmentu
    void grow();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);

};

