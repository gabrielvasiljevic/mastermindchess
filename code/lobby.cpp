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
                                        capagame(window, network, 1),
                                        playButton(420, 250, 100, 80, "  Play", ButtonStyle::Dark),
                                        playCapaButton(220, 250, 100, 80, "Play Capa", ButtonStyle::Dark),
                                        play960Button(620, 250, 100, 80, "Play 960", ButtonStyle::Dark),
                                        PlayerListContainer(5, 100, 170, 600){
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
    mainWindow.draw(playCapaButton.image);
    mainWindow.draw(playCapaButton.text);
    mainWindow.draw(play960Button.image);
    mainWindow.draw(play960Button.text);
    mainWindow.draw(warnings);

    PlayerListContainer.draw(mainWindow);
    //window.clear(sf::Color(0, 0, 0));
    mainWindow.display();
}

void Lobby::run(STATE& state){
    packetID receive;
    while (mainWindow.isOpen() && state == STATE::Lobby){
        sf::Event event;
        while (mainWindow.pollEvent(event)){
            handleEvent(event, state);
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

            case packetID::CapaConnect:
                state = STATE::CapaGame;
                warnings.setString("");
            break;
            case packetID::CapaOptions:
                capagame.myColor = 0;
                capagame.b.InitializeBlack(CBOARD_X, CBOARD_Y);
            break;

            case packetID::Options:
                game.myColor = 0;
                game.b.InitializeBlack(BOARD_X, BOARD_Y);
            break;

            case packetID::PlayerList:
                PlayerListContainer.receiveList(network.receivePlayerList());
            break;
        }

        draw();
    }
    if(state == STATE::Game){
        game.Run(state);
    }
    if(state == STATE::CapaGame){
        capagame.Run(state);
    }
}

void Lobby::handleEvent(const sf::Event& event, STATE& state){
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
                cout << "Waiting for another player..." << endl;
                network.sendGameRequest();
            }
            if(playCapaButton.clicked(x, y)){
                warnings.setString("Waiting for another player...");
                cout << "Waiting for another player..." << endl;
                network.sendCapaGameRequest();
                //state = STATE::CapaGame;
            }
            PlayerListContainer.handleInput(x,y);
        break;

    }
}

void Lobby::keepConnectionAlive(){

}
