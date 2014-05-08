#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <fstream>

#include "headers/board.h"
#include "headers/checkbox.h"
#include "headers/game.h"
#include "headers/networkHandler.h"
#include "headers/login.h"
#include "headers/lobby.h"
#include "headers/dataTypes.h"


using namespace std;
using namespace sf;


//220, 100

STATE state = STATE::Login;

string VERSION = "0.1.5";

Packet packet;

TcpSocket server;
//int port = 14193;
//string ip = "127.0.0.1";
string ip;
int enemyID = -1;
int i;
int j;
int optColor = 1;
bool check;
sf::Text temporary;
sf::Font tempfont;
//string username, password;

/*
void Highlight(Piece b[8][8], TYPE t, int i, int j);
void HighlightTower(Piece b[8][8], int i, int j);
void HighlightBishop(Piece b[8][8], int i, int j);
void Unhighlight(Piece b[8][8]);
void Initialize_Texture(Piece b[8][8]);
*/


int main(){
    sf::RenderWindow window(sf::VideoMode(933, 700), "MasterMind Chess", sf::Style::Close);
    sf::Image icon;
    icon.loadFromFile("media/images/Icon.png");
    window.setIcon(256, 256, icon.getPixelsPtr());
    NetworkHandler network;

    tempfont.loadFromFile("media/fonts/AGENCYB.TTF");
    temporary.setFont(tempfont);
    temporary.setPosition(420, 360);
    temporary.setString("Waiting for another player...");
    temporary.setCharacterSize(20U);
    Login login(window, network);
    Lobby lobby(window, network);
    Game game(window, network, 1);
    while (window.isOpen()){
        switch(network.receive()){
            case packetID::Options:
                optColor = 0;
                state = STATE::Game;
                game.myColor = 0;
                game.b.InitializeBlack(BOARD_X, BOARD_Y);
            break;
        }
        sf::Event event;
        if(state == STATE::Login){
            login.run(state);
        }

        if(state == STATE::Lobby){
            lobby.run(state);
        }

        /*if(state == STATE::Game){
            game.Run(state);
        }
        while (window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    //network.sendDisconnect();
                    window.close();
                case sf::Event::MouseButtonPressed: //When the mouse button is clicked, check where it was
                    if(state == STATE::Game){
                    }

                    break;
                } //switch end

        }//event while ends

        /*Draw everything

        window.clear(sf::Color(0, 150, 255));
        //window.clear(sf::Color(0, 0, 0));
        window.draw(temporary);
        window.display();

    }
  /*


    //Main loop

    //game.myColor = myColor;
    while (window.isOpen()){

        network.handleEvents();



        }
        //Handle the events



       /* if(game.moveCount%2 == 0){
            network.sendMoveHistory(game.history.currentMove);
        }
        if(state == STATE::Game || state == STATE::GameOver){
            game.draw();
        }
        else */
    }
    return 0;
}


