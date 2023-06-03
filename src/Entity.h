#pragma once

#include <SFML/Graphics.hpp>

class Entity
{

private:

public:
    Entity(int x, int y, int width, int height);
    sf::Vector2i pos;
    sf::Vector2i dim;
    bool entity_over(sf::Vector2i pos2);

};