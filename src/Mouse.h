#pragma once

#pragma once
#include "Entity.h"
#include "Box.h"
#include <SFML/Graphics.hpp>

class Mouse : public Entity
{
private:
    

public:
    sf::Vector2i selected;
    Mouse(int x, int y, int width, int height);
    void update(std::vector<std::vector<Box*>> box, sf::RenderWindow& window);

};