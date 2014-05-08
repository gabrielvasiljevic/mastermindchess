#ifndef _GAMEOVER
#define _GAMEOVER
#include "inputBox.h"
#include "button.h"
#include "networkHandler.h"
#include "dataTypes.h"

class Gameover{
    public:
        sf::Sprite background;
        sf::Texture* backgroundTexture;
        sf::Text warnings;
        sf::Font warningFont;
        sf::RenderWindow &mainWindow;
        NetworkHandler &network;
        Button backButton;
        Button saveHistoryButton;
        void handleEvent(const sf::Event& event, STATE& state);
        void draw();
        void keepConnectionAlive();
        void run(STATE& state);
        void setWinner(int winner);
        Gameover(sf::RenderWindow& window, NetworkHandler& network);
};


#endif // _GAMEOVER

