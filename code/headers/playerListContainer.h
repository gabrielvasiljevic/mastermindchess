#ifndef _PLCONTAINER
#define _PLCONTAINER
#include "playerPanel.h"
#include "button.h"

class playerListContainer : public Interface_Element{
    public:
        std::vector<playerPanel*> playerList;
        std::vector<userInfo> playersInfo;
        int pos_x, pos_y;

        Button scrollDownButton;
        Button scrollUpButton;

        int initial_player;
        int final_player;
        int listSize;

        void draw(sf::RenderWindow& window);
        void receiveList(std::vector<userInfo> playerlist);
        void refresh();
        void scrollDown();
        void scrollUp();
        void handleInput(int x, int y);
        playerListContainer(int x, int y, int size_x, int size_y);
};


#endif // _PLCONTAINER


