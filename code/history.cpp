#include "headers/history.h"
#include <string>
#include <iostream>


History::History(int x, int y, int size_x, int size_y): scrollBackButton(x + 12, y + 186, 8, 8, "", "bord", ButtonStyle::NoText),
                                                        scrollNextButton(x + 132, y + 186, 8, 8, "", "bord2", ButtonStyle::NoText){
    this->charSize = 23U;
    this->height = 5;
    this->historyLength = 5;
    this->moveNumber = 1;
    this->histNumber = 1;
    this->posNumber = 0;
    this->initialMove = 0;
    this->histFont.loadFromFile("media/fonts/circhand.ttf");

    this->historyText.setFont(this->histFont);
    this->historyText.setColor(sf::Color::Black);
    this->historyText.setCharacterSize(this->charSize);


    this->image.setPosition(x, y);
    this->waterMark.setPosition(x + 48, y + 85);

    this->texture = new sf::Texture();
    this->chatTexture = new sf::Texture();
    this->waterMarkTexture = new sf::Texture();

    this->texture->loadFromFile("media/images/papers/yellowpaper.png");
    this->chatTexture->loadFromFile("media/images/papers/chatpaper.png");
    this->waterMarkTexture->loadFromFile("media/images/watermarks/water5.png");

    this->image.setTexture(*this->texture);
    this->waterMark.setTexture(*this->waterMarkTexture);
    sf::RectangleShape shape(sf::Vector2f(size_x, size_y));
    shape.setPosition(x, y);
    sf::FloatRect squareRect(shape.getPosition().x, shape.getPosition().y, shape.getSize().x, shape.getSize().y);
    this->rectHistBox = squareRect;

    this->histBox = shape;
    this->chatOn = false;
}


void History::draw(sf::RenderWindow & window){
    if(chatOn){
        image.setTexture(*this->chatTexture);
        window.draw(image);
    }
    else{
        image.setTexture(*this->texture);
        window.draw(image);
        window.draw(waterMark);
    }
	float x = histBox.getGlobalBounds().left + 15;
	float y = histBox.getGlobalBounds().top + 30;// + histBox.getGlobalBounds().height - 3*height - 2*charSize;

    if(!chatOn)
        for(std::size_t i = initialMove; i < initialMove + 5; i++){
            if(i < history.size()){
                historyText.setString(history[i]);
                historyText.setPosition(x, y + (i%5)*charSize);//  - i*height - height);
                window.draw(historyText);
            }
        }
    window.draw(scrollNextButton.image);
    window.draw(scrollBackButton.image);
}

void History::scrollBack(){
    if(initialMove - 5 >= 0){
        initialMove -= 5;
    }
}

void History::scrollNext(){
    initialMove = posNumber;
}

void History::handleInput(int x, int y){
    if(scrollBackButton.clicked(x, y)){
        scrollBack();
    }
    if(scrollNextButton.clicked(x,y)){
        scrollNext();
    }
}


void History::reset(int gameType, int gameTime){
    history.clear();
    this->texture          = Textures::selectPaper(gameType);
    this->waterMarkTexture = Textures::selectWaterMark(gameTime);

    this->waterMark.setTexture(*this->waterMarkTexture);
    this->moveNumber = 1;
    this->histNumber = 1;
    this->posNumber = 0;
}

void History::putMove(string Move){
    if(moveNumber%2 == 0){
        history[history.size()-1] += " " + Move;
        histNumber++;
    }
    else{
        history.push_back(to_string(histNumber) + ". " + Move);
    }
    moveNumber++;
    if((moveNumber-1)%5 == 1 && histNumber%5 == 1){
        posNumber = histNumber - 1;
    }
    initialMove = posNumber;
}

