#include "Object.h"

void Object::initVariables()
{
}

void Object::initObject(const sf::RenderWindow& window)
{
    sf::Color color(rand() % 255, rand() % 255, rand() % 255);
    object.setFillColor(color);
    object.setPosition(sf::Vector2f(
    static_cast<float>(rand() % window.getSize().x - object.getGlobalBounds().width),
    static_cast<float>(rand() % window.getSize().y - object.getGlobalBounds().height)));
    object.setRadius(25.f);

    movement = sf::Vector2f(static_cast<float>(std::rand() % 3 - 1), static_cast<float>(std::rand() % 3 - 1));

}
Object::Object(const sf::RenderWindow& window)
{
    initObject(window);
}

Object::~Object()
{
}

void Object::update(sf::RenderTarget& target)
{

}

const sf::CircleShape Object::getShape() const
{
    return object;
}

// ta funkcja jest do u¿ycia po usunieciu getshape, bedzie bardziej praktyczna na sprie
const sf::FloatRect Object::getBounds() const
{
    return object.getGlobalBounds();
}

void Object::move(const sf::Vector2f& offset)
{
    object.move(movement);
}

void Object::checkCollision(const sf::RenderWindow& window)
{
    // SprawdŸ kolizjê z krawêdziami okna
    if (object.getPosition().x < 0 || object.getPosition().x + object.getRadius() * 2 > window.getSize().x ||
        object.getPosition().y < 0 || object.getPosition().y + object.getRadius() * 2 > window.getSize().y)
    {
        movement = -movement;
    }
}



void Object::render(sf::RenderTarget& target)
{
	target.draw(object);
}

