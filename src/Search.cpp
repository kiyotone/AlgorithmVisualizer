#include "Search.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Algorithm.h"
#include "Node.h"

Search::Search(){
}

void Search::init_solve(){

	Node start( sf::Vector2i(0,0),box[0][0]);
	goal_state = sf::Vector2i(128,128);
	std::cout<<start.action.x<<' '<<start.action.y<<std::endl;
	frontier.add(start);
}

void Search::init(){

    init_boxes();
	init_window();
    init_variables();
	init_solve();

}

void Search::init_variables(){
    deltime = 0.0f;
}

void Search::init_boxes(){

    for (int x = 0; x < matrix_height; x++)
	{
		std::vector<Box*> temp_box;
		for (int y = 0; y < matrix_width; y++)
		{
			temp_box.push_back(new Box(origin.x + (x * 32), origin.y + (y * 32), 32, 32));
		}
		box.push_back(temp_box);
	}
}

void Search::updateSFMLevents(){
		
		deltime = clock.restart().asSeconds();
		while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
		if (sfEvent.type == sf::Event::KeyPressed){
			if(sfEvent.key.code == sf::Keyboard::Q or sfEvent.key.code == sf::Keyboard::Escape ){
				this->window->close();
			}
		
		}
	}
		
		
		}

void Search::update(){

	updateSFMLevents();
    mouse->update(box, *window);
    update_boxes();

	// solve();
}

void Search::update_boxes(){

	for (int x = 0; x < matrix_height; x++)
		{
			for (int y = 0; y < matrix_width; y++)
			{
				if (box[x][y]->animating)
				{
					box[x][y]->animate(deltime);
				}
			}
		}

}

void Search::draw_boxes(){
    	//Draw
		for (int x = 0; x < matrix_height; x++)
		{
			for (int y = 0; y < matrix_width; y++)
			{
				if(!box[x][y]->animating)
					window->draw(box[x][y]->rect);
			}
		}
		for (int x = 0; x < matrix_height; x++)
		{
			for (int y = 0; y < matrix_width; y++)
			{
				if(box[x][y]->animating)
					window->draw(box[x][y]->rect);
			}
		}

}

void Search::draw(){
        window->clear();
        draw_boxes();
        window->display();
}

void Search::init_window(){
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	this->window =  new sf::RenderWindow(mode, "SFML works!");
}

void Search::run(){


	while (this->window->isOpen()){
		// * Update

		update();
	

		// * Draw

		draw();

		

	}
}

void Search::solve(){

	if(frontier.empty()){
		window->close();
	}
	
	Node node = frontier.remove();
	
	std::cout<<node.action.x<<' '<<node.action.y<<std::endl;


	if (node.state == goal_state){

		while (node.parent->state != initiai_state)
		{
			actions.push_back(node.action);
			node = *node.parent;
			std::cout<< node.box->pos.x <<" "<<node.box->pos.y<<std::endl;
		}
		window->close();
		
	}
	frontier.explored.push_back(node.state);

	actions = node.get_actions();

	for (int x = 0; x< actions.size();x++){
		if( !frontier.contains_state(actions[x]) and !frontier.inExplored(actions[x])){
			Box *box_ = box[actions[x].x][actions[x].y];
			sf::Vector2i act = actions[x];

			Node child = Node(act , &node , act , box_ );
			frontier.add(child);
		}
	}








}