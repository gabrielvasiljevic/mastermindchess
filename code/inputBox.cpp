#include "headers/inputBox.h"
#include <string>
#include <iostream>

inputBox::inputBox(int x, int y, int size_x, int size_y, std::string desc, int text_x, int text_y, int size) :
                                                            Interface_Element(x, y, size_x, size_y){
    this->font.loadFromFile("media/fonts/AGENCYB.TTF");
    this->text.setFont(this->font);
    this->text.setPosition(text_x, text_y);
    this->text.setString(desc);
    this->text.setCharacterSize(20U);
    selected = false;
    this->inputText.setFont(this->font);
    this->inputText.setPosition(x + 4, y + 3);
    this->inputText.setString("");
    this->inputText.setCharacterSize(20U);
    this->inputText.setColor(sf::Color::Black);
    if(size == 0)
        this->background.setTexture(*Textures::inputBox);
    else if(size == 2)
        this->background.setTexture(*Textures::largeInputBox);
    this->background.setPosition(x, y);
}

void inputBox::select(){
    selected = true;
    this->inputText.setString(inputText.getString() + "|");
}

void inputBox::deselect(){
    std::string newString = inputText.getString();
    if(newString.size() > 0 && selected){
        newString.pop_back();
        selected = false;
    }
    this->inputText.setString(newString);
}

std::string inputBox::getLastLetters(std::string input, int letters){
    int i;
    std::string output = "";

    if(input.size() > letters){
        for(i = input.size() - letters; i < input.size(); i++){
            output += input[i];
        }
        return output;
    }
    else return input;
}
