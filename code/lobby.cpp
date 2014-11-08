#include <SFML/Graphics.hpp>
#include "headers/lobby.h"
#include "headers/gesturalModule.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


Lobby::Lobby(sf::RenderWindow& window):
                    mainWindow(window), //x, y, size x, size y, title, text x, text y
                    game(window, 1, 1),
                    playButton            (420, 15, 100, 80, "Play", "", ButtonStyle::NoImage),
                    exitQueueButton       (840, 50, 35, 35, "", "redExit", ButtonStyle::NoText),
                    select5minutesButton  (250, 50, 15, 15, "5"),
                    select15minutesButton (300, 50, 25, 15, "15"),
                    select30minutesButton (350, 50, 25, 15, "30"),
                    selectClassicButton   (550, 50, 50, 15, "Classic"),
                    select960Button       (622, 50, 35, 15, "Fischer"),
                    selectCapaButton      (690, 50, 65, 15, "Capablanca"),
                    PlayerListContainer   (20, 100, 170, 600),
                    PlayerRankContainer   (160, 100, 780, 450),
                    MatchContainer        (160, 400, 780, 150),
                    invite(window),
                    spectator(window, game, 1){
    warningFont.loadFromFile("media/fonts/AGENCYB.TTF");
    warnings.setFont(warningFont);
    warnings.setPosition(390, 560);
    warnings.setString("");
    warnings.setCharacterSize(20U);


    playButton.text.setCharacterSize(30U);
    myNick.setFont(warningFont);
    myNick.setPosition(50, 40);
    myNick.setString(network.myName);
    myNick.setCharacterSize(20U);
    myNick.setColor(sf::Color::White);

    myELO.setFont(warningFont);
    myELO.setPosition(50, 65);
    myELO.setString("");
    myELO.setCharacterSize(20U);
    myELO.setColor(sf::Color::White);

    this->backgroundTexture         = new sf::Texture();
    this->BTNbackgroundTexture      = new sf::Texture();
    this->fichaTexture              = new sf::Texture();
    this->selectionMarkTexture      = new sf::Texture();
    this->selectionUnderMarkTexture = new sf::Texture();
    this->redMarkTexture            = new sf::Texture();

    BTNbackground.setPosition(select5minutesButton.pos_x - 35, select5minutesButton.pos_y - 40);
    selectionMark.setPosition(select5minutesButton.pos_x - 15, select5minutesButton.pos_y - 15);
    selectionUnderMark.setPosition(selectClassicButton.pos_x - 5, selectClassicButton.pos_y + 15);
    redMark.setPosition(playButton.pos_x, playButton.pos_y + 8);


    this->BTNbackgroundTexture->loadFromFile("media/images/buttonBG.png");
    this->BTNbackground.setTexture(*this->BTNbackgroundTexture);

    this->selectionMarkTexture->loadFromFile("media/images/mark.png");
    this->selectionMark.setTexture(*this->selectionMarkTexture);

    this->selectionUnderMarkTexture->loadFromFile("media/images/undermark.png");
    this->selectionUnderMark.setTexture(*this->selectionUnderMarkTexture);

    this->redMarkTexture->loadFromFile("media/images/redmark.png");
    this->redMark.setTexture(*this->redMarkTexture);

    this->backgroundTexture->loadFromFile("media/images/lobbybg.png");
    this->background.setTexture(*this->backgroundTexture);

    this->fichaTexture->loadFromFile("media/images/ficha.png");
    this->ficha.setTexture(*this->fichaTexture);
    this->ficha.setPosition(200, 200);


    this->waitingForGame = false;
    this->invited = false;
    this->ranked = false;
    gameTime = 300;
    select5minutesButton.mark();
    select15minutesButton.unmark();
    select30minutesButton.unmark();
    gameMode = 0;
    selectClassicButton.mark();
    select960Button.unmark();
    selectCapaButton.unmark();
    PlayerRankContainer.setCurrentElo(gameTime, gameMode);
}

