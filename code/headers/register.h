#ifndef _REGISTER
#define _REGISTER
#include "inputBox.h"
#include "button.h"
#include "networkHandler.h"
#include "dataTypes.h"
#include "configurationDAO.h"




class Register{
    public:

        int selectedBox = 0;
        inputBox usernameInputBox;
        inputBox passwordInputBox;
        inputBox passwordConfirmInputBox;
        inputBox nicknameInputBox;
        inputBox emailInputBox;
        inputBox serverInputBox;

        Button cancelButton;
        Button registerButton;
        sf::Sprite background;
        sf::Texture* backgroundTexture;
        sf::RenderWindow &mainWindow;

        std::string usernameBuffer;
        std::string passwordBuffer;
        std::string passwordConfirmBuffer;
        std::string nicknameBuffer;
        std::string emailBuffer;
        std::string serverBuffer;
        std::string secretPass;
        std::string secretPassConfirm;

        void handleEvent(const sf::Event& event, STATE& state);
        void draw();
        void selectBox();
        void tryToRegister();
        void waitForGame();
        void run(STATE& state);
        Register(sf::RenderWindow& window);
};

#endif // _REGISTER
