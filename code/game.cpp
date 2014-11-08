#include <SFML/Graphics.hpp>
#include "headers/game.h"
#include <iostream>
#include <string>
#include <sstream>


using namespace std;

    sf::Texture pawns,   bpawns,
                towers,  btowers,
                knights, bknights,
                bishops, bbishops,
                queens,  bqueens,
                kings,   bkings,
                archbishops, barchbishops,
                chancelers, bchancelers,
                blanks;

    bool pieceClick = false;



Game::Game(sf::RenderWindow &window, int color, int gametype) :
            b(BOARD_X, BOARD_Y, color, gametype),
            Hint(750, 100, 15, 15, "Hint"),
            Mute(750, 130, 15, 15, "Chat"),
            TurnIndicator(120, 100, 15, 15),
            pieceholder(window),
            mainWindow(window),
            gameover(window), //int x, int y, int size_x, int size_y, int input_x, int input_y, ChatStyle style
            hist(PAPER_X, PAPER_Y, 150, 190),
            chat(PAPER_X, PAPER_Y, 150, 190, BOARD_X + 128, BOARD_Y + 256, ChatStyle::GameChat),
            giveUpButton(865, 650, 33, 33, "", "exit", ButtonStyle::NoText),
            OptionsButton(715 + 3, 648 + 8, 35, 35, "", "eye3D", ButtonStyle::NoText),
            ChatButton(765, 650, 40, 30, "", "chat", ButtonStyle::NoText){
    font.loadFromFile("media/fonts/Carbon.TTF");
    this->boardTexture = new sf::Texture();
    this->capaboardTexture = new sf::Texture();

    this->backgroundTexture = new sf::Texture();

    this->outborderTexture = new sf::Texture();
    this->capaoutborderTexture = new sf::Texture();

    this->topPlayerTexture = new sf::Texture();
    this->botPlayerTexture = new sf::Texture();

    this->boxTexture       = new sf::Texture();
    this->bigboxTexture    = new sf::Texture();

    this->paperTexture     = new sf::Texture();

    this->closedEyeTexture = new sf::Texture();

    this->bipBuffer        = new sf::SoundBuffer();
    this->bipBuffer->loadFromFile("media/sounds/bip2.wav");
    this->bip.setBuffer(*this->bipBuffer);

    this->tocBuffer        = new sf::SoundBuffer();
    this->tocBuffer->loadFromFile("media/sounds/toc.wav");
    this->toc.setBuffer(*this->tocBuffer);


    this->boardTexture->loadFromFile("media/images/board.png");
    this->outborderTexture->loadFromFile("media/images/outborderNumbered.png");
    this->capaboardTexture->loadFromFile("media/images/capaboard.png");
    this->capaoutborderTexture->loadFromFile("media/images/capaoutborder.png");

    this->backgroundTexture->loadFromFile("media/images/background.png");
    this->topPlayerTexture->loadFromFile("media/images/topplayer.png");
    this->botPlayerTexture->loadFromFile("media/images/botplayer.png");
    this->boxTexture->loadFromFile("media/images/box.png");
    this->bigboxTexture->loadFromFile("media/images/bigbox.png");
    this->paperTexture->loadFromFile("media/images/papers/chatpaper.png");
    this->closedEyeTexture->loadFromFile("media/images/closedEye.png");

    this->board.setTexture(*this->boardTexture);
    this->capaboard.setTexture(*this->capaboardTexture);
    this->background.setTexture(*this->backgroundTexture);
    this->outborder.setTexture(*this->outborderTexture);
    this->capaoutborder.setTexture(*this->capaoutborderTexture);
    this->topPlayer.setTexture(*this->topPlayerTexture);
    this->botPlayer.setTexture(*this->botPlayerTexture);
    this->box.setTexture(*this->boxTexture);
    this->bigbox.setTexture(*this->bigboxTexture);
    this->paper.setTexture(*this->paperTexture);
    this->closedEye.setTexture(*this->closedEyeTexture);

    this->closedEye.setPosition(715 + 3, 648 + 8);


    this->board.setPosition(BOARD_X, BOARD_Y);
    this->capaboard.setPosition(BOTPLAYER_X + 30, CBOARD_Y);

    this->outborder.setPosition(BOARD_X - 15, BOARD_Y - 15);
    this->capaoutborder.setPosition(BOTPLAYER_X + 15, CBOARD_Y - 13);

    this->topPlayer.setPosition(TOPPLAYER_X, TOPPLAYER_Y);
    this->botPlayer.setPosition(BOTPLAYER_X, BOTPLAYER_Y);

    this->box.setPosition(BOX_X, BOX_Y);
    this->bigbox.setPosition(BOX_X - 16, BOX_Y);

    this->myPrize.setPosition(TOPPLAYER_X + 45, TOPPLAYER_Y + 637);
    this->enemyPrize.setPosition(TOPPLAYER_X + 45, TOPPLAYER_Y + 7);
    this->paper.setPosition(PAPER_X, PAPER_Y);
    this->gameIcon.setPosition(822, 450);

    this->turn = 1;
    this->myColor = color;
    this->moveCount = 0;
    this->check = false;
    this->enemyCheck = false;
    this->checkMate = false;
    this->ranked = true;

    this->warnings.setFont(font);
    this->warnings.setCharacterSize(30U);
    this->warnings.setColor(sf::Color::Red);
    this->warnings.setPosition(BOARD_X + 64*3, BOARD_Y + 64*4 - 16);
    this->warnings.setString("Check!");

    this->myClockText.setFont(font);
    this->myClockText.setCharacterSize(20U);
    this->myClockText.setColor(sf::Color::Black);
    this->myClockText.setPosition(750, 400);

    this->myName.setFont(font);
    this->myName.setCharacterSize(40U);
    this->myName.setColor(sf::Color::Black);
    this->myName.setPosition(350, botPlayer.getPosition().y + 5);


    this->displayELO.setFont(font);
    this->displayELO.setCharacterSize(20U);
    this->displayELO.setColor(sf::Color::Black);
    this->displayELO.setPosition(TOPPLAYER_X + 100, BOTPLAYER_Y + 20);

    this->enemyELO.setFont(font);
    this->enemyELO.setCharacterSize(20U);
    this->enemyELO.setColor(sf::Color::Black);
    this->enemyELO.setPosition(TOPPLAYER_X + 100, TOPPLAYER_Y + 20);


    this->enemyClockText.setFont(font);
    this->enemyClockText.setCharacterSize(20U);
    this->enemyClockText.setColor(sf::Color::Black);
    this->enemyClockText.setPosition(750, 200);

    this->enemyName.setFont(font);
    this->enemyName.setCharacterSize(40U);
    this->enemyName.setColor(sf::Color::Black);
    this->enemyName.setPosition(350, 5);
    this->enemyName.setString("Enemy name");

    this->watching.setFont(font);
    this->watching.setCharacterSize(18U);
    this->watching.setColor(sf::Color(0, 172, 0));
    this->watching.setPosition(738, 663);
    this->watching.setString("0");
    this->isPublic = 1;

    this->myTime = 300;
    this->enemyTime = 300;

    this->userX = 0;
    this->userY = 0;

    rows = 8;
    columns = 8;
    int k, p;
    for(k = 0; k < rows; k++){
        for(p = 0; p < 10; p++){
            boardStatus[k][p] = ' ';
        }
    }
    testCheck.columns = columns;
}

