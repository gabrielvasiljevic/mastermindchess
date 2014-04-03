#include "headers/inputBox.h"
#include <string>
#include <iostream>


inputBox::inputBox(int x, int y, int size_x, int size_y, std::string desc, int text_x, int text_y) : Interface_Element(x, y, size_x, size_y){
    this->font.loadFromFile("media/fonts/AGENCYB.TTF");
    this->text.setFont(this->font);
    this->text.setPosition(text_x, text_y);
    this->text.setString(desc);
    this->text.setCharacterSize(20U);
    this->inputText.setFont(this->font);
    this->inputText.setPosition(x, y);
    this->inputText.setString("");
    this->inputText.setCharacterSize(20U);
    this->inputText.setColor(sf::Color::Black);
}

