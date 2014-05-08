#include <SFML/Graphics.hpp>
#include "headers/capablanca.h"
#include <iostream>
#include <string>
#include <sstream>


using namespace std;

    sf::Texture capapawns;
    sf::Texture capabpawns;
    sf::Texture capatowers;
    sf::Texture capabtowers;
    sf::Texture capaknights;
    sf::Texture capabknights;
    sf::Texture capabishops;
    sf::Texture capabbishops;
    sf::Texture capaqueens;
    sf::Texture capabqueens;
    sf::Texture archbishops;
    sf::Texture barchbishops;
    sf::Texture chancelers;
    sf::Texture bchancelers;
    sf::Texture capakings;
    sf::Texture capabkings;
    sf::Texture capablanks;
    sf::Texture capaTabuleiro;
    sf::Sprite capaboard;

    bool pieceCapaClick = false;

string toCapaClock(double time){
    string clock = "";
    clock = clock + ((time/60 < 10) ? "0" : "") + to_string(static_cast<int>(time/60)) + ":";
    time = static_cast<int>(time)%60;
    clock += ((time < 10) ? "0" : "") + to_string(static_cast<int>(time));
    return clock;
}

Capablanca::Capablanca(sf::RenderWindow &window, NetworkHandler &mainNetwork) : b(CBOARD_X, CBOARD_Y, 1),
            Hint(750, 100, 15, 15, "Hint"),
            TurnIndicator(120, 100, 15, 15),
            chat(CBOARD_X, CBOARD_Y*(55*8) + 5, CBOARD_X, CBOARD_Y*55, CBOARD_X, CBOARD_Y*(55*8), ChatStyle::GameChat),
            gameover(window, mainNetwork),
            mainWindow(window),
            network(mainNetwork){
    sf::Font font;
    this->boardTexture = new sf::Texture();
    this->backgroundTexture = new sf::Texture();

    this->boardTexture->loadFromFile("media/images/capaboard55.png");
    this->backgroundTexture->loadFromFile("media/images/background.jpg");

    this->board.setTexture(*this->boardTexture);
    this->background.setTexture(*this->backgroundTexture);

    this->board.setPosition(CBOARD_X, CBOARD_Y);
    this->turn = 1;
    this->myColor = 1;
    this->moveCount = 0;
    this->check = false;
    this->enemyCheck = false;
    this->checkMate = false;

    this->warnings.setFont(font);
    this->warnings.setCharacterSize(20U);
    this->warnings.setColor(sf::Color::Red);
    this->warnings.setPosition(750, 600);
    this->warnings.setString("Check!");

    this->myClockText.setFont(font);
    this->myClockText.setCharacterSize(20U);
    this->myClockText.setColor(sf::Color::White);
    this->myClockText.setPosition(750, 400);

    this->enemyClockText.setFont(font);
    this->enemyClockText.setCharacterSize(20U);
    this->enemyClockText.setColor(sf::Color::White);
    this->enemyClockText.setPosition(750, 200);



    this->myTime = 300;
    this->enemyTime = 300;

}

Capablanca::Capablanca(sf::RenderWindow &window, NetworkHandler &mainNetwork, int color) :
            b(CBOARD_X, CBOARD_Y, color),
            Hint(750, 100, 15, 15, "Hint"),
            TurnIndicator(120, 100, 15, 15),
            mainWindow(window),
            gameover(window, mainNetwork), //int x, int y, int size_x, int size_y, int input_x, int input_y, ChatStyle style
            chat(CBOARD_X, CBOARD_Y+(55*8) + 40, 55*8, 55*2, CBOARD_X, CBOARD_Y+(55*8) + 15 + 55*2, ChatStyle::GameChat),
            network(mainNetwork){
    font.loadFromFile("media/fonts/AGENCYB.TTF");
    this->boardTexture = new sf::Texture();
    this->backgroundTexture = new sf::Texture();

    this->boardTexture->loadFromFile("media/images/capaboard55.png");
    this->backgroundTexture->loadFromFile("media/images/bg1.jpg");

    this->board.setTexture(*this->boardTexture);
    this->background.setTexture(*this->backgroundTexture);

    this->board.setPosition(CBOARD_X, CBOARD_Y);
    this->turn = 1;
    this->myColor = color;
    this->moveCount = 0;
    this->check = false;
    this->enemyCheck = false;
    this->checkMate = false;

    this->warnings.setFont(font);
    this->warnings.setCharacterSize(20U);
    this->warnings.setColor(sf::Color::Red);
    this->warnings.setPosition(750, 600);
    this->warnings.setString("Check!");

    this->myClockText.setFont(font);
    this->myClockText.setCharacterSize(20U);
    this->myClockText.setColor(sf::Color::White);
    this->myClockText.setPosition(750, 400);

    this->enemyClockText.setFont(font);
    this->enemyClockText.setCharacterSize(20U);
    this->enemyClockText.setColor(sf::Color::White);
    this->enemyClockText.setPosition(750, 200);

    this->myTime = 300;
    this->enemyTime = 300;

}

