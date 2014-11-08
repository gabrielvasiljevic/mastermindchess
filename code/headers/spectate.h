#ifndef _WATCH
#define _WATCH


#include <string>
#include "dataTypes.h"
#include "game.h"
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;

class Spectator{
    public:
        sf::RenderWindow &mainWindow;
        Game game;
        Button exitButton;
        Chat chat;
        int whiteELO, blackELO;

        sf::Texture*    watchingTexture;
        sf::Sprite      watching;
        void run(STATE& state);

        void handleEvent(const sf::Event& event, STATE& state);
        void movePiece(int i, int j, int iP, int jP);
        void updateMatchStatus(string white, string black, int whiteElo, int blackElo, string newBoard[][10], int gameMode);
        void draw();
        Spectator(sf::RenderWindow &window, Game &game, int gametype);
};



#endif // _NET

