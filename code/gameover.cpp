#include <SFML/Graphics.hpp>
#include "headers/gameover.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Gameover::Gameover(sf::RenderWindow& window, NetworkHandler& network):
                                        mainWindow(window), //x, y, size x, size y, title, text x, text y
                                        network(network),
                                        backButton(320, 450, 100, 80, "  Back", ButtonStyle::Dark),
                                        saveHistoryButton(420, 450, 70, 80, "Save Match", ButtonStyle::Dark){
    warningFont.loadFromFile("media/fonts/AGENCYB.TTF");
    warnings.setFont(warningFont);
    warnings.setPosition(330, 160);
    warnings.setString("");
    warnings.setCharacterSize(50U);

    this->backgroundTexture = new sf::Texture();

    this->backgroundTexture->loadFromFile("media/images/bg1.jpg");
    this->background.setTexture(*this->backgroundTexture);
}

void Gameover::draw(){
    mainWindow.clear(sf::Color(0, 150, 255));
    mainWindow.draw(background);
    mainWindow.draw(backButton.image);
    mainWindow.draw(backButton.text);
    mainWindow.draw(saveHistoryButton.image);
    mainWindow.draw(saveHistoryButton.text);
    mainWindow.draw(warnings);
    //window.clear(sf::Color(0, 0, 0));
    mainWindow.display();
}

void Gameover::run(STATE& state){
    packetID receive;
    while (mainWindow.isOpen() && state == STATE::GameOver){
        sf::Event event;
        while (mainWindow.pollEvent(event)){
            handleEvent(event, state);
        }
        receive = network.receive();
        switch(receive){
            case packetID::GameRequest:
                network.sendConnect();
            break;
        }
        draw();
    }
}


void Gameover::handleEvent(const sf::Event& event, STATE& state){
    char letter;
    switch(event.type){
        case sf::Event::Closed:
            mainWindow.close();
        break;
        case sf::Event::MouseButtonPressed:
            int x = event.mouseButton.x;
            int y = event.mouseButton.y;
            if(backButton.clicked(x, y)){
                state = STATE::Lobby;
            }
        break;

    }
}

void Gameover::setWinner(int winner){
    winner? warnings.setString("White wins!") : warnings.setString("Black wins!");
}

void Gameover::keepConnectionAlive(){

}

