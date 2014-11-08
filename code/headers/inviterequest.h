#ifndef _INVITEREQ
#define _INVITEREQ

#include "button.h"
#include "checkbox.h"
#include "networkHandler.h"
#define inviteRequest InviteRequest::getInviteRequest()

class InviteRequest: public Interface_Element{
    private:
        //Singleton
        static InviteRequest* instance;
        InviteRequest(InviteRequest const&);
        void operator=(InviteRequest const&);

    public:

        static InviteRequest& getInviteRequest();
        sf::RenderWindow &mainWindow;

        std::string name;
        int gameMode, gameTime;
        bool inviting;
        bool isPublic;
        Button sendButton;
        Button cancelButton;

        sf::Sprite checkMode;
        sf::Sprite checkTime;
        sf::Sprite checkPublic;

        sf::Texture* checkTexture;

        Checkbox selectClassicButton;
        Checkbox selectFischerButton;
        Checkbox selectCapaButton;

        Checkbox selectPublicButton;
        Checkbox selectPrivateButton;

        Checkbox select5MinutesButton;
        Checkbox select15MinutesButton;
        Checkbox select30MinutesButton;

        void draw();
        bool handleInput(int x, int y);
        void handleInput(sf::Event::KeyEvent key, STATE& state);
        void CreateRequest(string name);
        InviteRequest(sf::RenderWindow& window);
};

#endif

