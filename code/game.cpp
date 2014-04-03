#include <SFML/Graphics.hpp>
#include "headers/game.h"
#include <iostream>
#include <string>
#include <sstream>


using namespace std;

    sf::Texture pawns;
    sf::Texture bpawns;
    sf::Texture towers;
    sf::Texture btowers;
    sf::Texture knights;
    sf::Texture bknights;
    sf::Texture bishops;
    sf::Texture bbishops;
    sf::Texture queens;
    sf::Texture bqueens;
    sf::Texture kings;
    sf::Texture bkings;
    sf::Texture blanks;
    sf::Texture Tabuleiro;
    sf::Sprite board;

    bool pieceClick = false;

Game::Game(sf::RenderWindow &window, NetworkHandler &mainNetwork) : b(BOARD_X, BOARD_Y, 1),
            Hint(750, 100, 15, 15, "Hint"),
            TurnIndicator(120, 100, 15, 15),
            mainWindow(window),
            network(mainNetwork){
    sf::Font font;
    this->boardTexture = new sf::Texture();
    this->backgroundTexture = new sf::Texture();

    this->boardTexture->loadFromFile("media/images/board55.png");
    this->backgroundTexture->loadFromFile("media/images/background.jpg");

    this->board.setTexture(*this->boardTexture);
    this->background.setTexture(*this->backgroundTexture);

    this->board.setPosition(BOARD_X, BOARD_Y);
    this->turn = 1;
    this->myColor = 1;
    this->moveCount = 0;
    this->check = false;
    this->enemyCheck = false;
    this->checkMate = false;

}

Game::Game(sf::RenderWindow &window, NetworkHandler &mainNetwork, int color) :
            b(BOARD_X, BOARD_Y, color),
            Hint(750, 100, 15, 15, "Hint"),
            TurnIndicator(120, 100, 15, 15),
            mainWindow(window),
            network(mainNetwork){
    sf::Font font;
    this->boardTexture = new sf::Texture();
    this->backgroundTexture = new sf::Texture();

    this->boardTexture->loadFromFile("media/images/board55.png");
    this->backgroundTexture->loadFromFile("media/images/background.jpg");

    this->board.setTexture(*this->boardTexture);
    this->background.setTexture(*this->backgroundTexture);

    this->board.setPosition(BOARD_X, BOARD_Y);
    this->turn = 1;
    this->myColor = color;
    this->moveCount = 0;
    this->check = false;
    this->enemyCheck = false;
    this->checkMate = false;
    //font.loadFromFile("media/fonts/AGENCYB.TTF");
   // this->turnText.setFont(font);
   // this->turnText.setPosition(120 + 5, 100 - 6);
   // this->turnText.setString("Turn");
 //   this->turnText.setCharacterSize(20U);
}

void Game::draw(){
    mainWindow.draw(background);
    mainWindow.draw(board);
    mainWindow.draw(Hint.image);
    mainWindow.draw(TurnIndicator.image);
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            mainWindow.draw(b.pieces[i][j].square ); //Draw the background first
            mainWindow.draw(b.pieces[i][j].image ); //Then the piece itself
            if(b.pieces[i][j].highlighted){
                mainWindow.draw(b.pieces[i][j].border);
            }
        }
    }
    mainWindow.draw(Hint.text);
   mainWindow.draw(TurnIndicator.text);
}

int Game::Run(STATE& state){
    /*Pieces' texture initialization*/
    Initialize_Texture(b.pieces);
    int i, j, iP, jP;
    packetID receive;
    while (mainWindow.isOpen() && state == STATE::Game){
        sf::Event event;
        while (mainWindow.pollEvent(event)){
            handleEvent(event, state);
        }
        receive = network.receive();
        switch(receive){
            case packetID::Move:
                network.receiveMove(&i, &j, &iP, &jP, &check);
                if(b.pieces[iP][jP].type == KING && j - jP == 2){
                    b.pieces[iP][jP].changePiece(b.pieces, i, jP+1, iP, j+1);
                }
                else if(b.pieces[iP][jP].type == KING && j - jP == -2){
                    b.pieces[iP][jP].changePiece(b.pieces, i, jP-1, iP, j-2);
                }
                makeEnemyMove(i, j, iP, jP);
                if(check){
                    check = true;
                    logCheck();
                }
                testCheck.updateAttackBoard(b.pieces);
                TurnIndicator.changeTurn();
            break;
            case packetID::Checkmate:
                //state = STATE::GameOver;
                logCheck();
                cout << history.history << endl;
                cout << "Game over! " << (myColor? "Black wins!" : "White wins!") << endl;
                state = STATE::Lobby;
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
    /*Load board image and texture*/
   // if(!Tabuleiro.loadFromFile("media/images/board.jpg")) return 1;
   // board.setTexture(Tabuleiro);

    draw();
}

void Unhighlight(Piece b[8][8]){
     for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            b[i][j].square.setFillColor(sf::Color::Transparent);
            b[i][j].highlighted = false;
            b[i][j].clicked = false;
        }
    }
}

