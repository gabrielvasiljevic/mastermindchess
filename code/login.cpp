#include <SFML/Graphics.hpp>
#include "headers/login.h"
#include "headers/md5.h"
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>


int port;
int console;
int myColor = 1;

using namespace std;

void centralize(sf::Text& text){
    text.setPosition(470 - text.getGlobalBounds().width/2, text.getPosition().y);
}

Login::Login(sf::RenderWindow& window):
                                        mainWindow(window), //x, y, size x, size y, title, text x, text y
                                        _register(window),
                                        userInputBox(400, 300, 150, 25, "Login", 460, 270, 0),
                                        passwordInputBox(400, 370, 150, 25, "Password", 445, 340, 0),
                                        serverInputBox(375, 440, 200, 34, "Server", 454, 410, 2),
                                        registerButton(370, 480, 100, 70, "", "registerButton", ButtonStyle::NoText),
                                        loginButton(480, 480, 100, 45, "", "loginButton", ButtonStyle::NoText){

    serverBuffer = configurationDAO.getServer();
    port = configurationDAO.getPort();
    console = configurationDAO.getConsole();
    userBuffer = configurationDAO.getUser();


    if(!console){
        FreeConsole();
    }
    serverInputBox.inputText.setString(serverInputBox.getLastLetters(serverBuffer, 30));
    userInputBox.inputText.setString(userInputBox.getLastLetters(userBuffer, 30));
    passwordInputBox.inputText.setString("");


    this->font.loadFromFile("media/fonts/AGENCYB.TTF");
    this->userAlert.setFont(this->font);
    this->userAlert.setPosition(450, 610);
    this->userAlert.setString("");
    this->userAlert.setCharacterSize(20U);

    userInputBox.select();
    this->backgroundTexture = new sf::Texture();

    this->backgroundTexture->loadFromFile("media/images/bg2.jpg");
    this->background.setTexture(*this->backgroundTexture);

    this->loginBG.setTexture(*Textures::loginBG);
    this->loginBG.setPosition(350, 260);
    this->secretPass = "";
    this->passwordBuffer = "";
}

void Login::run(STATE& state){
    packetID receive;
    while (mainWindow.isOpen() && state == STATE::Login){
        sf::Event event;
        while (mainWindow.pollEvent(event)){
            handleEvent(event, state);
        }
        receive = network.receive();
        switch(receive){
            case packetID::LoginResponse:
                if(network.receiveLoginResponse()){
                    cout << "Login successful!" << endl;
                    configurationDAO.setServer(serverBuffer);
                    configurationDAO.setUser(userBuffer);
                    state = STATE::Lobby;
                }
                else{
                    cout << "Incorrect login..." << endl;
                    userAlert.setString("Incorrect login...");
                    alertClock.restart();
                }
            break;
            case packetID::WrongVersion:
                cout << "You have an outdated version of the game. Please download the latest version." << endl;
                userAlert.setString("You have an outdated version of the game. Please download the latest version.");
                centralize(userAlert);
                alertClock.restart();
            break;
        }
        mainWindow.clear(sf::Color(0, 150, 255));
        //window.clear(sf::Color(0, 0, 0));
        draw();
        mainWindow.display();
    }
    if(state == STATE::Register){
        _register.run(state);
    }
}

void Login::draw(){
    int cl = 0;
    cl = 255 - static_cast<int>(alertClock.getElapsedTime().asSeconds()*96);
    if(cl < 0) cl = 0;
    if(cl > 255) cl = 0;
    userAlert.setColor(sf::Color(255, 0, 0, cl));
    mainWindow.draw(background);

    mainWindow.draw(loginBG);
    mainWindow.draw(serverInputBox.background);
    mainWindow.draw(userInputBox.background);
    mainWindow.draw(passwordInputBox.background);



    mainWindow.draw(userInputBox.text);
    mainWindow.draw(passwordInputBox.text);
    mainWindow.draw(serverInputBox.text);

    mainWindow.draw(userInputBox.inputText);
    mainWindow.draw(passwordInputBox.inputText);
    mainWindow.draw(serverInputBox.inputText);

    mainWindow.draw(loginButton.image);
    mainWindow.draw(registerButton.image);

    mainWindow.draw(loginButton.text);
    mainWindow.draw(registerButton.text);

    mainWindow.draw(userAlert);

}

