#ifndef GAME
#define GAME
#include <iostream>
#include "board.h"
#include "checkbox.h"
#include "checkmate.h"
#include "turnIndicator.h"
#include "networkHandler.h"
#include "dataTypes.h"





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
        Checkbox Hint;
        matchHistory history;
        CheckMate testCheck;
        NetworkHandler &network;
        turnIndicator TurnIndicator;
        sf::Sprite board;
        sf::Sprite background;
        sf::Texture* backgroundTexture;
        sf::Texture* boardTexture;
        sf::RenderWindow &mainWindow;
        int i, j, iPiece, jPiece;
        int turn, myColor, moveCount;
        bool check;
        bool enemyCheck;
        bool checkMate;
        bool HandleInput(int x, int y);
        void handleEvent(const sf::Event& event, STATE& state);
        void draw();
        void Initialize_Texture(Piece pieces[8][8]);
        void logCheck();
        void logMove(int i, int j, int iP, int jP);
        void logCapture(int i, int j, int iP, int jP);
        void makeEnemyMove(int i, int j, int iP, int jP);
        int Run(STATE& state);

        Game(sf::RenderWindow& window, NetworkHandler &mainNetwork, int color);
        Game(sf::RenderWindow &window, NetworkHandler &mainNetwork);
};


#endif // GAME