void Game::reset(int gameColor, int gameTime, int gameType, bool ranked){
    this->turn              = 1;
    this->myColor           = gameColor;
    this->gametype          = gameType;
    this->gameTime          = gameTime;
    this->moveCount         = 0;
    this->enemyelo          = 0;
    this->check             = false;
    this->enemyCheck        = false;
    this->checkMate         = false;
    this->ranked            = ranked;

    this->enemyClockText.setColor(sf::Color::Black);
    this->myClockText.setColor(sf::Color::Black);
    this->myPrize.setTexture(*Textures::selectPrize(network.myCurrentELO));
    this->gameIcon.setTexture(*Textures::selectGameIcon(gameType, gameTime));
    this->paper.setTexture(*Textures::selectPaper(gameType));
    this->displayELO.setString(to_string(network.myCurrentELO));
    this->hist.reset(gameType, gameTime);
    this->chat.history.clear();
    this->pieceholder.reset();

    if(gametype == 2){
        this->columns = 10;
        this->b.columns = 10;
    }
    else{
        this->columns = 8;
        this->b.columns = 8;
    }

    if(gameTime > 0) {
        this->myTime            = gameTime;
        this->enemyTime         = gameTime;
    }
    else{
        this->myTime            = 300;
        this->enemyTime         = 300;
    }



    this->TurnIndicator.turn = true;
    this->userX = 0;
    this->userY = 0;

    if(gameColor){
        if(gametype == 2)
            this->b.Initialize(BOTPLAYER_X + 30, CBOARD_Y, gametype);
        else
            this->b.Initialize(BOARD_X, BOARD_Y, gametype);
    }

    else{
        if(gametype == 2)
            this->b.InitializeBlack(BOTPLAYER_X + 30, CBOARD_Y, gametype);
        else
            this->b.InitializeBlack(BOARD_X, BOARD_Y, gametype);
    }


    testCheck.columns = columns;
}

