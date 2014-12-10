#ifndef GAME
#define GAME
#include <iostream>
#include <SFML/Audio.hpp>
#include "board.h"
#include "chat.h"
#include "history.h"
#include "gameover.h"
#include "checkbox.h"
#include "checkmate.h"
#include "turnIndicator.h"
#include "pieceholder.h"
#include "networkHandler.h"
#include "dataTypes.h"
#include "gesturalModule.h"


struct matchHistory{
    int enemyID;
    std::string date;
    std::string currentMove;
    std::string history;
    matchHistory(){currentMove = ""; history = "";}
};

class Game{
    public:
        Board b;
        Checkbox        Hint;
        Checkbox        Mute;
        matchHistory    history;
        CheckMate       testCheck;
        Gameover        gameover;
        Chat            chat;
        History         hist;
        turnIndicator   TurnIndicator;
        PieceHolder     pieceholder;

        Button          giveUpButton;
        Button          OptionsButton;
        Button          ChatButton;

        sf::Font        font;
        sf::Text        warnings;
        sf::Clock       myClock;
        sf::Clock       enemyClock;
        sf::Clock       warningClock;

        sf::Text        myClockText;
        sf::Text        myName;
        sf::Text        displayELO;
        sf::Text        enemyELO;
        sf::Text        enemyClockText;
        sf::Text        enemyName;
        sf::Text        watching;

        sf::Sprite      board;
        sf::Sprite      capaboard;
        sf::Sprite      background;
        sf::Sprite      outborder;
        sf::Sprite      capaoutborder;
        sf::Sprite      topPlayer;
        sf::Sprite      botPlayer;
        sf::Sprite      box;
        sf::Sprite      bigbox;
        sf::Sprite      myPrize;
        sf::Sprite      enemyPrize;
        sf::Sprite      paper;
        sf::Sprite      gameIcon;
        sf::Sprite      closedEye;

        sf::Texture*    backgroundTexture;
        sf::Texture*    boardTexture;
        sf::Texture*    capaboardTexture;
        sf::Texture*    outborderTexture;
        sf::Texture*    capaoutborderTexture;
        sf::Texture*    topPlayerTexture;
        sf::Texture*    botPlayerTexture;
        sf::Texture*    boxTexture;
        sf::Texture*    bigboxTexture;
        sf::Texture*    paperTexture;
        sf::Texture*    closedEyeTexture;

        sf::SoundBuffer* bipBuffer;
        sf::Sound        bip;

        sf::SoundBuffer* tocBuffer;
        sf::Sound        toc;

        sf::RenderWindow &mainWindow;
        bool            ranked;
        bool            pieceClick;
        int             i, j, iPiece, jPiece;
        int             rows, columns;
        int             userX, userY;
        int             turn, myColor, moveCount;
        int             gametype;
        int             gameTime;
        string          boardStatus[8][10];
        double          myTime, enemyTime;
        int             enemyelo;
        int             isPublic;
        bool            check;
        bool            enemyCheck;
        bool            checkMate;

        void reset              (int gameColor, int gameTime, int gametype, bool ranked);
        bool handleInput        (int x, int y);
        bool processInput       (int x, int y);
        void processMove        (STATE& state);
        void handleEvent        (const sf::Event& event, STATE& state);
        void draw               ();
        void Initialize_Texture (Piece pieces[8][10]);
        void logCheck           ();
        void updateBoardStatus  ();
        bool keyboardMove       (char c);
        void logMove            (int i, int j, int iP, int jP);
        void logCapture         (int i, int j, int iP, int jP);
        void makeEnemyMove      (int i, int j, int iP, int jP);
        int Run                 (STATE& state);

        Game(sf::RenderWindow& window, int color, int gametype);
        Game(sf::RenderWindow &window);
};


#endif // GAME
