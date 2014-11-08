#include "headers/playerPanel.h"
#include "headers/inviterequest.h"
#include <iostream>

using namespace std;

playerPanel::playerPanel(): viewProfile(100 + 15, 100 + 15, 15, 15, "", "profile", ButtonStyle::NoText),
                                        add(100 + 75, 100 + 75, 15, 15, "", "add", ButtonStyle::NoText),
                                        invite(100 + 45, 100 + 45, 15, 15, "", "sword", ButtonStyle::NoText),
                                        watch(100 + 45, 100 + 45, 15, 15, "", "eye", ButtonStyle::NoText){

    sf::RectangleShape shape(sf::Vector2f(SIZE_X, SIZE_Y));
    shape.setPosition(100, 100);

    this->font.loadFromFile("media/fonts/AGENCYB.TTF");
    this->playerName.setFont(this->font);
    this->playerName.setCharacterSize(15U);
    this->playerName.setPosition(100, 100);
    this->playerName.setString("");
    this->playerName.setColor(sf::Color::Black);

    this->onlineTexture = new sf::Texture();
    this->onlineTexture->loadFromFile("media/images/online.png");

    this->offlineTexture = new sf::Texture();
    this->offlineTexture->loadFromFile("media/images/offline.png");

    this->playingTexture = new sf::Texture();
    this->playingTexture->loadFromFile("media/images/playing.png");

    this->flagTexture = new sf::Texture();
    this->flagTexture->loadFromFile("media/images/flags/brazil.png");
    this->flag.setTexture(*flagTexture);

    this->backgroundTexture = new sf::Texture();
    this->backgroundTexture->loadFromFile("media/images/playerBG.png");
    this->background.setTexture(*this->backgroundTexture);

    this->square = shape;

    sf::FloatRect squareRect(this->square.getPosition().x, this->square.getPosition().y, this->square.getSize().x, this->square.getSize().y);
    this->rectSquare = squareRect;
    this->square.setFillColor(sf::Color::Black);
    this->visible = false;
}

void playerPanel::update(int x, int y, statusID status){
    square.setPosition(x, y);
    background.setPosition(x, y);
    playerName.setPosition(x + 45, y + 22);
    playerName.setString(name);
    this->status.setPosition(x + 5, y + 24);
    this->flag.setPosition(x + 22, y + 18);
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
    add.rectSquare = squareRect2;

    invite.square.setPosition(x + 130, y + 24);
    invite.image.setPosition(x + 130, y + 24);
    sf::FloatRect squareRect1(x + 130, y + 24, invite.square.getSize().x, invite.square.getSize().y);
    invite.rectSquare = squareRect1;

    viewProfile.square.setPosition(x + 130, y + 10);
    viewProfile.image.setPosition(x + 130, y + 10);
    sf::FloatRect squareRect3(x + 130, y + 10, viewProfile.square.getSize().x, viewProfile.square.getSize().y);
    viewProfile.rectSquare = squareRect3;

    watch.square.setPosition(x + 130, y + 25);
    watch.image.setPosition(x + 130, y + 25);
    sf::FloatRect squareRect4(x + 130, y + 25, watch.square.getSize().x, watch.square.getSize().y);
    watch.rectSquare = squareRect4;
}

void playerPanel::handleInput(int x, int y){
    if(visible){
        if(invite.clicked(x, y)){
            cout << name << endl;
            inviteRequest.CreateRequest(name);
        }
    }

}

void playerPanel::draw(sf::RenderWindow& window, statusID status){
    window.draw(square);
    window.draw(background);
    if(status == statusID::playing){
        window.draw(watch.image);
    }
    else{
        window.draw(invite.image);
    }

    //window.draw(add.image);
    //window.draw(viewProfile.image);
    playerName.setString(name);
    window.draw(playerName);
    window.draw(this->status);
    //window.draw(this->flag);

}

void playerPanel::setName(std::string name){
    this->playerName.setString(name);
}
