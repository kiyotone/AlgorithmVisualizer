#pragma once

#pragma once
#include "Entity.h"
#include "Box.h"

class Mouse : public Entity
{
private:

public:
    Mouse(int x, int y, int width, int height);
    void update(std::vector<std::vector<Box*>> box, sf::RenderWindow& window);

};