void Game::draw(){
    mainWindow.draw(background);
    if(gametype == 2){
        mainWindow.draw(capaoutborder);
        mainWindow.draw(capaboard);
        mainWindow.draw(bigbox);
    }
    else{
        mainWindow.draw(outborder);
        mainWindow.draw(board);
        mainWindow.draw(box);
    }

    mainWindow.draw(topPlayer);
    mainWindow.draw(botPlayer);


    //mainWindow.draw(Hint.image);
    //mainWindow.draw(Hint.text);

    //mainWindow.draw(Mute.image);
    //mainWindow.draw(Mute.text);

    //mainWindow.draw(TurnIndicator.image);
    //mainWindow.draw(TurnIndicator.text);
    mainWindow.draw(myClockText);
    mainWindow.draw(myName);
    mainWindow.draw(enemyClockText);
    mainWindow.draw(enemyName);

    mainWindow.draw(ChatButton.image);
    mainWindow.draw(giveUpButton.image);
    if(isPublic){
        mainWindow.draw(OptionsButton.image);
        mainWindow.draw(watching);
    }

    else
        mainWindow.draw(closedEye);
    //displayELO.setString(to_string(network.myCurrentELO));
    if(ranked){
        mainWindow.draw(displayELO);
        mainWindow.draw(enemyELO);
        mainWindow.draw(myPrize);
        mainWindow.draw(enemyPrize);
    }



    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++){
            mainWindow.draw(b.pieces[i][j].square ); //Draw the background first
            mainWindow.draw(b.pieces[i][j].image ); //Then the piece itself
            if(b.pieces[i][j].highlighted){
                mainWindow.draw(b.pieces[i][j].border);
            }
            if(b.pieces[i][j].current){
                mainWindow.draw(b.pieces[i][j].grayborder);
            }
            if(b.pieces[i][j].attacked){
                mainWindow.draw(b.pieces[i][j].redborder);
            }
            if(b.pieces[i][j].selected){
                mainWindow.draw(b.pieces[i][j].yellowborder);
            }
        }
    }
    mainWindow.draw(warnings);
    hist.draw(mainWindow);
    pieceholder.draw();
    if(hist.chatOn) chat.draw(mainWindow);
    //mainWindow.draw(gameIcon);
}

