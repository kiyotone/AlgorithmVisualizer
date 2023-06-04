#include "Search.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Algorithm.h"
#include "Node.h"

Search::Search()
{
}

void Search::init_solve()
{
	Node start(initial_state, box[5][5]);
	goal_state = sf::Vector2i(4, 4);
	// std::cout<<start.action.x<<' '<<start.action.y<<std::endl;
	alg.add(start);
}

void Search::init()
{
	init_boxes();
	init_window();
	init_variables();
	init_solve();
}

void Search::init_variables()
{
	deltime = 0.0f;
}

void Search::init_boxes()
{
	for (int x = 0; x < 40; x++)
	{
		std::vector<Box*> temp_box;
		for (int y = 0; y < 40; y++)
		{
			temp_box.push_back(new Box(origin.x + (x * 32), origin.y + (y * 32), 32, 32));
		}
		box.push_back(temp_box);
	}
}

void Search::updateSFMLevents()
{
	deltime = clock.restart().asSeconds();
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
		if (sfEvent.type == sf::Event::KeyPressed)
		{
			if (sfEvent.key.code == sf::Keyboard::Q or sfEvent.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
			else if (sfEvent.key.code == sf::Keyboard::S)
			{
				searching = true;
			}
		}
	}
}

void Search::update()
{
	updateSFMLevents();
	mouse->update(box, *window);


	totalTime += deltime;


	if (totalTime >= switchTIme and searching)
	{
		solve();

		totalTime = 0;
	}
	update_boxes();
}

void Search::update_boxes()
{
	for (int x = 0; x < 40; x++)
	{
		for (int y = 0; y < 40; y++)
		{
			if (box[x][y]->animating)
			{
				box[x][y]->animate(deltime);
			}
		}
	}
}

void Search::draw_boxes()
{
	//Draw
	for (int x = 0; x < 40; x++)
	{
		for (int y = 0; y < 40; y++)
		{
			if (!box[x][y]->animating)
				window->draw(box[x][y]->rect);
		}
	}
	for (int x = 0; x < 40; x++)
	{
		for (int y = 0; y < 40; y++)
		{
			if (box[x][y]->animating)
				window->draw(box[x][y]->rect);
		}
	}
}

void Search::draw()
{
	window->clear();
	draw_boxes();
	window->display();
}

void Search::init_window()
{
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	this->window = new sf::RenderWindow(mode, "SFML works!");
}

void Search::run()
{
	while (this->window->isOpen())
	{
		// * Update

		update();


		// * Draw

		draw();
	}
}

void Search::solve()
{
	if (alg.empty())
	{
		std::cout << "Empty" << std::endl;

		window->close();
	}

	Node node = alg.remove();


	if (node.state == goal_state)
	{
		// search_complete = true;
		// searching=false;

		// while (node.parent->state != initial_state)
		// {
		// 	actions.push_back(node.action);

		// 	Node *node_ = node.parent;

		// 	std::cout<< node_->state.x <<" "<<node_->state.y<<std::endl;
		// }
		window->close();
	}


	node.box->animating = true;

	alg.explored.push_back(node.state);


	std::cout << "Explored  " << alg.explored.size() << std::endl;

	if (node.state != initial_state)
	{
		std::cout << "State  " << node.state.x << " " << node.state.y << std::endl;
		std::cout << "Parent  " << node.parent->action.x << " " << node.parent->action.y << std::endl;
	}

	std::vector<sf::Vector2i> act = node.get_actions();


	for (int a = 0; a < act.size(); a++)
	{
		if (!alg.contains_state(act[a]) and !alg.inExplored(act[a]))
		{
			std::cout << std::endl;
			std::cout << "Action  " << act[a].x << " " << act[a].y << std::endl;

			Box* box_ = box[act[a].x][act[a].y];


			auto child = new Node(sf::Vector2i(act[a].x, act[a].y), &node, sf::Vector2i(act[a].x, act[a].y), box_);

			std::cout << "CHILD     " << child->state.x << " " << child->state.y << std::endl;
			std::cout << "PARENT    " << child->parent->state.x << " " << child->parent->state.y << std::endl;

			alg.add(*child);
		}
	}
	std::cout << "Frontier  " << alg.frontier.size() << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}
