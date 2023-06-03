#include "Search.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Algorithm.h"
#include "Node.h"

Search::Search(){
}

void Search::init_solve(){

	Node start( sf::Vector2i(5,5) , box[5][5]);
	goal_state = sf::Vector2i(23,23);
	// std::cout<<start.action.x<<' '<<start.action.y<<std::endl;
	alg.add(start);
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
	
	
        
	solve();


    

	update_boxes();

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

	if(alg.empty()){
		std::cout<<"Empty"<<std::endl;

		// window->close();
	}
	
	Node node = alg.remove();
	
	std::cout<<"Node  "<<node.state.x<<" "<<node.state.y <<std::endl;	


	if (node.state == goal_state){

		while (node.parent->state != initiai_state)
		{
			actions.push_back(node.action);
			node = *node.parent;
			std::cout<< node.box->pos.x <<" "<<node.box->pos.y<<std::endl;
		}
		// window->close();
		
	}
	
	

	node.box->animating= true;
	alg.explored.push_back(node.state);
	

	std::cout<<"Explored  "<<alg.explored.size()<<std::endl;
	
	std::vector<sf::Vector2i> act =  node.get_actions();



	for (int a = 0; a< act.size();a++){
		
		if( !alg.contains_state(act[a]) and !alg.inExplored(act[a])){
			
			std::cout<<"Action  "<< act[a].x <<" " <<act[a].y<<std::endl;

			Box *box_ = box[act[a].x][act[a].y];
			
			sf::Vector2i action = act[a];
			
	
	
			Node child = Node(action , &node , action , box_ );
			alg.add(child);


		}
	}
		std::cout<<"Frontier  "<<alg.frontier.size()<<std::endl;

		std::cout<<std::endl;
	


}