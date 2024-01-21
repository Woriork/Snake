#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Snake.h"

class Enemies:public Snake
{
private:
  

public:
    Enemies();
    virtual ~Enemies();

    sf::Vector2f movement;

    // Functions
    void update(const sf::RenderTarget* target) override;


};
