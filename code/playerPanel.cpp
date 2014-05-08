#include "headers/playerPanel.h"
#include <iostream>

using namespace std;

playerPanel::playerPanel() : viewProfile(100 + 15, 100 + 15, 15, 15, "", ButtonStyle::smallProfile),
                             add(100 + 75, 100 + 75, 15, 15, "", ButtonStyle::smallAdd),
                             invite(100 + 45, 100 + 45, 15, 15, "", ButtonStyle::smallInvite),
                             watch(100 + 45, 100 + 45, 15, 15, "", ButtonStyle::smallWatch){

    sf::RectangleShape shape(sf::Vector2f(SIZE_X, SIZE_Y));
    shape.setPosition(100, 100);

    this->font.loadFromFile("media/fonts/AGENCYB.TTF");
    this->playerName.setFont(this->font);
    this->playerName.setCharacterSize(15U);
    this->playerName.setPosition(100, 100);
    this->playerName.setString("");
    this->playerName.setColor(sf::Color::White);

    this->onlineTexture = new sf::Texture();
    this->onlineTexture->loadFromFile("media/images/online.png");
    this->offlineTexture = new sf::Texture();
    this->offlineTexture->loadFromFile("media/images/offline.png");
    this->playingTexture = new sf::Texture();
    this->playingTexture->loadFromFile("media/images/playing.png");
    //this->backgroundTexture = new sf::Texture();
  //  this->backgroundTexture->loadFromFile("media/images/button0.png");
   // this->background.setTexture(*this->backgroundTexture);
    this->square = shape;

    sf::FloatRect squareRect(this->square.getPosition().x, this->square.getPosition().y, this->square.getSize().x, this->square.getSize().y);
    this->rectSquare = squareRect;
    this->square.setFillColor(sf::Color::Black);
    this->visible = false;
}

void playerPanel::update(int x, int y, statusID status){
    square.setPosition(x, y);
    playerName.setPosition(x + 25, y + 5);
    playerName.setString(name);
    this->status.setPosition(x + 5, y + 5);
    this->x = x;
    this->y = y;

    if(status == statusID::offline){
        this->status.setTexture(*this->offlineTexture);
    }
    else if(status == statusID::online){
        this->status.setTexture(*this->onlineTexture);
    }
    else{
        this->status.setTexture(*this->playingTexture);
    }

    add.square.setPosition(x + 75, y + 30);
    add.image.setPosition(x + 75, y + 30);
    sf::FloatRect squareRect2(x + 75, y + 30, add.square.getSize().x, add.square.getSize().y);
    this->rectSquare = squareRect2;

    invite.square.setPosition(x + 45, y + 30);
    invite.image.setPosition(x + 45, y + 30);
    sf::FloatRect squareRect1(x + 45, y + 30, invite.square.getSize().x, invite.square.getSize().y);
    this->rectSquare = squareRect1;

    viewProfile.square.setPosition(x + 15, y + 30);
    viewProfile.image.setPosition(x + 15, y + 30);
    sf::FloatRect squareRect3(x + 15, y + 30, viewProfile.square.getSize().x, viewProfile.square.getSize().y);
    this->rectSquare = squareRect3;

    watch.square.setPosition(x + 45, y + 30);
    watch.image.setPosition(x + 45, y + 30);
    sf::FloatRect squareRect4(x + 45, y + 30, watch.square.getSize().x, watch.square.getSize().y);
    this->rectSquare = squareRect4;
}

void playerPanel::draw(sf::RenderWindow& window, statusID status){
    window.draw(square);
    //window.draw(background);
    if(status == statusID::playing){
        window.draw(watch.image);
    }
    else{
        window.draw(invite.image);
    }

    window.draw(add.image);
    window.draw(viewProfile.image);
    playerName.setString(name);
    window.draw(playerName);
    window.draw(this->status);

}

void playerPanel::setName(std::string name){
    this->playerName.setString(name);
}