void Capablanca::draw(){
    mainWindow.draw(background);
    mainWindow.draw(board);
    mainWindow.draw(Hint.image);
    mainWindow.draw(TurnIndicator.image);
    mainWindow.draw(myClockText);
    mainWindow.draw(enemyClockText);
    if(check)
    mainWindow.draw(warnings);
    for(i = 0; i < 8; i++){
        for(j = 0; j < 10; j++){
            mainWindow.draw(b.pieces[i][j].square ); //Draw the background first
            mainWindow.draw(b.pieces[i][j].image ); //Then the piece itself
            if(b.pieces[i][j].highlighted){
                mainWindow.draw(b.pieces[i][j].border);
            }
        }
    }
    mainWindow.draw(Hint.text);
   mainWindow.draw(TurnIndicator.text);
   chat.draw(mainWindow);
}

int Capablanca::Run(STATE& state){
    /*Pieces' texture initialization*/
    Initialize_Texture(b.pieces);
    int i, j, iP, jP;
    string msg;
    packetID receive;

    while (mainWindow.isOpen() && state == STATE::CapaGame){
        if(turn == myColor){
            if(myClock.getElapsedTime().asSeconds() > 1){
                myTime--;
                myClock.restart();
            }
        }
        else{
            if(myClock.getElapsedTime().asSeconds() > 1){
                enemyTime--;
                myClock.restart();
            }
        }

        if(myTime == 0){
            network.sendMyTimeout();
            gameover.setWinner(!myColor);
            state = STATE::GameOver;
        }
        else if(enemyTime == 0){
            network.sendEnemyTimeout();
            gameover.setWinner(myColor);
            state = STATE::GameOver;
        }

        if(enemyTime <= 20) enemyClockText.setColor(sf::Color::Red);
        if(myTime <= 20) myClockText.setColor(sf::Color::Red);

        enemyClockText.setString(toCapaClock(enemyTime));
        myClockText.setString(toCapaClock(myTime));

        sf::Event event;
        while (mainWindow.pollEvent(event)){
            handleEvent(event, state);
        }
        receive = network.receive();
        switch(receive){
            case packetID::Move:
                network.receiveMove(&i, &j, &iP, &jP, &check);
                if(b.pieces[iP][jP].type == CAPAKING && j - jP == 3){
                    b.pieces[iP][jP].changePiece(b.pieces, i, jP+2, iP, j+1);
                }
                else if(b.pieces[iP][jP].type == CAPAKING && j - jP == -3){
                    b.pieces[iP][jP].changePiece(b.pieces, i, jP-2, iP, j-2);
                }
                makeEnemyMove(i, j, iP, jP);
                if(check){
                    check = true;
                    warnings.setString("Check!");
                    logCheck();
                }
                testCheck.updateAttackBoard(b.pieces);
                TurnIndicator.changeTurn();
                enemyClock.restart();
            break;

            case packetID::MoveLog:
                network.receiveMoveLog(history.history);
            break;

            case packetID::Checkmate:
                logCheck();
                cout << history.history << endl;
                cout << "Game over! " << (myColor? "Black wins!" : "White wins!") << endl;
                gameover.setWinner(!myColor);
                state = STATE::GameOver;
            break;
            case packetID::Chat:
                msg = network.receiveChat();
                chat.receiveMessage(msg);
            break;
            case packetID::GameEnd:

                state = STATE::Lobby;
                //network.sendDisconnect();
                //mainWindow.close();
            break;
            case packetID::GameEndTimeOut:
                gameover.setWinner(!myColor);
                state = STATE::Lobby;
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

    if(state == STATE::GameOver){
        chat.history.clear();
        gameover.run(state);
    }
}

void Unhighlight(capapiece b[8][10]){
     for(int i = 0; i < 8; i++){
        for(int j = 0; j < 10; j++){
            b[i][j].square.setFillColor(sf::Color::Transparent);
            b[i][j].highlighted = false;
            b[i][j].clicked = false;
        }
    }
}

void Capablanca::Initialize_Texture(capapiece pieces[8][10]){

    capablanks.loadFromFile("media/images/blank55.png");
    capapawns.loadFromFile("media/images/pawn55.png");
    capabpawns.loadFromFile("media/images/bpawn55.png");
    capatowers.loadFromFile("media/images/tower55.png");
    capabtowers.loadFromFile("media/images/btower55.png");
    capaknights.loadFromFile("media/images/knight55.png");
    capabknights.loadFromFile("media/images/bknight55.png");
    capabishops.loadFromFile("media/images/bishop55.png");
    capabbishops.loadFromFile("media/images/bbishop55.png");
    capaqueens.loadFromFile("media/images/queen55.png");
    capabqueens.loadFromFile("media/images/bqueen55.png");
    archbishops.loadFromFile("media/images/archbishop55.png");
    barchbishops.loadFromFile("media/images/barchbishop55.png");
    chancelers.loadFromFile("media/images/chancellor55.png");
    bchancelers.loadFromFile("media/images/bchancellor55.png");
    capakings.loadFromFile("media/images/king55.png");
    capabkings.loadFromFile("media/images/bking55.png");

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 10; j++){
            pieces[i][j].square.setFillColor(sf::Color::Transparent); //background color, set in the square that defines the position of the piece
            switch (pieces[i][j].type){ //Set the texture of the piece depending of its type and color
                case CAPABLANK:
                    pieces[i][j].image.setTexture(capablanks);
                break;
                case CAPAPAWN:
                    if(pieces[i][j].color){
                        pieces[i][j].image.setTexture(capapawns);
                    }
                    else{
                        pieces[i][j].image.setTexture(capabpawns);
                    }
                break;
                case CAPATOWER:
                    if(pieces[i][j].color){
                        pieces[i][j].image.setTexture(capatowers);
                    }
                    else{
                        pieces[i][j].image.setTexture(capabtowers);
                    }
                break;
                case CAPABISHOP:
                    if(pieces[i][j].color){
                        pieces[i][j].image.setTexture(capabishops);
                    }
                    else{
                        pieces[i][j].image.setTexture(capabbishops);
                    }
                break;
                case CAPAKNIGHT:
                    if(pieces[i][j].color){
                        pieces[i][j].image.setTexture(capaknights);
                    }
                    else{
                        pieces[i][j].image.setTexture(capabknights);
                    }
                break;
                case CAPAQUEEN:
                    if(pieces[i][j].color){
                        pieces[i][j].image.setTexture(capaqueens);
                    }
                    else{
                        pieces[i][j].image.setTexture(capabqueens);
                    }
                break;
                case ARCHBISHOP:
                    if(pieces[i][j].color){
                        pieces[i][j].image.setTexture(archbishops);
                    }
                    else{
                        pieces[i][j].image.setTexture(barchbishops);
                    }
                break;
                case CHANCELER:
                    if(pieces[i][j].color){
                        pieces[i][j].image.setTexture(chancelers);
                    }
                    else{
                        pieces[i][j].image.setTexture(bchancelers);
                    }
                break;
                case CAPAKING:
                    if(pieces[i][j].color){
                        pieces[i][j].image.setTexture(capakings);
                    }
                    else{
                        pieces[i][j].image.setTexture(capabkings);
                    }
                break;
            }
        }
    }

}

