#include "headers/button.h"
#include <string>
#include <iostream>
#include <stdlib.h>

Button::Button(int x, int y, int size_x, int size_y, std::string desc, ButtonStyle style) : Interface_Element(x, y, size_x, size_y){
    this->font.loadFromFile("media/fonts/AGENCYB.TTF");
    this->text.setFont(this->font);
    this->text.setPosition(x + size_x/2 - 20, y + size_y/2 - 15);
    this->text.setString(desc);
    this->text.setCharacterSize(20U);
    this->text.setColor(sf::Color::Black);

    std::string filename = "media/images/button" + std::to_string(static_cast<int>(style)) + ".png";
    this->texture = new sf::Texture();
    this->texture->loadFromFile(filename);
    this->image.setTexture(*this->texture);
}