void Lobby::draw(){
    mainWindow.clear(sf::Color(0, 150, 255));
    mainWindow.draw(background);

   // mainWindow.draw(ficha);
    mainWindow.draw(BTNbackground);
    //mainWindow.draw(playButton.image);
    mainWindow.draw(playButton.text);
    if(waitingForGame)
        mainWindow.draw(exitQueueButton.image);

    mainWindow.draw(select5minutesButton.text);
    mainWindow.draw(select15minutesButton.text);
    mainWindow.draw(select30minutesButton.text);

    mainWindow.draw(selectClassicButton.text);
    mainWindow.draw(selectCapaButton.text);
    mainWindow.draw(select960Button.text);

    mainWindow.draw(selectionMark);
    mainWindow.draw(selectionUnderMark);
    if(playButton.rectSquare.contains(sf::Mouse::getPosition(mainWindow).x, sf::Mouse::getPosition(mainWindow).y)){
        mainWindow.draw(redMark);
    }
    mainWindow.draw(warnings);

    PlayerListContainer.draw(mainWindow);
    PlayerRankContainer.draw(mainWindow);
    MatchContainer.draw(mainWindow);
    //window.clear(sf::Color(0, 0, 0));
    if(invited || invite.inviteRejected)
        invite.draw();
    if(inviteRequest.inviting)
        inviteRequest.draw();

    myNick.setString(network.myName);
    mainWindow.draw(myNick);
    myELO.setString(to_string(network.myCurrentELO));
    mainWindow.draw(myELO);

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
        gesturalModule.receiveGesturalMovement();
        if(gesturalModule.clicked){
             handleInput(gesturalModule.x, gesturalModule.y, state);
        }

        switch(receive){
            case packetID::GameRequest:
                network.sendConnect();
            break;

            case packetID::GameInvite: {
                invited = true;
                string name;
                int gMode, gTime;
                bool gPublic;
                network.receiveInvite(name, gMode, gTime, gPublic);
                invite.name = name;
                invite.gameMode = gMode;
                invite.gameTime = gTime;
                invite.isPublic = gPublic;
                cout << "invite received" << endl;
                invite.setText();
            break;
            }

            case packetID::InviteRejection:{
                string name;
                invite.inviteRejected = true;
                network.receiveRejectedInvite(&name);
                invite.setRejectedText(name);

            break;
            }

            case packetID::Connect:
                state = STATE::Game;

            break;

            case packetID::Options:
                network.receiveOptions(&gameColor, &gameMode, &gameTime, &ranked);
            break;

            case packetID::FischerPieceOrder:{
                string newBoard[8][10];
                network.receiveFischerPiecesOrder(newBoard);
                game.b.setBoard(newBoard);
            break;
            }

            case packetID::WatchState: {
                string white, black;
                string newBoard[8][10];
                int whiteElo, blackElo, gameMode;
                network.receiveMatchStatus(&white, &black, &whiteElo, &blackElo, newBoard, &gameMode);
                spectator.updateMatchStatus(white, black, whiteElo, blackElo, newBoard, gameMode);
                state = STATE::Watching;
            break;
            }

            case packetID::PlayerList:
                PlayerListContainer.receiveList(network.receivePlayerList());
                PlayerRankContainer.receiveList(PlayerListContainer.playersInfo);
            break;
            case packetID::MatchList:
                network.receiveMatchList(MatchContainer.matchesInfo);
                MatchContainer.updateList();
            break;
        }

        draw();
    }
    if(state == STATE::Game){
        warnings.setString("");
        waitingForGame = false;
        if(invited){
            game.reset(0, invite.gameTime, invite.gameMode, 0);
            game.isPublic = invite.isPublic;
        }else
            game.reset(gameColor, gameTime, gameMode, ranked);

        invited = false;
        if(gameMode == 1){
            game.b.randomizePieces();
            game.updateBoardStatus();
            network.sendFischerPiecesOrder(game.boardStatus);
        }
        game.Run(state);
    }
    if(state == STATE::Watching){
        spectator.run(state);
    }
}

void Lobby::handleEvent(const sf::Event& event, STATE& state){
    char letter;

    switch(event.type){
        case sf::Event::Closed:
            network.sendDisconnect();
            network.sendExitQueue();
            mainWindow.close();
        break;
        case sf::Event::MouseButtonPressed:{
            int x = event.mouseButton.x;
            int y = event.mouseButton.y;
            handleInput(x, y, state);
        break;
        }

        case sf::Event::KeyPressed:
            handleInput(event.key, state);
        break;
    }
}

void Lobby::handleInput(sf::Event::KeyEvent key, STATE& state){
    if(inviteRequest.inviting){
        inviteRequest.handleInput(key, state);
    }
}

