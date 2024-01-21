#include "Enemies.h"
#include <cstdlib>



Enemies::Enemies()
{   movement = sf::Vector2f(static_cast<float>(std::rand() % 3 - 1), static_cast<float>(std::rand() % 3 - 1));

}

Enemies::~Enemies()
{
}

void Enemies::update(const sf::RenderTarget* target)
{
    updateWindowBoundsCollision(target);
        for (size_t i = segments.size() - 1; i > 0; --i)
    {
        sf::Vector2f prevPos = segments[i - 1].getPosition();
        segments[i].setPosition(prevPos);
    }
    segments.front().move(movement);

}
