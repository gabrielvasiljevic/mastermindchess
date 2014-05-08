#include <SFML/Graphics.hpp>
#include "headers/login.h"
#include <iostream>
#include <string>
#include <fstream>

#define VERSION "0.1.5"

std::string secretPass = "";
std::string configBuffer;
int port;
int myColor = 1;
bool waitingForGame = false;
using namespace std;

Login::Login(sf::RenderWindow& window, NetworkHandler& network):
                                        mainWindow(window), //x, y, size x, size y, title, text x, text y
                                        network(network),
                                        _register(window, network),
                                        userInputBox(400, 300, 150, 25, "Login", 460, 270),
                                        passwordInputBox(400, 370, 150, 25, "Password", 445, 340),
                                        serverInputBox(375, 440, 200, 25, "Server", 454, 410),
                                        registerButton(370, 480, 100, 70, "Register", ButtonStyle::Dark),
                                        loginButton(480, 480, 100, 70, "Login", ButtonStyle::Dark){
    ifstream config {"config.dat"};
    if (config.is_open()){
        getline(config, serverBuffer, ';');
        config >> port;
    }
    serverInputBox.inputText.setString(serverBuffer);

    this->backgroundTexture = new sf::Texture();

    this->backgroundTexture->loadFromFile("media/images/bg1.jpg");
    this->background.setTexture(*this->backgroundTexture);
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
                    state = STATE::Lobby;
                }
                else cout << "Incorrect login..." << endl;
            break;
            case packetID::WrongVersion:
                cout << "You have an outdated version of the game. Please download the latest version." << endl;
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
    mainWindow.draw(background);

    mainWindow.draw(userInputBox.square);
    mainWindow.draw(passwordInputBox.square);
    mainWindow.draw(serverInputBox.square);

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
}

void Login::handleEvent(const sf::Event& event, STATE& state){
    char letter;
    switch(event.type){
        case sf::Event::Closed:
            network.sendDisconnect();
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
                                userInputBox.inputText.setString(userBuffer);
                            }
                        }
                        else if(userBuffer.size() > 0){
                            userBuffer.pop_back();
                            userInputBox.inputText.setString(userBuffer);
                        }
                    break;
                    case 1: //password
                        if(letter != '\b'){
                            if(passwordBuffer.size() < 15){
                               passwordBuffer.push_back(letter);
                                secretPass = secretPass + "*";
                                passwordInputBox.inputText.setString(secretPass);
                            }
                        }

                        else if(passwordBuffer.size() > 0){
                            passwordBuffer.pop_back();
                            secretPass.pop_back();
                            passwordInputBox.inputText.setString(secretPass);
                        }
                    break;
                    case 2: //server
                        if(letter != '\b'){
                            if(serverBuffer.size() < 25){
                                serverBuffer.push_back(letter);
                                serverInputBox.inputText.setString(serverBuffer);
                            }

                        }
                        else if(serverBuffer.size() > 0){
                            serverBuffer.pop_back();
                            serverInputBox.inputText.setString(serverBuffer);
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
}


void Login::tryToConnect(){
    if(userBuffer.size() > 0){
        if(passwordBuffer.size() > 0){
           network.connect(serverBuffer, port);
            //    network.verifyVersion(VERSION);
            bool response = false, Color = false;
            string answer;

            network.sendLogin(userBuffer, passwordBuffer, VERSION);
            cout << "Please wait..." << endl;
        }
        else
            cout << "Input your password!" << endl;
    }
    else
        cout << "Input a username!" << endl;
}
