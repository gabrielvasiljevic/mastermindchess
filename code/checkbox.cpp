#include "headers/checkbox.h"
#include <string>
#include <iostream>
Checkbox::Checkbox(int x, int y, int size_x, int size_y, std::string desc) : Interface_Element(x, y, size_x, size_y){
    this->checked = true;
    this->texture = new sf::Texture();
    this->texture->loadFromFile("media/images/marked.png");
    this->image.setTexture(*this->texture);

    this->font.loadFromFile("media/fonts/AGENCYB.TTF");
    this->text.setFont(this->font);
    this->text.setPosition(x + 5, y - 6); //+size_x
    this->text.setString(desc);
    this->text.setCharacterSize(20U);
    this->text.setColor(sf::Color::Black);
}

void Checkbox::action(){
    delete this->texture;
    this->texture = new sf::Texture();
    if(checked){
        this->texture->loadFromFile("media/images/checkbox.png");
        this->image.setTexture(*this->texture);
    }
    else{
        this->texture->loadFromFile("media/images/marked.png");
        this->image.setTexture(*this->texture);
    }
    checked = !checked;

}

void Checkbox::unmark(){
    if(checked){
        delete this->texture;
        this->texture = new sf::Texture();
        this->texture->loadFromFile("media/images/checkbox.png");
        this->image.setTexture(*this->texture);
        checked = false;
    }
}

void Checkbox::mark(){
    if(!checked){
        delete this->texture;
        this->texture = new sf::Texture();
        this->texture->loadFromFile("media/images/marked.png");
        this->image.setTexture(*this->texture);
        checked = true;
    }
}

