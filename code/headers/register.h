#ifndef _REGISTER
#define _REGISTER
#include "inputBox.h"
#include "button.h"
#include "networkHandler.h"
#include "dataTypes.h"

class Register{
    public:

        int selectedBox = 0;
        inputBox usernameInputBox;
        inputBox passwordInputBox;
        inputBox passwordConfirmInputBox;
        inputBox nicknameInputBox;
        inputBox emailInputBox;
        Button cancelButton;
        Button registerButton;
        sf::Sprite background;
        sf::Texture* backgroundTexture;
        sf::RenderWindow &mainWindow;
        NetworkHandler &network;
        std::string usernameBuffer;
        std::string passwordBuffer;
        std::string passwordConfirmBuffer;
        std::string nicknameBuffer;
        std::string emailBuffer;
        std::string secretPass;
        std::string secretPassConfirm;
        void handleEvent(const sf::Event& event, STATE& state);
        void draw();
        void tryToRegister();
        void waitForGame();
        void run(STATE& state);
        Register(sf::RenderWindow& window, NetworkHandler& network);
};

#endif // _REGISTER
