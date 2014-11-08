#ifndef _LOGIN
#define _LOGIN
#include "inputBox.h"
#include "button.h"
#include "register.h"
#include "networkHandler.h"
#include "dataTypes.h"
#include "configurationDAO.h"

class Login{
    public:

        int selectedBox = 0;
        inputBox userInputBox;
        inputBox passwordInputBox;
        inputBox serverInputBox;

        Button loginButton;
        Button registerButton;

        sf::Font font;
        sf::Text userAlert;
        sf::Clock alertClock;

        sf::Sprite background;
        sf::Sprite loginBG;

        sf::Texture* backgroundTexture;

        sf::RenderWindow &mainWindow;

        Register _register;

        std::string userBuffer;
        std::string passwordBuffer;
        std::string serverBuffer;
        std::string secretPass;
        std::string configBuffer;

        void selectBox();
        void handleEvent(const sf::Event& event, STATE& state);
        void draw();
        void tryToConnect();
        void waitForGame();
        void run(STATE& state);
        Login(sf::RenderWindow& window);
};

#endif // _LOGIN
