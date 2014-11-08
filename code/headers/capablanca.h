#ifndef _CAPA
#define _CAPA
#include <iostream>
#include "capaboard.h"
#include "chat.h"
#include "history.h"
#include "gameover.h"
#include "checkbox.h"
#include "capacheckmate.h"
#include "turnIndicator.h"
#include "networkHandler.h"
#include "dataTypes.h"

#define TOPPLAYER_X 9
#define TOPPLAYER_Y 3

#define BOTPLAYER_X 9
#define BOTPLAYER_Y 629

#define BOX_X 730
#define BOX_Y 20

#define PAPER_X 755
#define PAPER_Y 445

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

        History         hist;

        Button          giveUpButton;
        Button          OptionsButton;
        Button          ChatButton;

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
        sf::Text        myName;
        sf::Text        enemyClockText;
        sf::Text        enemyName;

        sf::Sprite      board;
        sf::Sprite      background;
        sf::Sprite      outborder;
        sf::Sprite      topPlayer;
        sf::Sprite      botPlayer;
        sf::Sprite      box;
        sf::Sprite      paper;

        sf::Texture*    backgroundTexture;
        sf::Texture*    boardTexture;
        sf::Texture*    outborderTexture;
        sf::Texture*    topPlayerTexture;
        sf::Texture*    botPlayerTexture;
        sf::Texture*    boxTexture;


        sf::RenderWindow &mainWindow;
        int             i, j, iPiece, jPiece;
        int             turn, myColor, moveCount;
        int             userX, userY;
        double          myTime, enemyTime;
        bool            check;
        bool            enemyCheck;
        bool            checkMate;

        void reset       (int gameColor, int gameTime);
        bool keyboardMove(char c);
        bool HandleInput(int x, int y);
        bool processInput(int i, int j);
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


#endif // _CAPA

