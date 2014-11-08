#ifndef _PLAYERPANEL
#define _PLAYERPANEL

#include <SFML/Graphics.hpp>
#include "button.h"
#include "networkHandler.h"

#define SIZE_X 150
#define SIZE_Y 54


class playerPanel{
    public:

        int x, y;
        bool visible;
        std::string name;

        sf::Font font;
        sf::Text playerName;

        sf::Sprite background;
        sf::Sprite status;
        sf::Sprite flag;


        sf::Texture* backgroundTexture;
        sf::Texture* offlineTexture;
        sf::Texture* playingTexture;
        sf::Texture* onlineTexture;
        sf::Texture* flagTexture;


        sf::RectangleShape square;
        sf::FloatRect rectSquare;

        Button invite;
        Button add;
        Button viewProfile;
        Button watch;

        void setName(std::string name);
        void draw(sf::RenderWindow& window, statusID status);
        void handleInput(int x, int y);
        void refresh();
        void update(int x, int y, statusID status);

        playerPanel();
};


#endif // _PLAYERPANEL


