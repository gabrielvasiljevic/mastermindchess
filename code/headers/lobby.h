#ifndef _LOBBY
#define _LOBBY
#include "inputBox.h"
#include "button.h"
#include "game.h"
#include "capablanca.h"
#include "networkHandler.h"
#include "dataTypes.h"
#include "playerListContainer.h"

class Lobby{
    public:
        sf::Sprite background;
        sf::Texture* backgroundTexture;
        sf::Text warnings;
        sf::Font warningFont;
        sf::RenderWindow &mainWindow;
        NetworkHandler &network;
        Game game;
        Capablanca capagame;
        Button playButton;
        Button playCapaButton;
        Button play960Button;
        playerListContainer PlayerListContainer;
        void handleEvent(const sf::Event& event, STATE& state);
        void draw();
        void tryToConnect();
        void waitForGame();
        void keepConnectionAlive();
        void run(STATE& state);
        Lobby(sf::RenderWindow& window, NetworkHandler& network);
};


#endif // _LOBBY