int Game::Run(STATE& state){
    /*Pieces' texture initialization*/
    Initialize_Texture(b.pieces);
    int i, j, iP, jP, cl = 0;

    string msg;
    packetID receive;

    updateBoardStatus();
    network.sendBoardStatus(boardStatus);
    while (mainWindow.isOpen() && state == STATE::Game){
        if(turn == myColor){
            myClockText.setColor(sf::Color(155, 155, 155));
            enemyClockText.setColor(sf::Color::Black);
            if(myClock.getElapsedTime().asSeconds() > 1){
                myTime--;
                myClock.restart();
            }
        }
        else{
            enemyClockText.setColor(sf::Color(155, 155, 155));
            myClockText.setColor(sf::Color::Black);
            if(myClock.getElapsedTime().asSeconds() > 1){
                enemyTime--;
                myClock.restart();
            }
        }
        if(enemyTime <= 20) enemyClockText.setColor(sf::Color::Red);
        if(myTime <= 20) myClockText.setColor(sf::Color::Red);


            cl = 255 - static_cast<int>(warningClock.getElapsedTime().asSeconds()*85);

        if(cl < 0) cl = 0;
        if(cl > 255) cl = 0;
        warnings.setColor(sf::Color(150, 0, 0, cl));

        enemyClockText.setString(toClock(enemyTime));
        myClockText.setString(toClock(myTime));

        if(myTime == 0){
            network.sendMyTimeout();
            gameover.setWinner(!myColor);
            if(ranked)
                gameover.setEloDifferente(network.myCurrentELO, enemyelo, 0);
        }
        else if(enemyTime == 0){
            network.sendEnemyTimeout();
            gameover.setWinner(myColor);
            if(ranked)
                gameover.setEloDifferente(network.myCurrentELO, enemyelo, 1);
        }

        sf::Event event;
        while (mainWindow.pollEvent(event)){
            handleEvent(event, state);
        }
        gesturalModule.receiveGesturalMovement();
        if(gesturalModule.clicked){
             if(handleInput(gesturalModule.x, gesturalModule.y)){
                processMove(state);
             }
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
                b.pieces[i][j].moves++;
                if(check){
                    warningClock.restart();
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

            case packetID::numberWatching:
                watching.setString(to_string(network.receiveNumberWatching()));
            break;

            case packetID::Checkmate:
                logCheck();
                cout << history.history << endl;
                cout << "Game over! " << (myColor? "Black wins!" : "White wins!") << endl;
                gameover.setWinner(!myColor);
                if(ranked)
                    gameover.setEloDifferente(network.myCurrentELO, enemyelo, 0);
                state = STATE::GameOver;
            break;
            case packetID::GiveUp:
                cout << "Game over! " << (!myColor? "Black wins!" : "White wins!") << endl;
                gameover.setWinner(myColor);
                if(ranked)
                    gameover.setEloDifferente(network.myCurrentELO, enemyelo, 1);
                state = STATE::GameOver;
            break;
            case packetID::Chat:
                msg = network.receiveChat();
                if(Mute.checked)
                    chat.receiveMessage(msg);
                if(!hist.chatOn){
                    ChatButton.changeIcon("chatAlert.png");
                    bip.play();
                }

            break;
            case packetID::Name:
                msg = network.receiveName();

                enemyName.setString(msg);
                myName.setString(network.myName);

                enemyName.setPosition(345 - 7*enemyName.getString().getSize(), 5);
                myName.setPosition(345 - 7*myName.getString().getSize(), botPlayer.getPosition().y + 5);

                enemyClockText.setPosition(enemyName.getPosition().x + 300, enemyName.getPosition().y + 15);
                myClockText.setPosition(enemyName.getPosition().x + 300, myName.getPosition().y + 15);

            break;
            case packetID::Elo:
                enemyelo = network.receiveElo();
                enemyELO.setString(to_string(enemyelo));
                enemyPrize.setTexture(*Textures::selectPrize(enemyelo));
            break;
            case packetID::GameEnd:

                state = STATE::GameOver;
                //network.sendDisconnect();
                //mainWindow.close();
            break;
            case packetID::GameEndTimeOut:
                gameover.setWinner(!myColor);
                if(ranked)
                    gameover.setEloDifferente(network.myCurrentELO, enemyelo, 0);
                state = STATE::GameOver;
            break;
        }
        mainWindow.clear(sf::Color(0, 150, 255));
        //window.clear(sf::Color(0, 0, 0));
        draw();
        mainWindow.display();

    }

    if(state == STATE::GameOver){
        gameover.setMatchDuration(gameTime, myTime, enemyTime);
        gameover.run(state);
    }
}

void Unhighlight(Piece b[8][10]){
     for(int i = 0; i < 8; i++){
        for(int j = 0; j < 10; j++){
            b[i][j].square.setFillColor(sf::Color::Transparent);
            b[i][j].highlighted = false;
            b[i][j].clicked = false;
            b[i][j].attacked = false;
            b[i][j].selected = false;
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
    history.currentMove = b.pieces[i][j].code + coordToCode(iP, jP) + coordToCode(i, j);
    hist.putMove(history.currentMove);
}

void Game::logCapture(int i, int j, int iP, int jP){
    history.currentMove = b.pieces[i][j].code + coordToCode(iP, jP) + "x" + coordToCode(i, j);
    hist.putMove(history.currentMove);
}

void Game::logCheck(){
    history.currentMove = history.currentMove + "+";
    hist.putMove(history.currentMove);
}

void Game::makeEnemyMove(int i, int j, int iP, int jP){

    if(b.pieces[i][j].color == !b.pieces[iP][jP].color){
        logCapture(i, j, iP, jP);
        pieceholder.add(b.pieces[i][j].type, b.pieces[i][j].color);
    }
    else
        logMove(i, j, iP, jP);

    if(b.pieces[iP][jP].type == PAWN &&
       b.pieces[i][j].type == BLANK){ //en passant
        if(jP == j + 1){
            b.pieces[iP][j].type = BLANK;
            b.pieces[iP][j].code = "";
            b.pieces[iP][j].color = -1;
        }
        else if(jP == j - 1){
            b.pieces[iP][j].type = BLANK;
            b.pieces[iP][j].code = "";
            b.pieces[iP][j].color = -1;
        }


    }
    b.pieces[i][j].hasMoved = true;
    b.pieces[i][j].code = b.pieces[iP][jP].code;
    b.pieces[i][j].type = b.pieces[iP][jP].type;
    b.pieces[i][j].color = b.pieces[iP][jP].color;
    b.pieces[iP][jP].type = BLANK;
    b.pieces[iP][jP].code = "";
    b.pieces[iP][jP].color = -1;

    if((i == 0 || i == columns - 1) && b.pieces[i][j].type == PAWN){
        b.pieces[i][j].code = "Q";
        b.pieces[i][j].type = QUEEN;
    }

    Initialize_Texture(b.pieces);
    turn = !turn;
    enemyCheck = false;
    moveCount++;
    toc.play();
}

void Game::handleEvent(const sf::Event& event, STATE& state){
    char input;
    switch(event.type){
        case sf::Event::Closed:
            network.sendGiveUp();
            network.sendDisconnect();
            mainWindow.close();
        break;
        case sf::Event::TextEntered:
            input = static_cast<char>(event.text.unicode);
            if(hist.chatOn)
                chat.handleInput(input);
        break;
        case sf::Event::KeyPressed:
            input = static_cast<char>(event.text.unicode);
            if(keyboardMove(input)){
                processMove(state);
            }
        break;
        case sf::Event::MouseButtonPressed:
            if(handleInput(event.mouseButton.x, event.mouseButton.y)){
                processMove(state);
            }
            else if(chat.rectChatBox.contains(event.mouseButton.x, event.mouseButton.y)){
                chat.active = true;
            }
            else if(giveUpButton.clicked(event.mouseButton.x, event.mouseButton.y)){
                network.sendMatchHistory(history.history);
                network.sendGiveUp();
                gameover.setWinner(!myColor);
                cout << "Game over! " << (!myColor? "White wins!" : "Black wins!") << endl;
                if(ranked)
                    gameover.setEloDifferente(network.myCurrentELO, enemyelo, 0);
                state = STATE::GameOver;
            }
            hist.handleInput(event.mouseButton.x, event.mouseButton.y);
        break;
    }
}

void Game::processMove(STATE& state){
    network.sendMove(this->i, this->j, iPiece, jPiece, enemyCheck, boardStatus);
    network.sendMoveLog(history.currentMove + ";");
    TurnIndicator.changeTurn();
    cout << history.history << endl;
    if(checkMate){
        network.sendMatchHistory(history.history);
        network.sendCheckMate();
        gameover.setWinner(myColor);
        //state == STATE::GameOver;
        cout << "Game over! " << (myColor? "White wins!" : "Black wins!") << endl;
        if(ranked)
            gameover.setEloDifferente(network.myCurrentELO, enemyelo, 1);
        state = STATE::GameOver;
    }
    myClock.restart();
    toc.play();

}

bool Game::keyboardMove(char c){
    switch(c){
        case sf::Keyboard::Space: {
            return processInput(userY, userX);
        }
        case sf::Keyboard::Down: {
            if(myColor){
               if(userY - 1 >= 0){
                    b.pieces[userY][userX].current = false;
                    b.pieces[--userY][userX].current = true;
                }
            }
            else{
                if(userY + 1 < 8){
                    b.pieces[userY][userX].current = false;
                    b.pieces[++userY][userX].current = true;
                }
            }

            break;
        }
        case sf::Keyboard::Up: {
            if(myColor){
                if(userY + 1 < 8){
                    b.pieces[userY][userX].current = false;
                    b.pieces[++userY][userX].current = true;
                }
            }
            else{
                if(userY - 1 >= 0){
                    b.pieces[userY][userX].current = false;
                    b.pieces[--userY][userX].current = true;
                }
            }
            break;
        }
        case sf::Keyboard::Left: {
            if(myColor){
                if(userX - 1 >= 0){
                    b.pieces[userY][userX].current = false;
                    b.pieces[userY][--userX].current = true;
                }
            }
            else{
                if(userX + 1 < columns){
                    b.pieces[userY][userX].current = false;
                    b.pieces[userY][++userX].current = true;
                }
            }

            break;
        }
        case sf::Keyboard::Right: {
            if(myColor){
               if(userX + 1 < columns){
                    b.pieces[userY][userX].current = false;
                    b.pieces[userY][++userX].current = true;
                }
            }
            else{
                if(userX - 1 >= 0){
                    b.pieces[userY][userX].current = false;
                    b.pieces[userY][--userX].current = true;
                }
            }
            break;
        }
    }
    return false;
}

bool Game::handleInput(int x, int y){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < columns; j++){
            if(b.pieces[i][j].rectSquare.contains(x, y)){ //If the click was in a square...
                if(processInput(i, j)) return true;
                return false;
            }
        }
    }
    if(Hint.clicked(x, y)){
        Hint.action();
        return false;
    }
    if(Mute.clicked(x, y)){
        Mute.action();
        return false;
    }
    if(ChatButton.clicked(x, y)){
        if(hist.chatOn) ChatButton.changeIcon("chat.png");
        else            ChatButton.changeIcon("notepad.png");
        hist.chatOn = !hist.chatOn;
        return false;
    }
    return false;
}

bool Game::processInput(int i, int j){
    if(myColor == turn){
        if(b.pieces[i][j].color == myColor){ //I clicked one of my pieces.
            if(!pieceClick){ //I have not clicked in one of my pieces yet.
                pieceClick = true;
                iPiece = i;
                jPiece = j;
                if(!b.pieces[i][j].clicked)//? b.pieces[i][j].square.setFillColor(sf::Color::Transparent) : //If the piece was already clicked once, turn it back to transparent
                    b.pieces[i][j].selected = true; //If not, highlight it in yellow
                b.pieces[i][j].clicked = !b.pieces[i][j].clicked;
                if(Hint.checked) b.Highlight(b.pieces[i][j].type, i, j);
            }
            else if(pieceClick && i == iPiece && j == jPiece){ //Clicking again in the same piece
                Unhighlight(b.pieces);
                pieceClick = false;
            }
        }//I have already clicked on a piece, and now I am clicking on an enemy's piece.
        else if(pieceClick && b.pieces[i][j].color == !myColor){
            TYPE type = b.pieces[i][j].type;
            if(b.pieces[i][j].capture(b.pieces, i, j, iPiece, jPiece, check)){ //Capture the piece, if possible
                pieceholder.add(type, !b.pieces[i][j].color);
                b.pieces[i][j].hasMoved = true;
                if((i == 0 || i == columns - 1) && b.pieces[i][j].type == PAWN){
                    b.pieces[i][j].code = "Q";
                    b.pieces[i][j].type = QUEEN;
                }
                Initialize_Texture(b.pieces);
                Unhighlight(b.pieces);
                pieceClick = false;
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
                updateBoardStatus();
                return true;
            }
            else{
                warnings.setString("Invalid move!");
                warningClock.restart();
            }
        }//I have already clicked on a piece, and now I am clicking on an empty square.
        else if(pieceClick && b.pieces[i][j].type == BLANK ){
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
                pieceClick = false;
                this->i = i;
                this->j = j;
                history.history += history.currentMove + ";";
                updateBoardStatus();
                return true;
            }
            else{
                warnings.setString("Invalid move!");
                warningClock.restart();
            }
        }
    }
    return false;
}

