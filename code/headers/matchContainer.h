#ifndef _MTCHCONTAINER
#define _MTCHCONTAINER
#include "matchPanel.h"
#include "match.h"
#include "button.h"

#define NUMBER_OF_MATCHES 3
class matchContainer : public Interface_Element{
    public:
        std::vector<matchPanel*> matchList;
        std::vector<Match> matchesInfo;
        int pos_x, pos_y;
        int initial_match;
        int final_match;

        int listSize;

        sf::Text pages;

        Button backButton;
        Button nextButton;


        void draw(sf::RenderWindow& window);
        void updateList();
        void updatePagination();
        void updateMatchesBG(int gameType);

        void refresh();
        void scrollBack();
        void scrollNext();
        int handleInput(int x, int y);
        matchContainer(int x, int y, int size_x, int size_y);
};


#endif // _MTCHCONTAINER


