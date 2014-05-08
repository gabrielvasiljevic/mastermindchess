#include <SFML/Graphics.hpp>
#include "headers/register.h"
#include <iostream>
#include <string>
#include <fstream>


std::string serverBuffer;
int netport;
using namespace std;

Register::Register(sf::RenderWindow& window, NetworkHandler& network):
                                        mainWindow(window), //x, y, size x, size y, title, text x, text y
                                        network(network),
                                        usernameInputBox(400, 150, 150, 25, "Username", 440, 120),
                                        passwordInputBox(400, 220, 150, 25, "Password", 445, 190),
                                        passwordConfirmInputBox(400, 290, 150, 25, "Confirm Password", 420, 260),
                                        nicknameInputBox(400, 360, 150, 25, "Nickname", 445, 330),
                                        emailInputBox(400, 430, 150, 25, "Email", 460, 400),
                                        registerButton(370, 520, 100, 70, "Register", ButtonStyle::Dark),
                                        cancelButton(480, 520, 100, 70, "Cancel", ButtonStyle::Dark){
    ifstream config {"config.dat"};
    if (config.is_open()){
        getline(config, serverBuffer, ';');
        config >> netport;
    }
    this->backgroundTexture = new sf::Texture();

    this->backgroundTexture->loadFromFile("media/images/bg1.jpg");
    this->background.setTexture(*this->backgroundTexture);

    secretPass = "";
    secretPassConfirm = "";
}

void Register::run(STATE& state){
    packetID receive;
    while (mainWindow.isOpen() && state == STATE::Register){
        sf::Event event;
        while (mainWindow.pollEvent(event)){
            handleEvent(event, state);
        }
        receive = network.receive();
        switch(receive){
            case packetID::RegisterResponse:
                if(network.receiveRegisterResponse()){
                    cout << "Register successful!" << endl;
                    state = STATE::Login;
                }
                else cout << "This username, nickname or e-mail is already being used." << endl;
            break;
        }
        mainWindow.clear(sf::Color(0, 150, 255));
        //window.clear(sf::Color(0, 0, 0));
        draw();
        mainWindow.display();

    }
}

void Register::draw(){
    mainWindow.draw(background);

    mainWindow.draw(usernameInputBox.square);
    mainWindow.draw(passwordInputBox.square);
    mainWindow.draw(passwordConfirmInputBox.square);
    mainWindow.draw(nicknameInputBox.square);
    mainWindow.draw(emailInputBox.square);


    mainWindow.draw(usernameInputBox.text);
    mainWindow.draw(passwordInputBox.text);
    mainWindow.draw(passwordConfirmInputBox.text);
    mainWindow.draw(nicknameInputBox.text);
    mainWindow.draw(emailInputBox.text);

    mainWindow.draw(usernameInputBox.inputText);
    mainWindow.draw(passwordInputBox.inputText);
    mainWindow.draw(passwordConfirmInputBox.inputText);
    mainWindow.draw(nicknameInputBox.inputText);
    mainWindow.draw(emailInputBox.inputText);

    mainWindow.draw(cancelButton.image);
    mainWindow.draw(registerButton.image);

    mainWindow.draw(cancelButton.text);
    mainWindow.draw(registerButton.text);
}

void Register::handleEvent(const sf::Event& event, STATE& state){
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
                selectedBox %= 5;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
                tryToRegister();
            }
            else{
                switch(selectedBox){
                    case 0: //username
                        if(letter != '\b'){
                            if(usernameBuffer.size() < 15){
                                usernameBuffer.push_back(letter);
                                usernameInputBox.inputText.setString(usernameBuffer);
                            }
                        }
                        else if(usernameBuffer.size() > 0){
                            usernameBuffer.pop_back();
                            usernameInputBox.inputText.setString(usernameBuffer);
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
                    case 2: //confirm password
                        if(letter != '\b'){
                            if(passwordConfirmBuffer.size() < 15){
                               passwordConfirmBuffer.push_back(letter);
                                secretPassConfirm = secretPassConfirm + "*";
                                passwordConfirmInputBox.inputText.setString(secretPassConfirm);
                            }
                        }
                        else if(passwordConfirmBuffer.size() > 0){
                            passwordConfirmBuffer.pop_back();
                            secretPassConfirm.pop_back();
                            passwordConfirmInputBox.inputText.setString(secretPassConfirm);
                        }
                    break;
                    case 3:
                        if(letter != '\b'){
                            if(nicknameBuffer.size() < 15){
                                nicknameBuffer.push_back(letter);
                                nicknameInputBox.inputText.setString(nicknameBuffer);
                            }
                        }
                        else if(nicknameBuffer.size() > 0){
                            nicknameBuffer.pop_back();
                            nicknameInputBox.inputText.setString(nicknameBuffer);
                        }
                    break;
                    case 4:
                        if(letter != '\b'){
                            if(emailBuffer.size() < 20){
                                emailBuffer.push_back(letter);
                                emailInputBox.inputText.setString(emailBuffer);
                            }
                        }
                        else if(emailBuffer.size() > 0){
                            emailBuffer.pop_back();
                            emailInputBox.inputText.setString(emailBuffer);
                        }
                    break;
                }
            }
        break;
        case sf::Event::MouseButtonPressed:
            int x = event.mouseButton.x;
            int y = event.mouseButton.y;
            if(usernameInputBox.clicked(x, y)){
                selectedBox = 0;
            }
            else if(passwordInputBox.clicked(x, y)){
                selectedBox = 1;
            }
            else if(passwordConfirmInputBox.clicked(x, y)){
                selectedBox = 2;
            }
            else if(nicknameInputBox.clicked(x, y)){
                selectedBox = 3;
            }
            else if(emailInputBox.clicked(x, y)){
                selectedBox = 4;
            }
            else if(registerButton.clicked(x, y)){
                tryToRegister();
            }
            else if(cancelButton.clicked(x, y)){
                state = STATE::Login;
            }
        break;

    }
}


void Register::tryToRegister(){
    if(usernameBuffer.size() > 0){
        if(passwordBuffer.size() > 0){
            if(passwordBuffer == passwordConfirmBuffer){
                network.connect(serverBuffer, netport);
                //    network.verifyVersion(VERSION);
                bool response = false, Color = false;
                string answer;

                network.sendRegister(usernameBuffer, passwordBuffer, nicknameBuffer, emailBuffer);
                cout << "Please wait..." << endl;
            }
            else
                cout << "Password and confirmation do not match!" << endl;
        }
        else
            cout << "Input a password!" << endl;
    }
    else
        cout << "Input a username!" << endl;
}