void Game::updateBoardStatus(){
    int i, j;
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++){
            switch(b.pieces[i][j].type){
                case BLANK:
                    boardStatus[i][j] = " ";
                break;
                case PAWN:
                    if(b.pieces[i][j].color)
                        boardStatus[i][j] = "P";
                    else
                        boardStatus[i][j] = "p";
                break;
                case KNIGHT:
                    if(b.pieces[i][j].color)
                        boardStatus[i][j] = "N";
                    else
                        boardStatus[i][j] = "n";
                break;
                case BISHOP:
                    if(b.pieces[i][j].color)
                        boardStatus[i][j] = "B";
                    else
                        boardStatus[i][j] = "b";
                break;
                case TOWER:
                    if(b.pieces[i][j].color)
                        boardStatus[i][j] = "R";
                    else
                        boardStatus[i][j] = "r";
                break;
                case QUEEN:
                    if(b.pieces[i][j].color)
                        boardStatus[i][j] = "Q";
                    else
                        boardStatus[i][j] = "q";
                break;
                case KING:
                    if(b.pieces[i][j].color)
                        boardStatus[i][j] = "K";
                    else
                        boardStatus[i][j] = "k";
                break;
                case ARCHBISHOP:
                    if(b.pieces[i][j].color)
                        boardStatus[i][j] = "A";
                    else
                        boardStatus[i][j] = "a";
                    break;
                case CHANCELER:
                    if(b.pieces[i][j].color)
                        boardStatus[i][j] = "C";
                    else
                        boardStatus[i][j] = "c";
                    break;
            }
        }
    }
}



