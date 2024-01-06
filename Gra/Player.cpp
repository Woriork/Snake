#include "Player.h"



void Player::initVariables()
{
	movementSpeed = 10.f;
	hpMax = 10;
	hp = hpMax;
}

void Player::initShape()
{
	shape.setFillColor(sf::Color::Red);
	shape.setSize(sf::Vector2f(100.f, 100.f));
}

Player::Player()
{
	shape.setPosition(50.f,50.f);
	initVariables();
	initShape();
}

Player::~Player()
{
}

void Player::updateInput()
{
	//window bounds collision
	//keyboard input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		shape.move(-movementSpeed, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		shape.move(movementSpeed, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		shape.move(0.f,-movementSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		shape.move(0.f,movementSpeed);
	}
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
    sf::Vector2f playerPos = shape.getPosition();
    sf::Vector2f playerSize = shape.getSize();

    // Left edge check (player fully exited on the right)
    if (playerPos.x + playerSize.x < 0.f) {
        shape.setPosition(target->getSize().x, playerPos.y);
    }
    // Right edge check (player fully exited on the left)
    else if (playerPos.x > target->getSize().x) {
        shape.setPosition(-playerSize.x, playerPos.y);
    }

    // Top edge check (player fully exited on the bottom)
    if (playerPos.y + playerSize.y < 0.f) {
        shape.setPosition(playerPos.x, target->getSize().y);
    }
    // Bottom edge check (player fully exited on the top)
    else if (playerPos.y > target->getSize().y) {
        shape.setPosition(playerPos.x, -playerSize.y);
    }
}



void Player::update(const sf::RenderTarget* target)
{	
	//Window bounds collision
	updateWindowBoundsCollision(target);
	updateInput();
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(shape);
}

