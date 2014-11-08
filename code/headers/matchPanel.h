#ifndef _MATCHPANEL
#define _MATCHPANEL

#include <SFML/Graphics.hpp>
#include "button.h"

#define SIZE_X 192
#define SIZE_Y 32


class matchPanel : public Interface_Element{
    public:
        int x, y;
        bool visible;
        int id;
        int gameType;
        bool ranked, isPublic;
        std::string whiteNick;
        std::string blackNick;

        sf::Font font;
        sf::Text whiteName;
        sf::Text blackName;
        sf::Text X;

        sf::Sprite background;
        sf::Sprite borders;
        sf::Sprite closedEye;

        sf::Texture* backgroundTexture;
        sf::Texture* closedEyeTexture;

        sf::RectangleShape square;
        sf::FloatRect rectSquare;

        Button watch;

        void setName(std::string whitename, std::string blackname);
        void draw(sf::RenderWindow& window);
        void refresh();
        void update(int status);
        void updateBG(int gameType);
        bool handleInput(int x, int y);

        matchPanel(int x, int y);
};


#endif // _MATCHPANEL