//Takes two cartesian coordinates and convert it to board coordinates.
string coordToCapaCode(int i, int j){
    string code = "";
    j = j + 97;
    i = i + 1;
    char codeJ = j;
    code += static_cast<char>(codeJ);
    char codeI = '0' + i;
    code += static_cast<char>(codeI); // + static_cast<char>(codeI);
    return code;
}

void Capablanca::logMove(int i, int j, int iP, int jP){
    history.currentMove = b.pieces[i][j].code + coordToCapaCode(iP, jP) + "-" + coordToCapaCode(i, j);
}

void Capablanca::logCapture(int i, int j, int iP, int jP){
    history.currentMove = b.pieces[i][j].code + coordToCapaCode(iP, jP) + "-" + "x" + coordToCapaCode(i, j);
}

void Capablanca::logCheck(){
    history.currentMove = history.currentMove + "+";
}

void Capablanca::makeEnemyMove(int i, int j, int iP, int jP){

    if(b.pieces[i][j].color == !b.pieces[iP][jP].color)
        logCapture(i, j, iP, jP);
    else
        logMove(i, j, iP, jP);

    if(b.pieces[iP][jP].type == CAPAPAWN &&
       b.pieces[i][j].type == CAPABLANK){ //en passant
        if(jP == j + 1){
            b.pieces[iP][j].type = CAPABLANK;
            b.pieces[iP][j].code = "";
            b.pieces[iP][j].color = -1;
        }
        else if(jP == j - 1){
            b.pieces[iP][j].type = CAPABLANK;
            b.pieces[iP][j].code = "";
            b.pieces[iP][j].color = -1;
        }

    }
    b.pieces[i][j].hasMoved = true;
    b.pieces[i][j].moves++;
    b.pieces[i][j].code = b.pieces[iP][jP].code;
    b.pieces[i][j].type = b.pieces[iP][jP].type;
    b.pieces[i][j].color = b.pieces[iP][jP].color;
    b.pieces[iP][jP].type = CAPABLANK;
    b.pieces[iP][jP].code = "";
    b.pieces[iP][jP].color = -1;
    Initialize_Texture(b.pieces);
    turn = !turn;
    enemyCheck = false;
    moveCount++;
}

