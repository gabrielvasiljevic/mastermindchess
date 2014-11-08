#ifndef _HIST
#define _HIST
#include "GUI.h"
#include "networkHandler.h"
#include <iostream>
#include "chat.h"
#include "button.h"
#include <deque>

class History{
    public:
        std::size_t historyLength;
        float height;
        float length;
        int charSize;
        int moveNumber;
        int histNumber;
        int posNumber;
        int initialMove;
        bool chatOn;

        sf::Sprite image;
        sf::Sprite waterMark;

        sf::Texture* texture;
        sf::Texture* chatTexture;
        sf::Texture* waterMarkTexture;
        sf::Font histFont;

        sf::Text historyText;

        sf::RectangleShape histBox;
        sf::FloatRect rectHistBox;

        Button scrollBackButton;
        Button scrollNextButton;

        std::vector<std::string> history;

        void scrollBack();
        void scrollNext();
        void reset(int gameType, int gameTime);
        void draw(sf::RenderWindow & window);
        void putMove(string Move);
        void handleInput(int x, int y);
        History(int x, int y, int size_x, int size_y);
};


#endif // _HIST
