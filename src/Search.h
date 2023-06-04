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
	~Search();

	sf::RenderWindow* window;
	Mouse* mouse;
	sf::Vector2i origin = sf::Vector2i(32, 32);
	std::vector<std::vector<Box*>> box;
	float deltime;
	sf::Clock clock;
	sf::Event sfEvent;
	Algorithm alg;
	sf::Vector2i goal_state;
	std::vector<sf::Vector2i> actions;
	float totalTime = .0f;
	float switchTIme = .1f;
	bool searching = false;
	bool search_complete = false;

	sf::Vector2i initial_state = sf::Vector2i(5, 5);

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
