#include <SFML/Graphics.hpp>
#include "headers/lobby.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Lobby::Lobby(sf::RenderWindow& window, NetworkHandler& network):
                                        mainWindow(window), //x, y, size x, size y, title, text x, text y
                                        network(network),
                                        game(window, network, 1),
                                        playButton(420, 250, 100, 80, "  Play", ButtonStyle::Dark){
    warningFont.loadFromFile("media/fonts/AGENCYB.TTF");
    warnings.setFont(warningFont);
    warnings.setPosition(390, 360);
    warnings.setString("");
    warnings.setCharacterSize(20U);

    this->backgroundTexture = new sf::Texture();

    this->backgroundTexture->loadFromFile("media/images/bg1.jpg");
    this->background.setTexture(*this->backgroundTexture);
}

void Lobby::draw(){
    mainWindow.clear(sf::Color(0, 150, 255));
    mainWindow.draw(background);
    mainWindow.draw(playButton.image);
    mainWindow.draw(playButton.text);
    mainWindow.draw(warnings);

    //window.clear(sf::Color(0, 0, 0));
    mainWindow.display();
}

void Lobby::run(STATE& state){
    packetID receive;
    while (mainWindow.isOpen() && state == STATE::Lobby){
        sf::Event event;
        while (mainWindow.pollEvent(event)){
            handleEvent(event);
        }
        receive = network.receive();
        switch(receive){
            case packetID::GameRequest:
                network.sendConnect();
            break;
            case packetID::Connect:
                state = STATE::Game;
                warnings.setString("");
            break;
            case packetID::Options:
                game.myColor = 0;
                game.b.InitializeBlack(BOARD_X, BOARD_Y);
            break;
        }

        draw();
    }
    if(state == STATE::Game){
        game.Run(state);
    }
}

void Lobby::handleEvent(const sf::Event& event){
    char letter;
    switch(event.type){
        case sf::Event::Closed:
            network.sendDisconnect();
            mainWindow.close();
        break;
        case sf::Event::MouseButtonPressed:
            int x = event.mouseButton.x;
            int y = event.mouseButton.y;
            if(playButton.clicked(x, y)){
                warnings.setString("Waiting for another player...");
                //waitingForGame = true;
                cout << "Waiting for another player..." << endl;
                network.sendGameRequest();
                //state = STATE::Waiting;
            }
        break;

    }
}

void Lobby::keepConnectionAlive(){

}
