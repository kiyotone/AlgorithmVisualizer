#include "Search.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Algorithm.h"
#include "Node.h"

Search::Search(){
}

void Search::init_solve(){

	Node start( initial_state , box[5][5]);
	goal_state = sf::Vector2i(10,4);
	// std::cout<<start.action.x<<' '<<start.action.y<<std::endl;
	start.box->rect.setFillColor(sf::Color::Red);
	alg.add(&start);
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

    for (int x = 0; x < 40; x++)
	{
		std::vector<Box*> temp_box;
		for (int y = 0; y < 40; y++)
		{
			temp_box.push_back(new Box(origin.x + (x * 16), origin.y + (y * 16), 16, 16));
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
			else if(sfEvent.key.code == sf::Keyboard::S ){
				searching= true;
			}

		}
	}
		
		
		}

void Search::update(){

	updateSFMLevents();
    mouse->update(box, *window);
	
	
        
	

	totalTime += deltime;


    if (totalTime >= switchTIme and searching) {
       
    
		solve();
		
	    totalTime = 0;

	}
	update_boxes();

}

void Search::update_boxes(){

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

void Search::draw_boxes(){
    	//Draw
		for (int x = 0; x < 40; x++)
		{
			for (int y = 0; y < 40; y++)
			{
				if(!box[x][y]->animating)
					window->draw(box[x][y]->rect);
			}
		}
		for (int x = 0; x < 40; x++)
		{
			for (int y = 0; y < 40; y++)
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
	this->window =  new sf::RenderWindow(mode, "SFML works!",sf::Style::Fullscreen);
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

		window->close();
	}
	
	Node *node = alg.remove();
	
	

	if (node->state == goal_state){
		node->box->rect.setFillColor(sf::Color::Red);

		while (node->parent->state != initial_state)
		{
			actions.push_back(node->action);
			std::cout<< node->state.x <<" "<<node->state.y<<std::endl;
			node = node->parent;
			node->box->animating=true;
			node->box->path=true;

			
		}
			std::cout<< actions.size()<<std::endl;
		
		this->searching = false;
		// window->close();

	}
	
	if (this->searching){

		
	node->box->animating= true;

	alg.explored.push_back(node->state);
	

      

	// if(node->state != initial_state){

	// 	std::cout<<"State  "<<node->state.x<<" "<<node->state.y <<std::endl;	
	// 	std::cout<<"Child  "<<node->state.x<<" "<<node->state.y <<std::endl;	
    //     std::cout<<"Parent  "<<node->parent->state.x<<" "<<node->parent->state.y <<std::endl;	
    	

	// } 
	
	std::vector<sf::Vector2i> act = node->get_actions();



	for (int a = 0; a< act.size();a++){
		
		if( !alg.contains_state(act[a]) and !alg.inExplored(act[a])){
			
			std::cout<<std::endl;
			std::cout<<"Action  "<< act[a].x <<" " <<act[a].y<<std::endl;
			
			Box *box_ = box[act[a].x][act[a].y];
	
			Node *child = new Node( sf::Vector2i(act[a].x,act[a].y) , node , sf::Vector2i(act[a].x,act[a].y) , box_ );

			alg.add(child);


		}
	}
		std::cout<<"Frontier  "<<alg.frontier.size()<<std::endl;

		std::cout<<std::endl;
		std::cout<<std::endl;
		std::cout<<std::endl;
	
	}

}
