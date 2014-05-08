#include "headers/playerListContainer.h"

using namespace std;

playerListContainer::playerListContainer(int x, int y, int size_x, int size_y) : Interface_Element(x, y, size_x, size_y),
                                                                                 scrollDownButton(x + size_x - 20, y + size_y - 20, 15, 15, "", ButtonStyle::smallDown),
                                                                                 scrollUpButton(x + size_x - 20, y, 15, 15, "", ButtonStyle::smallUp){
    this->square.setFillColor(sf::Color::Black);
    this->initial_player = 0;
    this->final_player = 3;
    this->pos_x = x;
    this->pos_y = y;
    this->font.loadFromFile("media/fonts/AGENCYB.TTF");
    this->text.setFont(this->font);
    this->text.setString("Userlist");
    this->text.setPosition(pos_x + 60, pos_y+5);
    this->text.setCharacterSize(20U);
    refresh();
}

void playerListContainer::handleInput(int x, int y){
    if(scrollDownButton.clicked(x, y)){
        scrollDown();
    }
    if(scrollUpButton.clicked(x,y)){
        scrollUp();
    }
}

void playerListContainer::refresh(){
    int i;
    for(i = initial_player; i < playerList.size(); i++){
        if(playerList.size() > 0){
            playerList[i]->visible = true;
            playerList[i]->update(pos_x, pos_y + 30 + 60*i, playersInfo[i].status);
        }
    }
}

void playerListContainer::draw(sf::RenderWindow& window){
    window.draw(square);
    window.draw(scrollDownButton.image);
    window.draw(scrollUpButton.image);
    window.draw(text);
    int i;
    for(i = initial_player; i < final_player; i++){
   // for(i = initial_player; i < playerList.size(); i++){
        if(playerList.size() > 0){
            if(final_player <= playerList.size()){
                if(playerList[i]->visible){
                    playerList[i]->draw(window, playersInfo[i].status);
                }
            }
        }
    }
}

void playerListContainer::scrollDown(){
    if(final_player + 1 < playerList.size()){
        final_player++;
        initial_player++;
    }
}

void playerListContainer::scrollUp(){
    if(initial_player - 1 >= 0){
        initial_player--;
        final_player--;
    }
}

void playerListContainer::receiveList(std::vector<userInfo> playerList){
    int i;
    userInfo player;

    for(i = 0; i < playerList.size(); i++){
        if(playersInfo.size() < playerList.size()){
            player.nickname = playerList[i].nickname;
            player.status = playerList[i].status;
            playersInfo.emplace_back(player);
            this->playerList.emplace_back(new playerPanel());
            this->playerList[i]->name = player.nickname;
        }
        else{

            playersInfo[i].status = playerList[i].status;
        }
    }
    refresh();
}
