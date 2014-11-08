#include "headers/playerRankContainer.h"
#include <math.h>

#define PLAYERS_PER_PAGE 8

using namespace std;

playerRankContainer::playerRankContainer(int x, int y, int size_x, int size_y) : Interface_Element(x, y, size_x, size_y),
                                                                                 backButton(x + 100, y + 5, 15, 15, "", "scrollBack", ButtonStyle::NoText),
                                                                                 nextButton(x + 164, y + 5, 15, 15, "", "scrollNext", ButtonStyle::NoText){
    this->square.setFillColor(sf::Color::Transparent);
    this->initial_player = 0;
    this->final_player = PLAYERS_PER_PAGE;
    this->pos_x = x;
    this->pos_y = y;
    this->font.loadFromFile("media/fonts/AGENCYB.TTF");

    this->text.setFont(this->font);
    this->text.setString("Rank");
    this->text.setPosition(pos_x + 60, pos_y+5);
    this->text.setCharacterSize(20U);

    pages.setFont(font);
    pages.setString("(1/1)");
    pages.setPosition(x + 125, y + 5);
    pages.setCharacterSize(15U);
    refresh();
}



void playerRankContainer::handleInput(int x, int y){
    if(backButton.clicked(x, y)){
        scrollBack();
    }
    if(nextButton.clicked(x, y)){
        scrollNext();
    }
}

void playerRankContainer::sortRank(){
    int i = 0;
    rankPanel temp;
    while(i < playerList.size()){
        if(i == 0 || playerList[i]->elo <= playerList[i-1]->elo){
            i++;
        }
        else{
            temp = *playerList[i];
            *playerList[i] = *playerList[i-1];
            *playerList[i-1] = temp;
            i--;
        }
    }
}

void playerRankContainer::scrollBack(){
    if(initial_player - 8 >= 0){
        final_player = initial_player;
        initial_player -= 8;
        refresh();
    }
}

void playerRankContainer::scrollNext(){
    int cap = final_player + 8;
    if(cap > playerList.size())
        cap = playerList.size();
    while(final_player < cap && cap <= playerList.size()){
        final_player++;
    }
    if(initial_player + 8 <= final_player)
        initial_player += 8;
    refresh();
}

void playerRankContainer::draw(sf::RenderWindow& window){
    window.draw(square);
    window.draw(backButton.image);
    window.draw(pages);
    window.draw(nextButton.image);
    window.draw(text);
    int i;
    for(i = initial_player; i < final_player; i++){
        if(playerList.size() > 0){
            if(i < playerList.size()){
                if(playerList[i]->visible){
                    playerList[i]->draw(window, playersInfo[i].status);
                }
            }
        }
    }
}

void playerRankContainer::refresh(){
    int i, x, y;
    for(i = initial_player, y = 0, x = 0; i < playerList.size(); i++, x++){
        if(playerList.size() > 0 && i <= final_player){
            if((x + 1)%5 == 0){
                y++;
                x = 0;
            }
            playerList[i]->visible = true;
            playerList[i]->update(pos_x + 64 + 180*x, pos_y + 50 + 130*y, playersInfo[i].status);
        }
    }
    updatePagination();
}

void playerRankContainer::updatePagination(){
    int initial_page, final_page;

    initial_page = initial_player/PLAYERS_PER_PAGE + 1; //always a multiple of players_per_page
    final_page = ceil(static_cast<double>(playerList.size())/PLAYERS_PER_PAGE);

    pages.setString("(" + to_string(initial_page) + "/" + to_string(final_page) + ")");

}

void playerRankContainer::receiveList(std::vector<userInfo> serverPlayerList){
    int i, match_count = 0;
    userInfo player;

    for(i = 0; i < serverPlayerList.size(); i++){
        if(i + 1 > this->playerList.size()){
            playersInfo.emplace_back();
            player.nickname     = serverPlayerList[i].nickname;
            player.currentElo   = serverPlayerList[i].elo[0][0];
            player.currentVLD   = to_string(serverPlayerList[i].victories[0][0]) + "/"
                                   + to_string(serverPlayerList[i].defeats[0][0]) + "/"
                                   + to_string(serverPlayerList[i].draws[0][0]);

            for(int j = 0; j < 3; j++){
                for(int k = 0; k < 3; k++){
                    player.elo[j][k] = serverPlayerList[i].elo[j][k];
                    player.victories[j][k] = serverPlayerList[i].victories[j][k];
                    player.defeats[j][k] = serverPlayerList[i].defeats[j][k];
                    player.draws[j][k] = serverPlayerList[i].draws[j][k];
                }
            }

            match_count   = serverPlayerList[i].victories[0][0] +
                            serverPlayerList[i].defeats[0][0] +
                                  serverPlayerList[i].draws[0][0];

            player.status = static_cast<statusID>(serverPlayerList[i].status);

            playersInfo[i] = player;


            this->playerList.emplace_back(new rankPanel());
            this->playerList[i]->numberOfMatches = match_count;
            this->playerList[i]->name = player.nickname;
            this->playerList[i]->elo = player.currentElo;
            this->playerList[i]->vld = player.currentVLD;
            this->playerList[i]->pos = i + 1;
        }
        else{
            playersInfo[i].status = static_cast<statusID>(serverPlayerList[i].status);
        }
    }
    sortRank();
    refresh();
}

void playerRankContainer::setCurrentElo(int time, int gameMode){
    int i;
    for(i = 0; i < playerList.size(); i++){
        this->playerList[i]->elo = playersInfo[i].elo[gameMode][time/900];
        this->playerList[i]->vld = to_string(playersInfo[i].victories[gameMode][time/900]) + "/"
                                 + to_string(playersInfo[i].defeats[gameMode][time/900]) + "/"
                                 + to_string(playersInfo[i].draws[gameMode][time/900]);
        this->playerList[i]->numberOfMatches = playersInfo[i].victories[gameMode][time/900] +
                                               playersInfo[i].defeats[gameMode][time/900] +
                                               playersInfo[i].draws[gameMode][time/900];
    }
    sortRank();
    refresh();
}

void playerRankContainer::setRecordColor(string recordColor){
    for(int i = 0; i < playerList.size(); i++){
        playerList[i]->setColor(recordColor);
    }
}
