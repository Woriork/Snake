#include "Player.h"

Player::Player()
{
    movementSpeed = 10.f;

}

Player::~Player()
{
}

void Player::update(const sf::RenderTarget* target)
{
    updateWindowBoundsCollision(target);
    updateInput();
   
}
void Player::updateInput()
{
    for (size_t i = segments.size() - 1; i > 0; --i)
    {
        sf::Vector2f prevPos = segments[i - 1].getPosition();
        segments[i].setPosition(prevPos);
    }
    // Pobierz aktualn¹ pozycjê myszy
    sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);

    // Ustaw pozycjê myszy na przedniej krawêdzi g³owy wê¿a
    mousePosition.x -= segments.front().getRadius();
    mousePosition.y -= segments.front().getRadius();

    // Je¿eli pozycja myszki zmieni³a siê wzglêdem poprzedniej klatki, zaktualizuj kierunek ruchu
    if (mousePosition != lastMousePosition) {
        sf::Vector2f direction = mousePosition - segments.front().getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length != 0) {
            direction /= length;
            lastDirection = direction;
        }

        // Zaktualizuj ostatni¹ znan¹ pozycjê myszy
        lastMousePosition = mousePosition;
    }

    // Ustaw prêdkoœæ ruchu wê¿a na ostatni znany kierunek ruchu
    sf::Vector2f movement = lastDirection * movementSpeed;

    // Przesuwaj tylko g³owê wê¿a, reszta segmentów pod¹¿y za ni¹ w metodzie move()
    segments.front().move(movement);
}



