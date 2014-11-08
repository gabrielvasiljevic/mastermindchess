#include "headers/matchPanel.h"
#include <iostream>

using namespace std;

matchPanel::matchPanel(int x, int y) : Interface_Element(x, y, SIZE_X, SIZE_Y),
                            watch(100 + 45, 100 + 45, 15, 15, "", "eye", ButtonStyle::NoText){

    this->x = x;
    this->y = y;
    sf::RectangleShape shape(sf::Vector2f(SIZE_X, SIZE_Y));
    shape.setPosition(x, y);

    this->font.loadFromFile("media/fonts/AGENCYB.TTF");

    this->whiteName.setFont(this->font);
    this->whiteName.setCharacterSize(15U);
    this->whiteName.setPosition(x + 112, y + 8);
    this->whiteName.setString("");
    this->whiteName.setColor(sf::Color::Black);

    this->X.setFont(this->font);
    this->X.setCharacterSize(15U);
    this->X.setPosition(x + 112, y + 24);
    this->X.setString("X");
    this->X.setColor(sf::Color::Black);

    this->blackName.setFont(this->font);
    this->blackName.setCharacterSize(15U);
    this->blackName.setPosition(x + 112, y + 38);
    this->blackName.setString("");
    this->blackName.setColor(sf::Color::Black);




    this->backgroundTexture = new sf::Texture();
    this->backgroundTexture->loadFromFile("media/images/yellowmatch.png");
    this->background.setTexture(*this->backgroundTexture);
    this->background.setPosition(x, y);

    this->closedEyeTexture = new sf::Texture();
    this->closedEyeTexture->loadFromFile("media/images/closedEye.png");
    this->closedEye.setTexture(*this->closedEyeTexture);
    this->closedEye.setPosition(x + 192, y + 24);

    this->square = shape;

    sf::FloatRect squareRect(this->square.getPosition().x, this->square.getPosition().y, this->square.getSize().x, this->square.getSize().y);
    this->rectSquare = squareRect;
    this->square.setFillColor(sf::Color::Transparent);
    this->visible = false;
    this->ranked = false;

    watch.square.setPosition(x + 192, y + 24);
    watch.image.setPosition(x + 192, y + 24);
    sf::FloatRect squareRect2(x + 192, y + 24, watch.square.getSize().x, watch.square.getSize().y);
    watch.rectSquare = squareRect2;

}

void matchPanel::update(int status){
    if(ranked)
        this->backgroundTexture = Textures::selectMatchBG(gameType);
    else
        this->backgroundTexture = Textures::whiteMatch;

    this->background.setTexture(*this->backgroundTexture);

    whiteName.setString("(#0) " + whiteNick );
    blackName.setString("(#0) " + blackNick);

    whiteName.setPosition( x + 112 - whiteName.getGlobalBounds().width/2, y + 8);
    blackName.setPosition( x + 112 - blackName.getGlobalBounds().width/2, y + 38);
    if(status)
        this->visible = true;
    else
        this->visible = false;
}

void matchPanel::updateBG(int gameType){
    this->backgroundTexture = Textures::selectMatchBG(gameType);
    this->background.setTexture(*this->backgroundTexture);
}

void matchPanel::draw(sf::RenderWindow& window){
    if(visible){
        window.draw(square);
        window.draw(background);
        //whiteName.setString("( "+ to_string(id) + " ) " + whiteNick + " X " + blackNick);

        window.draw(whiteName);
        window.draw(X);
        window.draw(blackName);
        if(isPublic)
            window.draw(watch.image);
        else
            window.draw(closedEye);
    }

}


bool matchPanel::handleInput(int x, int y){
    if(rectSquare.contains(x, y) && visible) return true;
    return false;
}


