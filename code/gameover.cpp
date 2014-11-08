#include <SFML/Graphics.hpp>
#include "headers/gameover.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Gameover::Gameover(sf::RenderWindow& window):
                                        mainWindow(window), //x, y, size x, size y, title, text x, text y
                                        backButton(794, 600, 100, 80, "    OK", "button0", ButtonStyle::TextAndImage),
                                        saveHistoryButton(420, 450, 70, 80, "Save Match", "button0", ButtonStyle::TextAndImage){
    warningFont.loadFromFile("media/fonts/AGENCYB.TTF");
    warnings.setFont(warningFont);
    warnings.setPosition(400, 160);
    warnings.setString("");
    warnings.setCharacterSize(50U);

    eloDiff.setFont(warningFont);
    eloDiff.setPosition(400, 260);
    eloDiff.setString("");
    eloDiff.setCharacterSize(30U);

    matchDuration.setFont(warningFont);
    matchDuration.setPosition(400, 300);
    matchDuration.setString("");
    matchDuration.setCharacterSize(30U);
    matchDuration.setColor(sf::Color::White);

    this->backgroundTexture = new sf::Texture();

    this->backgroundTexture->loadFromFile("media/images/endgame.png");
    this->background.setTexture(*this->backgroundTexture);
}

void Gameover::draw(){
    mainWindow.clear(sf::Color(0, 150, 255));
    mainWindow.draw(background);
    mainWindow.draw(backButton.image);
    mainWindow.draw(backButton.text);
    //mainWindow.draw(saveHistoryButton.image);
    //mainWindow.draw(saveHistoryButton.text);
    mainWindow.draw(warnings);
    mainWindow.draw(eloDiff);
    mainWindow.draw(matchDuration);
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
    if(winner){
        warnings.setString("White wins!");
        warnings.setColor(sf::Color::White);
    }
    else{
        warnings.setString("Black wins!");
        warnings.setColor(sf::Color::Black);
    }
}

void Gameover::setEloDifferente(int myElo, int enemyElo, int result){
    int newElo = calculateELO(myElo, enemyElo, result) - myElo;
    if(newElo > 0){
        eloDiff.setColor(sf::Color(0, 230, 0));
        eloDiff.setString("Elo: " + to_string(myElo + newElo) + " (+" + to_string(newElo) + ")");
    }
    else if(newElo < 0){
        eloDiff.setColor(sf::Color(230, 0, 0));
        eloDiff.setString("Elo: " + to_string(myElo + newElo)+ " (" + to_string(newElo) + ")");
    }

}

void Gameover::setMatchDuration(int gameTime, int myTime, int enemyTime){
    int usedTime = (gameTime - myTime) + (gameTime - enemyTime);

    matchDuration.setString("Duration: " + toClock(usedTime));
}

int Gameover::calculateELO(int Ra, int Rb, double Sa){ //Elo from player 1 and player 2, and result of the match
    int K = 15;
    double Ea = 1/(1 + pow(10,  ( (Rb - Ra)/400 ) ));
    cout << "Elo from player: " << Ra << endl;
    cout << "New Elo: " << (Ra + (int)(K*(Sa - Ea))) << endl;
    return (Ra + (int)(K*(Sa - Ea)));
}

void Gameover::keepConnectionAlive(){

}
