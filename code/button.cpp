#include "headers/button.h"
#include <string>
#include <iostream>
#include <stdlib.h>

Button::Button(int x, int y, int size_x, int size_y, std::string desc, std::string image, ButtonStyle style) : Interface_Element(x, y, size_x, size_y){
    this->font.loadFromFile("media/fonts/AGENCYB.TTF");
    this->text.setFont(this->font);
    std::string filename = "";
    this->text.setPosition(x + size_x/2 - 25, y + size_y/2 - 15);
    this->text.setString(desc);
    this->text.setCharacterSize(20U);
    this->text.setColor(sf::Color::Black);

    if(style == ButtonStyle::NoText){
        this->text.setString("");
    }
    if(style != ButtonStyle::NoImage){
        filename = "media/images/buttons/" + image + ".png";
    }
    else{
        filename = "media/images/buttons/blank.png";
    }

    this->texture = new sf::Texture();
    this->texture->loadFromFile(filename);
    this->image.setTexture(*this->texture);

}

void Button::changeIcon(std::string imagename){
    delete this->texture;
    this->texture = new sf::Texture();
    this->texture->loadFromFile("media/images/" + imagename);
    this->image.setTexture(*this->texture);
}


