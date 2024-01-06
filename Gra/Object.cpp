#include "Object.h"

void Object::initVariables()
{
}

void Object::initObject(const sf::RenderWindow& window)
{
    sf::Color color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
    object.setFillColor(color);
    object.setPosition(sf::Vector2f(
    static_cast<float>(rand() % window.getSize().x - object.getGlobalBounds().width),
    static_cast<float>(rand() % window.getSize().y - object.getGlobalBounds().height)));
    object.setRadius(25.f);

}
Object::Object(const sf::RenderWindow& window)
{
    initObject(window);
}

Object::~Object()
{
}




void Object::update()
{
}

void Object::render(sf::RenderTarget& target)
{
	target.draw(object);
}

void Object::spawnObjects()
{
}
