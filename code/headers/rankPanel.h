#ifndef _RANKPANEL
#define _RANKPANEL

#include <SFML/Graphics.hpp>
#include "button.h"

#define SIZE_X 127
#define SIZE_Y 1


class rankPanel{
    public:
        int x, y;
        int elo;
        int numberOfMatches;
        int pos;
        bool visible;
        std::string name;
        std::string vld;

        sf::Font font;
        sf::Text playerName;
        sf::Text playerELO;
        sf::Text playerRank;
        sf::Text playerVLD;

        sf::Sprite background;
        sf::Sprite status;
        sf::Sprite flag;
        sf::Sprite prize;

        sf::Texture* backgroundTexture;
        sf::Texture* offlineTexture;
        sf::Texture* playingTexture;
        sf::Texture* onlineTexture;
        sf::Texture* flagTexture;

        sf::RectangleShape square;
        sf::FloatRect rectSquare;

        Button viewProfile;

        void setName(std::string name);
        void setColor(std::string recordColor);
        void draw(sf::RenderWindow& window, statusID status);
        void refresh();
        void update(int x, int y, statusID status);
        void swap(rankPanel& other);
        rankPanel();
        rankPanel& operator=(const rankPanel& other){
            rankPanel temp(other);
            swap(temp);
            return *this;
        }
};


#endif // _RANKPANEL



