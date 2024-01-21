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
    // Pobierz aktualn� pozycj� myszy
    sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);

    // Ustaw pozycj� myszy na przedniej kraw�dzi g�owy w�a
    mousePosition.x -= segments.front().getRadius();
    mousePosition.y -= segments.front().getRadius();

    // Je�eli pozycja myszki zmieni�a si� wzgl�dem poprzedniej klatki, zaktualizuj kierunek ruchu
    if (mousePosition != lastMousePosition) {
        sf::Vector2f direction = mousePosition - segments.front().getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length != 0) {
            direction /= length;
            lastDirection = direction;
        }

        // Zaktualizuj ostatni� znan� pozycj� myszy
        lastMousePosition = mousePosition;
    }

    // Ustaw pr�dko�� ruchu w�a na ostatni znany kierunek ruchu
    sf::Vector2f movement = lastDirection * movementSpeed;

    // Przesuwaj tylko g�ow� w�a, reszta segment�w pod��y za ni� w metodzie move()
    segments.front().move(movement);
}



