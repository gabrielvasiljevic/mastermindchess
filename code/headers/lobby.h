#ifndef _LOBBY
#define _LOBBY
#include "inputBox.h"
#include "button.h"
#include "game.h"
#include "networkHandler.h"
#include "dataTypes.h"
#include "playerListContainer.h"
#include "playerRankContainer.h"
#include "matchContainer.h"
#include "spectate.h"
#include "invite.h"
#include "inviterequest.h"

class Lobby{
    public:
        bool waitingForGame;
        bool invited;
        bool ranked;
        int gameColor;
        int gameTime;
        int gameMode;
        string myName;

        sf::Sprite background;
        sf::Texture* backgroundTexture;

        sf::Sprite BTNbackground;
        sf::Texture* BTNbackgroundTexture;

        sf::Sprite ficha;
        sf::Texture* fichaTexture;

        sf::Sprite myPrize;
        sf::Texture* myPrizeTexture;

        sf::Sprite selectionMark;
        sf::Texture* selectionMarkTexture;

        sf::Sprite selectionUnderMark;
        sf::Texture* selectionUnderMarkTexture;

        sf::Sprite redMark;
        sf::Texture* redMarkTexture;

        sf::Text warnings;
        sf::Text myNick;
        sf::Text myELO;

        sf::Font warningFont;
        sf::RenderWindow &mainWindow;
        Game game;
        Spectator spectator;
        Invite invite;

        Button playButton;
        Button exitQueueButton;

        Checkbox selectClassicButton;
        Checkbox selectCapaButton;
        Checkbox select960Button;

        Checkbox select5minutesButton;
        Checkbox select15minutesButton;
        Checkbox select30minutesButton;

        playerListContainer PlayerListContainer;
        playerRankContainer PlayerRankContainer;
        matchContainer      MatchContainer;

        void handleEvent(const sf::Event& event, STATE& state);
        void handleInput(int x, int y, STATE& state);
        void handleInput(sf::Event::KeyEvent key, STATE& state);
        void draw();
        void tryToConnect();
        void waitForGame();
        void keepConnectionAlive();
        void run(STATE& state);
        Lobby(sf::RenderWindow& window);
};


#endif // _LOBBY
