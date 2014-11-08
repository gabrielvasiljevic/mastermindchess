#ifndef _RKCONTAINER
#define _PRKCONTAINER
#include "rankPanel.h"
#include "button.h"

class playerRankContainer : public Interface_Element{
    public:
        std::vector<rankPanel*> playerList;
        std::vector<userInfo> playersInfo;

        sf::Text pages;

        Button backButton;
        Button nextButton;

        int pos_x, pos_y;
        int initial_player;
        int final_player;
        int listSize;

        void draw(sf::RenderWindow& window);
        void receiveList(std::vector<userInfo> playerlist);
        void refresh();
        void updatePagination();
        void scrollBack();
        void scrollNext();
        void sortRank();
        void handleInput(int x, int y);
        void setRecordColor(std::string recordColor);
        void setCurrentElo(int time, int gameMode);
        playerRankContainer(int x, int y, int size_x, int size_y);
};


#endif // _RKCONTAINER
