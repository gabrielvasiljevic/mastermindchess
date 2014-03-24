#include "headers/GUI.h"


Interface_Element::Interface_Element(int x, int y, int size_x, int size_y){
    this->pos_x = x;
    this->pos_y = y;
    this->image.setPosition(x, y);
    sf::RectangleShape shape(sf::Vector2f(size_x, size_y)); //Create the shape of a square of size 60x60 pixels
    shape.setPosition(x, y);
    this->square = shape;
    sf::FloatRect squareRect(this->square.getPosition().x, this->square.getPosition().y, this->square.getSize().x, this->square.getSize().y);
    this->rectSquare = squareRect;
}

bool Interface_Element::clicked(int x, int y){
    if(this->rectSquare.contains(x, y)) return true;
    else return false;
}
