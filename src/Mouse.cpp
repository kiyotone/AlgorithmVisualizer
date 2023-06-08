#include <SFML/Graphics.hpp>
#include <iostream>
#include "Mouse.h"
#include <array>

Mouse::Mouse(int x, int y, int width, int height) :Entity(x, y, width, height) {

}

void Mouse::update(std::vector<std::vector<Box*>> box, sf::RenderWindow& window)
{
    pos = sf::Mouse::getPosition(window);
    // std::cout<<pos.x<<" "<<pos.y<<std::endl;
    
    int mouse_x = (int)(pos.x-32)/16;
    int mouse_y = (int)(pos.y-32)/16;
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    
                    box[this->selected.x][this->selected.y]->rect.setFillColor(sf::Color::Green);    
                    
                    this->selected = sf::Vector2i(mouse_x,mouse_y);
                    box[this->selected.x][this->selected.y]->rect.setFillColor(sf::Color::Red);
    }
}