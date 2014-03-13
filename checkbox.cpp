#include "checkbox.h"
#include <string>
#include <iostream>
Checkbox::Checkbox(int x, int y, int size_x, int size_y, std::string desc) : Interface_Element(x, y, size_x, size_y){
    this->checked = true;
    this->texture = new sf::Texture();
    this->texture->loadFromFile("images/marked.png");
    this->image.setTexture(*this->texture);

    this->font.loadFromFile("fonts/AGENCYB.TTF");
    this->text.setFont(this->font);
    this->text.setPosition(x + size_x + 5, y - 6);
    this->text.setString(desc);
    this->text.setCharacterSize(20U);
  //  this->description.setColor(sf::Color::Black);
}

void Checkbox::action(){
    delete this->texture;
    this->texture = new sf::Texture();
    if(checked){
        this->texture->loadFromFile("images/checkbox.png");
        this->image.setTexture(*this->texture);
    }
    else{
        this->texture->loadFromFile("images/marked.png");
        this->image.setTexture(*this->texture);
    }
    checked = !checked;

}
