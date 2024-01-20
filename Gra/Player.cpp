#include "Player.h"



void Player::initVariables()
{
	movementSpeed = 10.f;
	hpMax = 10;
	hp = hpMax;
    size = 20;
}

void Player::initShape()
{

    // Inicjalizacja wê¿a z jednym segmentem
    sf::CircleShape segment(size);
    segment.setFillColor(sf::Color::Red);
    segment.setPosition(50.f, 50.f);
    segments.push_back(segment);
}

Player::Player()
{
	initVariables();
	initShape();
}

Player::~Player()
{
}

const sf::CircleShape& Player::getShape() const
{
	return shape;
}

const std::vector<sf::CircleShape> Player::getSegments() const
{
    return segments;
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
void Player::grow()
{
    sf::CircleShape newSegment(size); 
    newSegment.setFillColor(sf::Color::Red); 
    newSegment.setPosition(segments.back().getPosition()); // Ustaw pozycjê nowego segmentu na koñcu wê¿a
    segments.push_back(newSegment); // Dodaj nowy segment do wektora
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
    sf::Vector2f headPos = segments.front().getPosition();
    float headRadius = segments.front().getRadius();

    // Left edge check (player fully exited on the right)
    if (headPos.x - headRadius > target->getSize().x) {
        segments.front().setPosition(-headRadius, headPos.y);
    }
    // Right edge check (player fully exited on the left)
    else if (headPos.x + headRadius < 0.f) {
        segments.front().setPosition(target->getSize().x + headRadius, headPos.y);
    }

    // Top edge check (player fully exited on the bottom)
    if (headPos.y - headRadius > target->getSize().y) {
        segments.front().setPosition(headPos.x, -headRadius);
    }
    // Bottom edge check (player fully exited on the top)
    else if (headPos.y + headRadius < 0.f) {
        segments.front().setPosition(headPos.x, target->getSize().y + headRadius);
    }
}


void Player::update(const sf::RenderTarget* target)
{	
    // Window bounds collision
    updateWindowBoundsCollision(target);
    updateInput();
}

void Player::render(sf::RenderTarget* target)
{
    for (const auto& segment : segments) {
        target->draw(segment);
    }
}

