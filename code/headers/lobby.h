#ifndef _LOBBY
#define _LOBBY
#include "inputBox.h"
#include "button.h"
#include "game.h"
#include "networkHandler.h"
#include "dataTypes.h"

class Lobby{
    public:
        sf::Sprite background;
        sf::Texture* backgroundTexture;
        sf::Text warnings;
        sf::Font warningFont;
        sf::RenderWindow &mainWindow;
        NetworkHandler &network;
        Game game;
        Button playButton;
        void handleEvent(const sf::Event& event);
        void draw();
        void tryToConnect();
        void waitForGame();
        void keepConnectionAlive();
        void run(STATE& state);
        Lobby(sf::RenderWindow& window, NetworkHandler& network);
};


#endif // _LOBBY
