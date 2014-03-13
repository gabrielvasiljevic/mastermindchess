#include <SFML/Graphics.hpp>
#define SIZE 60
#include "squares.h"


Square::Square(){
    sf::RectangleShape shape(sf::Vector2f(60, 60));
    this->square = shape;
    sf::FloatRect squareRect(this->square.getPosition().x, this->square.getPosition().y, this->square.getSize().x, this->square.getSize().y);
    this->rectSquare = squareRect;
    clicked = false;
}

bool Square::verify_click(int x, int y){
    return this->rectSquare.contains(x,y);
}