void Lobby::handleInput(int x, int y, STATE& state){
    int matchID;
    if(!waitingForGame && !invited && !invite.inviteRejected && !inviteRequest.inviting){
        if(playButton.clicked(x, y)){
            warnings.setString("Waiting for another player...");
            network.sendGameRequest(gameMode, gameTime);
            waitingForGame = true;
        }
        if(select5minutesButton.clicked(x, y) && gameTime != 300){
            selectionMark.setPosition(select5minutesButton.pos_x - 15, select5minutesButton.pos_y - 15);
            select5minutesButton.mark();
            select15minutesButton.unmark();
            select30minutesButton.unmark();

            gameTime = 300;
            network.myCurrentELO = network.myELO[gameMode][gameTime/900];
            PlayerRankContainer.setCurrentElo(gameTime, gameMode);
        }
        if(select15minutesButton.clicked(x, y) && gameTime != 900){
            selectionMark.setPosition(select15minutesButton.pos_x - 15, select15minutesButton.pos_y - 15);
            select5minutesButton.unmark();
            select15minutesButton.mark();
            select30minutesButton.unmark();
            gameTime = 900;
            network.myCurrentELO = network.myELO[gameMode][gameTime/900];
            PlayerRankContainer.setCurrentElo(gameTime, gameMode);
        }
        if(select30minutesButton.clicked(x, y) && gameTime != 1800){
            selectionMark.setPosition(select30minutesButton.pos_x - 11, select30minutesButton.pos_y - 15);
            select5minutesButton.unmark();
            select15minutesButton.unmark();
            select30minutesButton.mark();
            gameTime = 1800;
            network.myCurrentELO = network.myELO[gameMode][gameTime/900];
            PlayerRankContainer.setCurrentElo(gameTime, gameMode);
        }

        if(selectClassicButton.clicked(x, y) && gameMode != 0){
            selectionUnderMark.setPosition(selectClassicButton.pos_x - 5, selectClassicButton.pos_y + 15);
            PlayerRankContainer.setRecordColor("blue");
            selectClassicButton.mark();
            selectCapaButton.unmark();
            select960Button.unmark();
            gameMode = 0;
            network.myCurrentELO = network.myELO[gameMode][gameTime/900];
            PlayerRankContainer.setCurrentElo(gameTime, gameMode);
            //MatchContainer.updateMatchesBG(gameMode);
        }
        if(selectCapaButton.clicked(x, y) && gameMode != 2){
            selectionUnderMark.setPosition(selectCapaButton.pos_x + 5, selectCapaButton.pos_y + 15);
            PlayerRankContainer.setRecordColor("red");
            selectClassicButton.unmark();
            selectCapaButton.mark();
            select960Button.unmark();
            gameMode = 2;
            network.myCurrentELO = network.myELO[gameMode][gameTime/900];
            PlayerRankContainer.setCurrentElo(gameTime, gameMode);
            //MatchContainer.updateMatchesBG(gameMode);
        }
        if(select960Button.clicked(x, y) && gameMode != 1){
            selectionUnderMark.setPosition(select960Button.pos_x - 5, select960Button.pos_y + 15);
            PlayerRankContainer.setRecordColor("yellow");
            selectClassicButton.unmark();
            selectCapaButton.unmark();
            select960Button.mark();
            gameMode = 1;
            network.myCurrentELO = network.myELO[gameMode][gameTime/900];
            PlayerRankContainer.setCurrentElo(gameTime, gameMode);
            //MatchContainer.updateMatchesBG(gameMode);
        }

        PlayerListContainer.handleInput(x,y);
        PlayerRankContainer.handleInput(x,y);
        matchID = MatchContainer.handleInput(x,y);
        if(matchID != -1){
            //state = STATE::Watching;
            network.sendWatchGameRequest(matchID); //matchID
            cout << "Match ID: " << matchID << endl;
            game.reset(1, 300, 0, ranked);
            //spectator.run(state);
        }
    }
    else if(invited || invite.inviteRejected || waitingForGame){
        if(waitingForGame && exitQueueButton.clicked(x, y)){
            network.sendExitQueue();
            waitingForGame = false;
            warnings.setString("");
        }
        if(invite.handleInput(x, y) == false){ //invite rejected
            cout << "Invite rejected" << endl;
            network.sendInviteRejection(invite.name);
            invited = false;
        }
        else{
            cout << "Invite accepted" << endl;
        }
    }
    else{
        if(inviteRequest.handleInput(x, y)){
            //cout << "Invite" << endl;
        }
    }

}
