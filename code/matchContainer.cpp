#include "headers/matchContainer.h"

#define MATCHES_PER_LINE 3
#define TOTAL_NUMBER_OF_MATCHES 9
#define MATCHES_PER_PAGE 9

using namespace std;

matchContainer::matchContainer(int x, int y, int size_x, int size_y) : Interface_Element(x, y, size_x, size_y),
                                                                        backButton(x + 144, y + 5, 15, 15, "", "scrollBack", ButtonStyle::NoText),
                                                                        nextButton(x + 204, y + 5, 15, 15, "", "scrollNext", ButtonStyle::NoText){
    square.setFillColor(sf::Color::Transparent);
    initial_match = 0;
    final_match = TOTAL_NUMBER_OF_MATCHES - 1;
    pos_x = x;
    pos_y = y;
    font.loadFromFile("media/fonts/AGENCYB.TTF");
    text.setFont(font);
    text.setString("Matches (0)");
    text.setPosition(pos_x + 60, pos_y+5);
    text.setCharacterSize(20U);

    pages.setFont(font);
    pages.setString("(1/1)");
    pages.setPosition(x + 168, y + 5);
    pages.setCharacterSize(15U);

    int j, k;
    for(int i = 0, j = 0, k = 0; i < TOTAL_NUMBER_OF_MATCHES; i++, k++){
        if((k + 1)%(MATCHES_PER_LINE + 1) == 0){
            j++;
            k = 0;
        }
        matchList.emplace_back(new matchPanel(pos_x + 64 + 232*k, pos_y + 44 + 72*j));

    }

    refresh();
}

int matchContainer::handleInput(int x, int y){
    if(backButton.clicked(x, y)){
        scrollBack();
        return -1;
    }
    if(nextButton.clicked(x,y)){
        scrollNext();
        return -1;
    }
    for(int i = 0; i < matchList.size(); i++){
        if(matchList[i]->handleInput(x, y)){
            return matchList[i]->id;
        }
    }
    return -1;
}

void matchContainer::scrollBack(){
    if(initial_match - TOTAL_NUMBER_OF_MATCHES >= 0){
        final_match = initial_match - 1;
        initial_match -= TOTAL_NUMBER_OF_MATCHES;
        refresh();
    }
}

void matchContainer::scrollNext(){
    int cap = final_match + TOTAL_NUMBER_OF_MATCHES;
    if(cap > matchList.size())
        cap = matchList.size(); //set the maximum number of matches

    while(final_match <= cap - 1 && cap <= matchList.size()){
        final_match++;
    }

    if(initial_match + TOTAL_NUMBER_OF_MATCHES <= final_match)
        initial_match += TOTAL_NUMBER_OF_MATCHES;
    refresh();
}

void matchContainer::draw(sf::RenderWindow& window){
    window.draw(square);
    window.draw(backButton.image);
    window.draw(nextButton.image);
    window.draw(text);
    window.draw(pages);
    int i;
    for(i = 0; i < matchList.size(); i++){
        if(matchList[i]->visible){
            matchList[i]->draw(window);
        }
    }
}

void matchContainer::refresh(){
    int i, x = 0;
    for(i = initial_match; i < matchesInfo.size(); i++, x++){
        if(matchesInfo.size() > 0 && i <= final_match){
            matchList[x]->update(matchesInfo[i].status);
        }
    }
    text.setString("Matches (" + to_string(matchesInfo.size()) + ")");
}


void matchContainer::updatePagination(){
    int initial_page, final_page;

    initial_page = initial_match/MATCHES_PER_PAGE + 1; //always a multiple of matches_per_page
    final_page = ceil(static_cast<double>(matchList.size())/MATCHES_PER_PAGE);

    pages.setString("(" + to_string(initial_page) + "/" + to_string(final_page) + ")");

}


void matchContainer::updateList(){
    int i;
    for(i = 0; i < matchList.size(); i++){
        this->matchList[i]->visible = false;
    }
    if(matchesInfo.size() >= initial_match){
        for(i = initial_match; i <= final_match; i++){
            if(i < matchesInfo.size()){
                this->matchList[i%TOTAL_NUMBER_OF_MATCHES]->id        = matchesInfo[i].ID;
                this->matchList[i%TOTAL_NUMBER_OF_MATCHES]->gameType  = matchesInfo[i].gameMode;
                this->matchList[i%TOTAL_NUMBER_OF_MATCHES]->whiteNick = matchesInfo[i].white;
                this->matchList[i%TOTAL_NUMBER_OF_MATCHES]->blackNick = matchesInfo[i].black;
                this->matchList[i%TOTAL_NUMBER_OF_MATCHES]->ranked    = matchesInfo[i].ranked;
                this->matchList[i%TOTAL_NUMBER_OF_MATCHES]->isPublic  = matchesInfo[i].isPublic;
                this->matchList[i%TOTAL_NUMBER_OF_MATCHES]->visible = true;
            }
        }
    }
    refresh();
}

void matchContainer::updateMatchesBG(int gameType){
    int i;
    for(i = 0; i < matchList.size(); i++){
        matchList[i]->updateBG(gameType);
    }
}