void Game::Initialize_Texture(Piece pieces[8][8]){

    blanks.loadFromFile("media/images/blank55.png");
    pawns.loadFromFile("media/images/pawn55.png");
    bpawns.loadFromFile("media/images/bpawn55.png");
    towers.loadFromFile("media/images/tower55.png");
    btowers.loadFromFile("media/images/btower55.png");
    knights.loadFromFile("media/images/knight55.png");
    bknights.loadFromFile("media/images/bknight55.png");
    bishops.loadFromFile("media/images/bishop55.png");
    bbishops.loadFromFile("media/images/bbishop55.png");
    queens.loadFromFile("media/images/queen55.png");
    bqueens.loadFromFile("media/images/bqueen55.png");
    kings.loadFromFile("media/images/king55.png");
    bkings.loadFromFile("media/images/bking55.png");

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            pieces[i][j].square.setFillColor(sf::Color::Transparent); //background color, set in the square that defines the position of the piece
            switch (pieces[i][j].type){ //Set the texture of the piece depending of its type and color
                case BLANK:
                    pieces[i][j].image.setTexture(blanks);
                break;
                case PAWN:
                    if(pieces[i][j].color){
                        pieces[i][j].image.setTexture(pawns);
                    }
                    else{
                        pieces[i][j].image.setTexture(bpawns);
                    }
                break;
                case TOWER:
                    if(pieces[i][j].color){
                        pieces[i][j].image.setTexture(towers);
                    }
                    else{
                        pieces[i][j].image.setTexture(btowers);
                    }
                break;
                case BISHOP:
                    if(pieces[i][j].color){
                        pieces[i][j].image.setTexture(bishops);
                    }
                    else{
                        pieces[i][j].image.setTexture(bbishops);
                    }
                break;
                case KNIGHT:
                    if(pieces[i][j].color){
                        pieces[i][j].image.setTexture(knights);
                    }
                    else{
                        pieces[i][j].image.setTexture(bknights);
                    }
                break;
                case QUEEN:
                    if(pieces[i][j].color){
                        pieces[i][j].image.setTexture(queens);
                    }
                    else{
                        pieces[i][j].image.setTexture(bqueens);
                    }
                break;
                case KING:
                    if(pieces[i][j].color){
                        pieces[i][j].image.setTexture(kings);
                    }
                    else{
                        pieces[i][j].image.setTexture(bkings);
                    }
                break;
            }
        }
    }

}

//Takes two cartesian coordinates and convert it to board coordinates.
string coordToCode(int i, int j){
    string code = "";
    j = j + 97;
    i = i + 1;
    char codeJ = j;
    code += static_cast<char>(codeJ);
    char codeI = '0' + i;
    code += static_cast<char>(codeI); // + static_cast<char>(codeI);
    return code;
}

void Game::logMove(int i, int j, int iP, int jP){
    history.currentMove = b.pieces[i][j].code + coordToCode(iP, jP) + "-" + coordToCode(i, j);
}

void Game::logCapture(int i, int j, int iP, int jP){
    history.currentMove = b.pieces[i][j].code + coordToCode(iP, jP) + "-" + "x" + coordToCode(i, j);
}

void Game::logCheck(){
    history.currentMove = history.currentMove + "+";
}

void Game::makeEnemyMove(int i, int j, int iP, int jP){
    b.pieces[i][j].code = b.pieces[iP][jP].code;
    if(b.pieces[i][j].color == !b.pieces[iP][jP].color)
        logCapture(i, j, iP, jP);
    else
        logMove(i, j, iP, jP);
    b.pieces[i][j].hasMoved = true;
    b.pieces[i][j].type = b.pieces[iP][jP].type;
    b.pieces[iP][jP].type = BLANK;
    b.pieces[iP][jP].code = "";
    b.pieces[i][j].color = b.pieces[iP][jP].color;
    b.pieces[iP][jP].color = -1;
    Initialize_Texture(b.pieces);
    turn = !turn;
    enemyCheck = false;
    moveCount++;
}

