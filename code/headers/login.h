#ifndef _LOGIN
#define _LOGIN
#include "inputBox.h"
#include "button.h"
#include "networkHandler.h"
#include "dataTypes.h"

class Login{
    public:

        int selectedBox = 0;
        inputBox userInputBox;
        inputBox passwordInputBox;
        inputBox serverInputBox;
        Button loginButton;
        Button registerButton;
        sf::Sprite background;
        sf::Texture* backgroundTexture;
        sf::RenderWindow &mainWindow;
        NetworkHandler &network;
        std::string userBuffer;
        std::string passwordBuffer;
        std::string serverBuffer;
        void handleEvent(const sf::Event& event);
        void draw();
        void tryToConnect();
        void waitForGame();
        void run(STATE& state);
        Login(sf::RenderWindow& window, NetworkHandler& network);
};

#endif // _LOGIN
