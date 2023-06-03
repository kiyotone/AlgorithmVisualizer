#include "Entity.h"

Entity::Entity(int x, int y, int width, int height) {
    pos = sf::Vector2i(x, y);
    dim = sf::Vector2i(width, height);
}

bool Entity::entity_over(sf::Vector2i pos2) {

    if (this->pos.x < pos2.x and this->pos.x + this->dim.x > pos2.x) {

        if (this->pos.y < pos2.y and this->pos.y + this->dim.y > pos2.y)
        {
            return true;
        }
        else {
            return false;
        }

    }
    else {
        return false;
    }

}