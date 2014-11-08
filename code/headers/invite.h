#ifndef _INVITE
#define _INVITE

#include "button.h"
#include "networkHandler.h"

class Invite: public Interface_Element{
    public:
        sf::RenderWindow &mainWindow;

        bool inviting, invited, inviteRejected, isPublic;

        int gameMode, gameTime;
        std::string name;
        Button acceptButton;
        Button declineButton;
        Button okButton;

        void draw();
        void setText();
        void setRejectedText(string user);
        string getMatchOptionsText();
        bool handleInput(int x, int y);
        Invite(sf::RenderWindow& window);
};

#endif
