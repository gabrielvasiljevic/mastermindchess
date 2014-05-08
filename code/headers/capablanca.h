#ifndef CAPA
#define CAPA
#include <iostream>
#include "capaboard.h"
#include "chat.h"
#include "gameover.h"
#include "checkbox.h"
#include "capacheckmate.h"
#include "turnIndicator.h"
#include "networkHandler.h"
#include "dataTypes.h"


struct matchCapaHistory{
    int enemyID;
    std::string date;
    std::string currentMove;
    std::string history;
    matchCapaHistory(){currentMove = ""; history = "";}
};

class Capablanca{
    public:
        Capaboard b;
        Checkbox        Hint;
        matchCapaHistory    history;
        CapaCheckMate   testCheck;
        Gameover        gameover;
        Chat            chat;
        NetworkHandler  &network;
        turnIndicator   TurnIndicator;
        sf::Font        font;
        sf::Text        warnings;
        sf::Clock       myClock;
        sf::Clock       enemyClock;
        sf::Text        myClockText;
        sf::Text        enemyClockText;
        sf::Sprite      board;
        sf::Sprite      background;
        sf::Texture*    backgroundTexture;
        sf::Texture*    boardTexture;
        sf::RenderWindow &mainWindow;
        int             i, j, iPiece, jPiece;
        int             turn, myColor, moveCount;
        double          myTime, enemyTime;
        bool            check;
        bool            enemyCheck;
        bool            checkMate;

        bool HandleInput(int x, int y);
        void handleEvent(const sf::Event& event, STATE& state);
        void draw();
        void Initialize_Texture(capapiece pieces[8][10]);
        void logCheck();
        void logMove(int i, int j, int iP, int jP);
        void logCapture(int i, int j, int iP, int jP);
        void makeEnemyMove(int i, int j, int iP, int jP);
        int Run(STATE& state);

        Capablanca(sf::RenderWindow& window, NetworkHandler &mainNetwork, int color);
        Capablanca(sf::RenderWindow &window, NetworkHandler &mainNetwork);
};


#endif // CAPA

