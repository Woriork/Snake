#include "Snake.h"

void Snake::initVariables()
{
	
	size = 20;
}

void Snake::initShape()
{
	// Inicjalizacja wê¿a z jednym segmentem
	segment.setRadius(size);
	segment.setFillColor(sf::Color::White);
	segment.setPosition(50.f, 50.f);
	segments.push_back(segment);
}

Snake::Snake()
{
	initVariables();
	initShape();
}

Snake::~Snake()
{
}

const sf::CircleShape& Snake::getShape() const
{
	return segment;
}

const std::vector<sf::CircleShape>& Snake::getSegments() const
{
	return segments;
}

std::vector<sf::CircleShape>& Snake::getSegments()
{
	return segments;
}

void Snake::update(const sf::RenderTarget* target)
{
	//logika aktualizacji dla wê¿a
}

void Snake::grow()
{
	sf::CircleShape newSegment(size);
	sf::Color color(rand() % 255, rand() % 255, rand() % 255);
	newSegment.setFillColor(color);

	// Ustaw pozycjê nowego segmentu na koñcu poprzedniego segmentu
	sf::Vector2f lastSegmentPos = segments.back().getPosition();
	float lastSegmentRadius = segments.back().getRadius();
	float newSegmentRadius = newSegment.getRadius();

	float newX = lastSegmentPos.x + (2 * lastSegmentRadius + 2 * newSegmentRadius);
	float newY = lastSegmentPos.y;

	newSegment.setPosition(newX, newY);
	segments.push_back(newSegment); // Dodaj nowy segment do wektora
}


void Snake::updateWindowBoundsCollision(const sf::RenderTarget* target)
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


void Snake::checkCollisionWithObjects(std::vector<Object>& objects)
{
	auto it = objects.begin();
	while (it != objects.end()) {
		bool collisionDetected = false;

		// SprawdŸ kolizjê tylko z g³ow¹ wê¿a (pierwszym segmentem)
		if (segments.front().getGlobalBounds().intersects(it->getBounds())) {
			grow();
			collisionDetected = true;
		}

		if (collisionDetected) {
			it = objects.erase(it);
		}
		else {
			++it;
		}
	}
}

bool Snake::checkSelfCollision() const
{
	// SprawdŸ kolizjê g³owy z ogonem (segmentami od drugiego do ostatniego)
	for (size_t i = 1; i < segments.size(); ++i)
	{
		if (segments.front().getGlobalBounds().intersects(segments[i + 5].getGlobalBounds()))
		{
			return true; // Kolizja wystêpuje
		}
	}
	return false;
}

void Snake::render(sf::RenderTarget* target)
{
	for (const auto& segment : segments) {
		target->draw(segment);
	}
}
