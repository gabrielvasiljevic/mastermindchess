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

#define BOARD_X 220 //position of the board
#define BOARD_Y 100

using namespace std;
using namespace sf;

enum class STATE {Login, Lobby, Game, Waiting};


STATE state = STATE::Game;



Packet packet;
TcpSocket server;
//int port = 14193;
//string ip = "127.0.0.1";
int port;
string ip;
int enemyID = -1;
int i;
int j;
int iP;
int jP;
int myColor = 1;
string username, password;


void Highlight(Piece b[8][8], TYPE t, int i, int j);
void HighlightTower(Piece b[8][8], int i, int j);
void HighlightBishop(Piece b[8][8], int i, int j);
void Unhighlight(Piece b[8][8]);
void Initialize_Texture(Piece b[8][8]);



int main(){
    ifstream config {"config.dat"};
    if (config.is_open()){
        getline(config, ip, ';');
        config >> port;
    }

    NetworkHandler network;
    network.connect(port);
    bool response = false, Color = false;
    string answer;
    packetID receive;
    cout << "Input your username: " << endl;
    getline(cin, username);
    cout << "Input your password: " << endl;
    getline(cin, password);
    network.sendLogin(username, password);
    cout << "Please wait..." << endl;
    do{
        receive = network.receive();
    }while(receive == packetID::None);

    switch(receive){
        case packetID::LoginResponse:
            if(network.receiveLoginResponse()){
                cout << "Login successful!" << endl;
            }
            else cout << "Incorrect login..." << endl;
        break;
    }

    cout << "Waiting for another player..." << endl;
    network.sendGameRequest();
    do{
        receive = network.receive();
        if(receive == packetID::Options) cout << "options!!" << endl;
        switch(receive){
            case packetID::GameRequest:
                network.sendConnect();
            break;
            case packetID::Options:
                myColor = 0;
                Color = true;
                cout << "Changed color!" << endl;
            break;
            case packetID::Connect:
                response = true;
            break;
        }
    }while(!response && !Color);

    //window creation and icon setup
    sf::RenderWindow window(sf::VideoMode(933, 700), "MasterMind Chess", sf::Style::Close);
    sf::Image icon;
    icon.loadFromFile("media/images/Icon.png");
    window.setIcon(256, 256, icon.getPixelsPtr());
    Game game(window);
    /*Main loop*/
    if(state == STATE::Game){
        game.Run();
    }
    game.myColor = myColor;
    while (window.isOpen()){
        sf::Event event;
        network.handleEvents();
        switch(network.receive()){
            case packetID::Move:
                network.receiveMove(&i, &j, &iP, &jP);
                game.b.pieces[i][j].type = game.b.pieces[iP][jP].type;
                game.b.pieces[iP][jP].type = BLANK;
                game.b.pieces[i][j].color = game.b.pieces[iP][jP].color;
                game.b.pieces[iP][jP].color = -1;
                //game.b.pieces[i][j].movement(game.b.pieces, i, j, iP, jP);
                game.Initialize_Texture(game.b.pieces);
                game.turn = !game.turn;
            break;
            case packetID::GameEnd:
                network.sendDisconnect();
                window.close();
            break;

        }
        /*Handle the events*/
        while (window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    network.sendDisconnect();
                    window.close();
                case sf::Event::MouseButtonPressed: //When the mouse button is clicked, check where it was
                    if(game.HandleInput(event.mouseButton.x, event.mouseButton.y)){
                        network.sendMove(game.i, game.j, game.iPiece, game.jPiece);
                    }
                    break;
                } //switch end

        }//event while ends
        /*Draw everything*/

        window.clear(sf::Color(0, 150, 255));

        if(state == STATE::Game){
            game.draw();
        }
        window.display();
    }

    return 0;
}


