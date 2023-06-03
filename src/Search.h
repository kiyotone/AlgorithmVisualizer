#pragma once
#include "Mouse.h"
#include <SFML/Graphics.hpp>
#include "Node.h"
#include "Algorithm.h"

class Search
{
private:
    int matrix_height = 32;
    int matrix_width = 32;

public:

    Search();

    sf::RenderWindow *window;
    Mouse* mouse = new Mouse(0, 0, 2, 2);  
    sf::Vector2i origin = sf::Vector2i(32, 32);
    std::vector<std::vector<Box*>> box;
    float deltime;
    sf::Clock clock;
    sf::Event sfEvent;
    Algorithm frontier;
    sf::Vector2i goal_state;
    std::vector<sf::Vector2i> actions;
  
    sf::Vector2i initiai_state;
    

    void init();
    void init_variables();
    void init_window();
    void init_boxes();
    
    void update();
    void updateSFMLevents();
    void update_boxes();

    void draw_boxes();
    void draw();

    void solve();
    void init_solve();

    void run();





};