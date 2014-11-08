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
        sf::Text eloDiff;
        sf::Text matchDuration;
        sf::Font warningFont;
        sf::RenderWindow &mainWindow;
        Button backButton;
        Button saveHistoryButton;
        void handleEvent(const sf::Event& event, STATE& state);
        void draw();
        void keepConnectionAlive();
        void run(STATE& state);
        void setWinner(int winner);
        void setEloDifferente(int myElo, int enemyElo, int result);
        void setMatchDuration(int gameTime, int myTime, int enemyTime);
        int calculateELO(int Ra, int Rb, double Sa);
        Gameover(sf::RenderWindow& window);
};


#endif // _GAMEOVER

