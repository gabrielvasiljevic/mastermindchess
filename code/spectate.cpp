#include <SFML/Graphics.hpp>
#include "headers/spectate.h"
#include <iostream>
#include <string>
#include <sstream>


using namespace std;


Spectator::Spectator(sf::RenderWindow &window, Game &game, int gametype) :
            mainWindow(window),
            exitButton(865, 650, 33, 33, "", "exit", ButtonStyle::NoText),
            game(game),
            chat(BOARD_X + 64, BOARD_Y + 64, 384, 384, BOARD_X + 64, BOARD_Y + 512, ChatStyle::SpectateChat){

    this->watchingTexture = new sf::Texture();
    this->watchingTexture->loadFromFile("media/images/eyeIcon.png");

    this->watching.setTexture(*this->watchingTexture);
    this->watching.setPosition(830, 455);
}


void Spectator::draw(){
    game.displayELO.setString(to_string(whiteELO));
    game.draw();
    chat.draw(mainWindow);
    mainWindow.draw(watching);
}

void Spectator::run(STATE& state){
    /*Pieces' texture initialization*/
    game.reset(1, 300, 0, 1);
    game.Initialize_Texture(game.b.pieces);
    int i, j, iP, jP, cl = 0;
    bool check;
    string msg;
    packetID receive;
    game.warnings.setString("");
    while (mainWindow.isOpen() && state == STATE::Watching){

        sf::Event event;
        while (mainWindow.pollEvent(event)){
            handleEvent(event, state);
        }
        receive = network.receive();
        switch(receive){
            case packetID::Move:
                network.receiveMove(&i, &j, &iP, &jP, &check);
                if(game.b.pieces[iP][jP].type == KING && j - jP == 2){
                    game.b.pieces[iP][jP].changePiece(game.b.pieces, i, jP+1, iP, j+1);
                }
                else if(game.b.pieces[iP][jP].type == KING && j - jP == -2){
                    game.b.pieces[iP][jP].changePiece(game.b.pieces, i, jP-1, iP, j-2);
                }
                movePiece(i, j, iP, jP);
            break;

            case packetID::Chat:
                cout << "Received chat message." << endl;
                msg = network.receiveChat();
                //if(Mute.checked)
                chat.receiveMessage(msg);
            break;
            case packetID::Name:
                cout << "Received name" << endl;

            break;

            case packetID::GameEnd:

                state = STATE::Lobby;
                //network.sendDisconnect();
                //mainWindow.close();
            break;
        }
        mainWindow.clear(sf::Color(0, 150, 255));
        //window.clear(sf::Color(0, 0, 0));
        draw();
        mainWindow.display();
    }
}



void Spectator::movePiece(int i, int j, int iP, int jP){
    if(game.b.pieces[iP][jP].color == !game.b.pieces[i][j].color){
        game.pieceholder.add(game.b.pieces[i][j].type, game.b.pieces[i][j].color);
    }
    if(game.b.pieces[iP][jP].type == PAWN &&
       game.b.pieces[i][j].type == BLANK){ //en passant
        if(jP == j + 1){
            game.b.pieces[iP][j].type = BLANK;
            game.b.pieces[iP][j].code = "";
            game.b.pieces[iP][j].color = -1;
        }
        else if(jP == j - 1){
            game.b.pieces[iP][j].type = BLANK;
            game.b.pieces[iP][j].code = "";
            game.b.pieces[iP][j].color = -1;
        }
    }
    game.b.pieces[i][j].code = game.b.pieces[iP][jP].code;
    game.b.pieces[i][j].type = game.b.pieces[iP][jP].type;
    game.b.pieces[i][j].color = game.b.pieces[iP][jP].color;
    game.b.pieces[iP][jP].type = BLANK;
    game.b.pieces[iP][jP].code = "";
    game.b.pieces[iP][jP].color = -1;

    if((i == 0 || i == 7) && game.b.pieces[i][j].type == PAWN){
        game.b.pieces[i][j].code = "Q";
        game.b.pieces[i][j].type == QUEEN;
    }
    game.Initialize_Texture(game.b.pieces);
}

void Spectator::handleEvent(const sf::Event& event, STATE& state){
    char input;
    switch(event.type){
        case sf::Event::Closed:
            network.sendDisconnect();
            mainWindow.close();
        break;
        case sf::Event::TextEntered:
            input = static_cast<char>(event.text.unicode);
            chat.handleInput(input);
        break;
        case sf::Event::MouseButtonPressed:

            if(exitButton.clicked(event.mouseButton.x, event.mouseButton.y)){
                state = STATE::Lobby;
                chat.Clear();
            }
        break;
    }
}

void Spectator::updateMatchStatus(string white, string black, int whiteElo, int blackElo, string newBoard[][10], int gameMode){
    if(gameMode == 2)
        game.reset(1, 300, 2, 1);
    game.myName.setString(white);
    game.enemyName.setString(black);
    whiteELO = whiteElo;
    blackELO = blackElo;
    game.displayELO.setString(to_string(whiteELO));
    game.enemyELO.setString(to_string(blackELO));
    int i, j;
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            game.b.pieces[i][j].changeType(newBoard[i][j]);
            game.Initialize_Texture(game.b.pieces);
        }
    }
}