void Login::selectBox(){

    userInputBox.deselect();
    passwordInputBox.deselect();
    serverInputBox.deselect();

    switch(selectedBox){
        case 0:
            userInputBox.select();
        break;
        case 1:
            passwordInputBox.select();
        break;
        case 2:
            serverInputBox.select();
        break;
    }
}

void Login::handleEvent(const sf::Event& event, STATE& state){
    char letter;
    switch(event.type){
        case sf::Event::Closed:
            //network.sendDisconnect();
            mainWindow.close();
        break;
        case sf::Event::TextEntered:
            letter = static_cast<char>(event.text.unicode);
            if(letter == '\t'){
                selectedBox++;
                selectedBox %= 3;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
                tryToConnect();
            }
            else{
                switch(selectedBox){
                    case 0: //username
                        if(letter != '\b'){
                            if(userBuffer.size() < 15){
                                userBuffer.push_back(letter);
                                userInputBox.inputText.setString(userBuffer + "|");
                            }
                        }
                        else if(userBuffer.size() > 0){
                            userBuffer.pop_back();
                            userInputBox.inputText.setString(userBuffer + "|");
                        }
                    break;
                    case 1: //password
                        if(letter != '\b'){
                            if(passwordBuffer.size() < 15){
                               passwordBuffer.push_back(letter);
                                secretPass = secretPass + "*";
                                passwordInputBox.inputText.setString(secretPass + "|");
                            }
                        }

                        else if(passwordBuffer.size() > 0){
                            passwordBuffer.pop_back();
                            secretPass.pop_back();
                            passwordInputBox.inputText.setString(secretPass + "|");
                        }
                    break;
                    case 2: //server
                        if(letter != '\b'){
                            if(serverBuffer.size() < 64){
                                serverBuffer.push_back(letter);
                                serverInputBox.inputText.setString(serverInputBox.getLastLetters(serverBuffer, 30) + "|");
                            }

                        }
                        else if(serverBuffer.size() > 0){
                            serverBuffer.pop_back();
                            serverInputBox.inputText.setString(serverInputBox.getLastLetters(serverBuffer, 30) + "|");
                        }
                    break;
                }
            }
        break;
        case sf::Event::MouseButtonPressed:
            int x = event.mouseButton.x;
            int y = event.mouseButton.y;

            if(userInputBox.clicked(x, y)){
                selectedBox = 0;
            }
            else if(passwordInputBox.clicked(x, y)){
                selectedBox = 1;
            }
            else if(serverInputBox.clicked(x, y)){
                selectedBox = 2;
            }
            else if(loginButton.clicked(x, y)){
                tryToConnect();
            }
            else if(registerButton.clicked(x, y)){
                state = STATE::Register;
            }
        break;
    }
    selectBox();
}

void Login::tryToConnect(){
    if(userBuffer.size() > 0){
        if(passwordBuffer.size() > 0){
            cout << "Please wait..." << endl;
            userAlert.setString("Please wait...");
            centralize(userAlert);
            alertClock.restart();

            //    network.verifyVersion(VERSION);
            bool response = false, Color = false;
            string answer;
            if(network.connect(serverBuffer, port)){
                network.sendLogin(userBuffer, md5(passwordBuffer), VERSION);
            }

            else{
                userAlert.setString("Could not connect to server");
                centralize(userAlert);
                alertClock.restart();
            }


        }
        else{
            userAlert.setString("Input your password!");
            centralize(userAlert);
            alertClock.restart();
            cout << "Input your password!" << endl;
        }

    }
    else{
        userAlert.setString("Input a username!");
        centralize(userAlert);
        alertClock.restart();
        cout << "Input a username!" << endl;
    }
}


