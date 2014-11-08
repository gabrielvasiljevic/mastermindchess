#include "headers/playerListContainer.h"

using namespace std;

playerListContainer::playerListContainer(int x, int y, int size_x, int size_y) :
                                        Interface_Element(x, y, size_x, size_y),
                                        scrollDownButton(x + size_x - 20, y + 32,   15, 15, "", "scrollDown", ButtonStyle::NoText),
                                        scrollUpButton  (x + size_x - 20, y,        15, 15, "", "scrollUp", ButtonStyle::NoText){
    square.setFillColor(sf::Color::Transparent);
    initial_player = 0;
    final_player = 10;
    pos_x = x;
    pos_y = y;
    totalOnline = 0;
    font.loadFromFile("media/fonts/AGENCYB.TTF");
    text.setFont(font);
    text.setString("Online Users (" + to_string(totalOnline) + ")");
    text.setPosition(pos_x + 36, pos_y + 5);
    text.setCharacterSize(20U);
    refresh();
}

void playerListContainer::handleInput(int x, int y){
    if(scrollDownButton.clicked(x, y)){
        scrollDown();
    }
    if(scrollUpButton.clicked(x,y)){
        scrollUp();
    }
    for(int i = 0; i < playerList.size(); i++){
        playerList[i]->handleInput(x, y);
    }
}

void playerListContainer::refresh(){
    int i, x;
    totalOnline = 0;
    for(x = 0, i = initial_player; i < playerList.size(); i++){
        if(playerList.size() > 0 && i <= final_player){
            if(playersInfo[i].status != statusID::offline){ //only show online players
                playerList[i]->visible = true;
                playerList[i]->update(pos_x, pos_y + 32 + 64*x++, playersInfo[i].status);
                totalOnline++;
            }
        }
    }
    text.setString("Online Users (" + to_string(totalOnline) + ")");
}

void playerListContainer::draw(sf::RenderWindow& window){
    window.draw(square);
    window.draw(scrollDownButton.image);
    window.draw(scrollUpButton.image);
    window.draw(text);
    int i;
    for(i = initial_player; i < final_player; i++){
        if(playerList.size() > 0 && i < playerList.size()){
            if(playerList[i]->visible){
                playerList[i]->draw(window, playersInfo[i].status);
            }
        }
    }
}

void playerListContainer::scrollDown(){
    if(final_player + 1 < playerList.size() && final_player + 1 <= totalOnline){
        final_player++;
        initial_player++;
        refresh();
    }
}

void playerListContainer::scrollUp(){
    if(initial_player - 1 >= 0){
        initial_player--;
        final_player--;
    }
}

void playerListContainer::receiveList(std::vector<userInfo> serverPlayerList){
    int i;
    userInfo player;

    for(i = 0; i < serverPlayerList.size(); i++){
        if(i + 1 > this->playerList.size()){
            playersInfo.emplace_back();

            player.nickname        = serverPlayerList[i].nickname;
            player.currentElo      = serverPlayerList[i].elo[0][0];
            player.currentVLD      = to_string(serverPlayerList[i].victories[0][0])
                                   + to_string(serverPlayerList[i].defeats[0][0])
                                   + to_string(serverPlayerList[i].draws[0][0]);
            for(int j = 0; j < 3; j++){
                for(int k = 0; k < 3; k++){
                    player.elo[j][k] = serverPlayerList[i].elo[j][k];
                    player.victories[j][k] = serverPlayerList[i].victories[j][k];
                    player.defeats[j][k] = serverPlayerList[i].defeats[j][k];
                    player.draws[j][k] = serverPlayerList[i].draws[j][k];
                }
            }
            player.status   = static_cast<statusID>(serverPlayerList[i].status);
            playersInfo[i] = player;
            this->playerList.emplace_back(new playerPanel());
            this->playerList[i]->name = player.nickname;
        }
        else{
            playersInfo[i].status = static_cast<statusID>(serverPlayerList[i].status);
        }
    }
    refresh();
}
