#include <SFML/Graphics.hpp>
#include "Node.h"
#include "Box.h"
#include <math.h>


Node::Node(sf::Vector2i state, Node* parent, sf::Vector2i action , Box *box){
        this->parent = parent;
        this->action = action;
        this->box = box;
        this->state = state;
        
}

Node::Node(sf::Vector2i state,Box *box){
        this->box = box;
        this->state = state;
        
}

std::vector<sf::Vector2i> Node::get_actions(){

        std::vector<sf::Vector2i> actions;
        
        for(unsigned int a=1;a<3;a++){
                for(unsigned int b=1;b<3;b++){
                        int xpos = box->pos.x+ pow(1,a);
                        int ypos = box->pos.y+ pow(1,b);
                        actions.push_back(sf::Vector2i( xpos,ypos));
                        
                        }
        
        }

        return actions;

    
    

        }