void Game::handleEvent(const sf::Event& event, STATE& state){
    char letter;
    switch(event.type){
        case sf::Event::Closed:
            network.sendDisconnect();
            mainWindow.close();
        break;
        case sf::Event::TextEntered:
            letter = static_cast<char>(event.text.unicode);
        break;
        case sf::Event::MouseButtonPressed:
            if(HandleInput(event.mouseButton.x, event.mouseButton.y)){
                network.sendMove(this->i, this->j, iPiece, jPiece, enemyCheck);
                TurnIndicator.changeTurn();
                if(checkMate){
                    network.sendCheckMate();
                    //state == STATE::GameOver;
                    cout << history.history << endl;
                    cout << "Game over! " << (myColor? "White wins!" : "Black wins!") << endl;
                    state = STATE::Lobby;
                }
            }
        break;
    }
}

bool Game::HandleInput(int x, int y){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(b.pieces[i][j].rectSquare.contains(x, y)){ //If the click was in a square...
                if(myColor == turn){
                    if(b.pieces[i][j].color == myColor){ //I clicked one of my pieces.
                        if(!pieceClick){ //I have not clicked in one of my pieces yet.
                            pieceClick = true;
                            iPiece = i;
                            jPiece = j;
                            b.pieces[i][j].clicked? b.pieces[i][j].square.setFillColor(sf::Color::Transparent) : //If the piece was already clicked once, turn it back to transparent
                                                    b.pieces[i][j].square.setFillColor(sf::Color::Yellow); //If not, highlight it in yellow
                            b.pieces[i][j].clicked = !b.pieces[i][j].clicked;
                            if(Hint.checked) b.Highlight(b.pieces[i][j].type, i, j);
                        }
                        else if(pieceClick && i == iPiece && j == jPiece){ //Clicking again in the same piece
                            Unhighlight(b.pieces);
                            pieceClick = false;
                        }
                    }//I have already clicked on a piece, and now I am clicking on an enemy's piece.
                    else if(pieceClick && b.pieces[i][j].color == !myColor){
                        if(b.pieces[i][j].capture(b.pieces, i, j, iPiece, jPiece, check)){ //Capture the piece, if possible
                            b.pieces[i][j].hasMoved = true;
                            Initialize_Texture(b.pieces);
                            Unhighlight(b.pieces);
                            pieceClick = false;
                            turn = !turn;
                            moveCount++;
                            logCapture(i, j, iPiece, jPiece);
                            testCheck.updateAttackBoard(b.pieces);
                            if(testCheck.testCheck(b.pieces, myColor)){
                                cout << "Check!" << endl;
                                history.currentMove += "+";
                                if(testCheck.testCheckMate(b.pieces, myColor)){
                                    cout << "Checkmate!" << endl;
                                    history.currentMove += "+";
                                    checkMate = true;
                                }
                                enemyCheck = true;
                            }
                            this->i = i;
                            this->j = j;
                            history.history += history.currentMove + ";";
                            return true;
                        }
                    }//I have already clicked on a piece, and now I am clicking on an empty square.
                    else if(pieceClick && b.pieces[i][j].type == BLANK ){
                        //Execute a movement, if possible
                        if(b.pieces[i][j].movement(b.pieces, i, j, iPiece, jPiece, check)){
                            b.pieces[i][j].hasMoved = true;
                            turn = !turn;
                            moveCount++;
                            logMove(i, j, iPiece, jPiece);
                            testCheck.updateAttackBoard(b.pieces);
                            if(testCheck.testCheck(b.pieces, myColor)){
                                cout << "Check!" << endl;
                                history.currentMove += "+";
                                enemyCheck = true;
                                if(testCheck.testCheckMate(b.pieces, myColor)){
                                    cout << "Checkmate!" << endl;
                                    history.currentMove += "+";
                                }
                            }
                            Initialize_Texture(b.pieces);
                            Unhighlight(b.pieces);
                            pieceClick = false;
                            this->i = i;
                            this->j = j;
                            history.history += history.currentMove + ";";
                            return true;
                        }
                    }
                }
                return false;
            }
        }
    }
    if(Hint.clicked(x, y)){
        Hint.action();
        return false;
    }
}
