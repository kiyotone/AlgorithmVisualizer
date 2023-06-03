#include <SFML/Graphics.hpp>
#include <iostream>
#include "Mouse.h"
#include <array>

Mouse::Mouse(int x, int y, int width, int height) :Entity(x, y, width, height) {

}

void Mouse::update(std::vector<std::vector<Box*>> box, sf::RenderWindow& window)
{
    pos = sf::Mouse::getPosition(window);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        for (int i = 0; i < box.size(); i++) {

            for (int j = 0; j < box[0].size(); j++) {

                if (box[i][j]->entity_over(pos)) {
                    box[i][j]->animating = true;



                }
            }

        }

    }
}