void Capablanca::handleEvent(const sf::Event& event, STATE& state){
    char input;
    switch(event.type){
        case sf::Event::Closed:
            network.sendDisconnect();
            mainWindow.close();
        break;
        case sf::Event::TextEntered:
            input = static_cast<char>(event.text.unicode);
            chat.handleInput(network, input);
        break;
        case sf::Event::MouseButtonPressed:
            if(HandleInput(event.mouseButton.x, event.mouseButton.y)){
                network.sendMove(this->i, this->j, iPiece, jPiece, enemyCheck);
                network.sendMoveLog(history.currentMove + ";");
                TurnIndicator.changeTurn();
                cout << history.history << endl;
                if(checkMate){
                    network.sendCheckMate();
                    gameover.setWinner(myColor);
                    //state == STATE::CapablancaOver;
                    cout << "Capablanca over! " << (myColor? "White wins!" : "Black wins!") << endl;
                    state = STATE::GameOver;
                }
                myClock.restart();
            }
            else if(chat.rectChatBox.contains(event.mouseButton.x, event.mouseButton.y)){
                chat.active = true;
            }
        break;
    }
}

bool Capablanca::HandleInput(int x, int y){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 10; j++){
            if(b.pieces[i][j].rectSquare.contains(x, y)){ //If the click was in a square...
                if(myColor == turn){
                    if(b.pieces[i][j].color == myColor){ //I clicked one of my pieces.
                        if(!pieceCapaClick){ //I have not clicked in one of my pieces yet.
                            pieceCapaClick = true;
                            iPiece = i;
                            jPiece = j;
                            b.pieces[i][j].clicked? b.pieces[i][j].square.setFillColor(sf::Color::Transparent) : //If the piece was already clicked once, turn it back to transparent
                                                    b.pieces[i][j].square.setFillColor(sf::Color::Yellow); //If not, highlight it in yellow
                            b.pieces[i][j].clicked = !b.pieces[i][j].clicked;
                            if(Hint.checked) b.Highlight(b.pieces[i][j].type, i, j);
                        }
                        else if(pieceCapaClick && i == iPiece && j == jPiece){ //Clicking again in the same piece
                            Unhighlight(b.pieces);
                            pieceCapaClick = false;
                        }
                    }//I have already clicked on a piece, and now I am clicking on an enemy's piece.
                    else if(pieceCapaClick && b.pieces[i][j].color == !myColor){
                        if(b.pieces[i][j].capture(b.pieces, i, j, iPiece, jPiece, check)){ //Capture the piece, if possible
                            b.pieces[i][j].hasMoved = true;
                            Initialize_Texture(b.pieces);
                            Unhighlight(b.pieces);
                            pieceCapaClick = false;
                            turn = !turn;
                            moveCount++;
                            check = false;
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
                    else if(pieceCapaClick && b.pieces[i][j].type == CAPABLANK ){
                        //Execute a movement, if possible
                        if(b.pieces[i][j].movement(b.pieces, i, j, iPiece, jPiece, check)){
                            b.pieces[i][j].hasMoved = true;
                            turn = !turn;
                            check = false;
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
                                    checkMate = true;
                                }
                            }
                            Initialize_Texture(b.pieces);
                            Unhighlight(b.pieces);
                            pieceCapaClick = false;
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
    return false;
}

