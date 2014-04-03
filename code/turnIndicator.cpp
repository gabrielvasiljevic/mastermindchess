#include "headers/turnIndicator.h"
#include <string>
#include <iostream>

turnIndicator::turnIndicator(int x, int y, int size_x, int size_y) : Interface_Element(x, y, size_x, size_y){
    this->turn = true;
    this->texture = new sf::Texture();
    this->texture->loadFromFile("media/images/whiteTurn.png");
    this->image.setTexture(*this->texture);

    this->font.loadFromFile("media/fonts/AGENCYB.TTF");
    this->text.setFont(this->font);
    this->text.setPosition(x + size_x + 5, y - 6);
    this->text.setString("Turn");
    this->text.setCharacterSize(20U);
  //  this->description.setColor(sf::Color::Black);
}

void turnIndicator::changeTurn(){
    this->turn = !this->turn;
    delete this->texture;
    this->texture = new sf::Texture();
    if(turn){
        this->texture->loadFromFile("media/images/whiteTurn.png");
        this->image.setTexture(*this->texture);
    }
    else{
        this->texture->loadFromFile("media/images/blackTurn.png");
        this->image.setTexture(*this->texture);
    }
}