void Game::Initialize_Texture(Piece pieces[8][10]){

    blanks.loadFromFile("media/images/pieces/blank.png");

    pawns.loadFromFile("media/images/pieces/pawn.png");
    bpawns.loadFromFile("media/images/pieces/bpawn.png");

    towers.loadFromFile("media/images/pieces/rook.png");
    btowers.loadFromFile("media/images/pieces/brook.png");

    knights.loadFromFile("media/images/pieces/knight.png");
    bknights.loadFromFile("media/images/pieces/bknight.png");

    bishops.loadFromFile("media/images/pieces/bishop.png");
    bbishops.loadFromFile("media/images/pieces/bbishop.png");

    queens.loadFromFile("media/images/pieces/queen.png");
    bqueens.loadFromFile("media/images/pieces/bqueen.png");

    kings.loadFromFile("media/images/pieces/king.png");
    bkings.loadFromFile("media/images/pieces/bking.png");

    archbishops.loadFromFile("media/images/pieces/archbishop55.png");
    barchbishops.loadFromFile("media/images/pieces/barchbishop55.png");

    chancelers.loadFromFile("media/images/pieces/chancellor.png");
    bchancelers.loadFromFile("media/images/pieces/bchancellor55.png");

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < columns; j++){
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
            }
        }
    }

}
