#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <fstream>


#include "headers/board.h"
#include "headers/checkbox.h"
#include "headers/game.h"
#include "headers/networkHandler.h"
#include "headers/login.h"
#include "headers/lobby.h"
#include "headers/dataTypes.h"
#include "headers/gesturalModule.h"

using namespace std;
using namespace sf;

sf::RenderWindow window(sf::VideoMode(933, 700), "MasterMind Chess", sf::Style::Close);

STATE state = STATE::Login;

//Packet packet;

TcpSocket server;

string ip;
int enemyID = -1;
int optColor = 1;
bool check;
sf::Text temporary;
sf::Font tempfont;

void loadTextures();


int main(){

    sf::Image icon;
    icon.loadFromFile("media/images/icons/knightIcon.png");
    window.setIcon(256, 256, icon.getPixelsPtr());
    gesturalModule.connectToApplication();
    loadTextures();
    Login login(window);
    Lobby lobby(window);
    //Game game(window, 1, 1);

    //while (gesturalModule.listener.listen (14293) != Socket::Done);

    while (window.isOpen()){
        sf::Event event;
        if(state == STATE::Login){
            login.run(state);
        }

        if(state == STATE::Lobby){
            lobby.run(state);
        }
    }
    return 0;
}

    sf::Texture* Textures::blanks          = new sf::Texture();
    sf::Texture* Textures::bronzeMedal     = new sf::Texture();
    sf::Texture* Textures::silverMedal     = new sf::Texture();
    sf::Texture* Textures::goldMedal       = new sf::Texture();
    sf::Texture* Textures::bronzeTrophy    = new sf::Texture();
    sf::Texture* Textures::silverTrophy    = new sf::Texture();
    sf::Texture* Textures::goldTrophy      = new sf::Texture();
    sf::Texture* Textures::inputBox        = new sf::Texture();
    sf::Texture* Textures::largeInputBox   = new sf::Texture();
    sf::Texture* Textures::loginBG         = new sf::Texture();
    sf::Texture* Textures::invitationPaper = new sf::Texture();

    sf::Texture* Textures::classicPaper    = new sf::Texture();
    sf::Texture* Textures::fischerPaper    = new sf::Texture();
    sf::Texture* Textures::capaPaper       = new sf::Texture();
    sf::Texture* Textures::chatPaper       = new sf::Texture();

    sf::Texture* Textures::blueMatch    = new sf::Texture();
    sf::Texture* Textures::yellowMatch    = new sf::Texture();
    sf::Texture* Textures::redMatch       = new sf::Texture();
    sf::Texture* Textures::whiteMatch       = new sf::Texture();

    sf::Texture* Textures::water5       = new sf::Texture();
    sf::Texture* Textures::water15      = new sf::Texture();
    sf::Texture* Textures::water30      = new sf::Texture();

    sf::Texture* Textures::classic5icon       = new sf::Texture();
    sf::Texture* Textures::classic15icon      = new sf::Texture();
    sf::Texture* Textures::classic30icon      = new sf::Texture();

    sf::Texture* Textures::fischer5icon       = new sf::Texture();
    sf::Texture* Textures::fischer15icon      = new sf::Texture();
    sf::Texture* Textures::fischer30icon      = new sf::Texture();


    sf::Texture* Textures::capa5icon       = new sf::Texture();
    sf::Texture* Textures::capa15icon      = new sf::Texture();
    sf::Texture* Textures::capa30icon      = new sf::Texture();

void loadTextures(){
        Textures::bronzeMedal->loadFromFile("media/images/prizes/bronzeMedalS.png");
        Textures::bronzeTrophy->loadFromFile("media/images/prizes/bronzeTrophyS.png");

        Textures::silverMedal->loadFromFile("media/images/prizes/silverMedalS.png");
        Textures::silverTrophy->loadFromFile("media/images/prizes/silverTrophyS.png");

        Textures::goldMedal->loadFromFile("media/images/prizes/goldMedalS.png");
        Textures::goldTrophy->loadFromFile("media/images/prizes/goldTrophyS.png");

        Textures::inputBox->loadFromFile("media/images/inputBG.png");
        Textures::largeInputBox->loadFromFile("media/images/largeInputBG.png");
        Textures::loginBG->loadFromFile("media/images/loginBG.png");
        Textures::invitationPaper->loadFromFile("media/images/invitePaper.png");

        Textures::classicPaper->loadFromFile("media/images/papers/bluepaper.png");
        Textures::fischerPaper->loadFromFile("media/images/papers/yellowpaper.png");
        Textures::capaPaper->loadFromFile("media/images/papers/redpaper.png");
        Textures::chatPaper->loadFromFile("media/images/papers/chatpaper.png");

        Textures::blueMatch->loadFromFile("media/images/bluematch.png");
        Textures::yellowMatch->loadFromFile("media/images/yellowmatch.png");
        Textures::redMatch->loadFromFile("media/images/redmatch.png");
        Textures::whiteMatch->loadFromFile("media/images/whitematch.png");

        Textures::water5->loadFromFile("media/images/watermarks/water5.png");
        Textures::water15->loadFromFile("media/images/watermarks/water15.png");
        Textures::water30->loadFromFile("media/images/watermarks/water30.png");

        Textures::classic5icon->loadFromFile("media/images/icons/classic5icon.png");
        Textures::classic15icon->loadFromFile("media/images/icons/classic15icon.png");
        Textures::classic30icon->loadFromFile("media/images/icons/classic30icon.png");

        Textures::fischer5icon->loadFromFile("media/images/icons/fischer5icon.png");
        Textures::fischer15icon->loadFromFile("media/images/icons/fischer15icon.png");
        Textures::fischer30icon->loadFromFile("media/images/icons/fischer30icon.png");

        Textures::capa5icon->loadFromFile("media/images/icons/capa5icon.png");
        Textures::capa15icon->loadFromFile("media/images/icons/capa15icon.png");
        Textures::capa30icon->loadFromFile("media/images/icons/capa30icon.png");

}



