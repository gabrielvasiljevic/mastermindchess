#include "headers/rankPanel.h"
#include <iostream>

using namespace std;

rankPanel::rankPanel() : viewProfile(100 + 15, 100 + 15, 15, 15, "", "profile", ButtonStyle::NoText){

    sf::RectangleShape shape(sf::Vector2f(SIZE_X, SIZE_Y));
    shape.setPosition(100, 100);
    numberOfMatches = 0;
    this->font.loadFromFile("media/fonts/AGENCYB.TTF");
    this->playerName.setFont(this->font);
    this->playerName.setCharacterSize(15U);
    this->playerName.setPosition(100, 100);
    this->playerName.setString("");
    this->playerName.setColor(sf::Color::Black);

    this->playerELO.setFont(this->font);
    this->playerELO.setCharacterSize(15U);
    this->playerELO.setPosition(100, 130);
    this->playerELO.setString("");
    this->playerELO.setColor(sf::Color::Black);

    this->playerRank.setFont(this->font);
    this->playerRank.setCharacterSize(15U);
    this->playerRank.setPosition(100, 100);
    this->playerRank.setString("");
    this->playerRank.setColor(sf::Color::Black);

    this->playerVLD.setFont(this->font);
    this->playerVLD.setCharacterSize(15U);
    this->playerVLD.setPosition(100, 100);
    this->playerVLD.setString("");
    this->playerVLD.setColor(sf::Color::Black);


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
    this->backgroundTexture->loadFromFile("media/images/bluerecord.png");
    this->background.setTexture(*this->backgroundTexture);

    this->square = shape;

    sf::FloatRect squareRect(this->square.getPosition().x, this->square.getPosition().y, this->square.getSize().x, this->square.getSize().y);
    this->rectSquare = squareRect;
    this->square.setFillColor(sf::Color::Black);
    this->visible = false;
}

void rankPanel::update(int x, int y, statusID status){
    square.setPosition(x, y);
    background.setPosition(x, y);

    playerRank.setPosition(x + 5, y + 2);
    playerRank.setString("#"+to_string(pos));

    playerName.setPosition(x + 56 -(playerName.getCharacterSize()*name.size())/8, y + 2);
    playerName.setString(name);

    playerName.setCharacterSize(15U);

    if(playerName.getGlobalBounds().width > 100){
        playerName.setCharacterSize(11U);
    }


    playerVLD.setPosition(x + 5, y + 25);
    playerVLD.setString(vld);

    playerELO.setPosition(x + 96, y + 25);
    playerELO.setString(name);

    prize.setPosition(x + 35, y + 50);
    prize.setTexture(*Textures::selectPrize(elo));

    this->status.setPosition(x + 5, y + 25);
    this->flag.setPosition(x + 22, y + 28);
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


    viewProfile.square.setPosition(x + 85, y + 45);
    viewProfile.image.setPosition(x + 85, y + 45);
    sf::FloatRect squareRect3(x + 85, y + 45, viewProfile.square.getSize().x, viewProfile.square.getSize().y);
    this->rectSquare = squareRect3;

}

void rankPanel::draw(sf::RenderWindow& window, statusID status){
    window.draw(square);
    window.draw(background);


    //window.draw(add.image);
    //window.draw(viewProfile.image);
    playerName.setString(name);
    playerVLD.setString(vld);
    playerELO.setString(to_string(elo));

    window.draw(playerName);
    window.draw(playerELO);
    window.draw(playerRank);
    window.draw(playerVLD);

    if(numberOfMatches >= 10)
        window.draw(prize);
    //window.draw(this->status);
    //window.draw(this->flag);

}

void rankPanel::setName(std::string name){
    this->playerName.setString(name);
}

void rankPanel::setColor(std::string recordColor){
    delete this->backgroundTexture;
    this->backgroundTexture = new sf::Texture();
    this->backgroundTexture->loadFromFile("media/images/" + recordColor + "record.png");
    this->background.setTexture(*this->backgroundTexture);
}

void rankPanel::swap(rankPanel& other){
    std::swap(x, other.x);
    std::swap(y, other.y);
    std::swap(elo, other.elo);
    std::swap(vld, other.vld);
    std::swap(name, other.name);
}




