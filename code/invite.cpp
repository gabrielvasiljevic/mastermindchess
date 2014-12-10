#include "headers/invite.h"


Invite::Invite(sf::RenderWindow& window) : mainWindow(window),
                                           Interface_Element(INVITE_X, INVITE_Y, 300, 235),
                                           acceptButton (INVITE_X + 50, INVITE_Y + 150, 50, 30, "Yes", "", ButtonStyle::NoImage),
                                           declineButton(INVITE_X + 180, INVITE_Y + 150, 50, 30, "No", "", ButtonStyle::NoImage),
                                           okButton     (INVITE_X + 150, INVITE_Y + 150, 50, 30, "Ok", "", ButtonStyle::NoImage){
    this->image.setTexture(*Textures::invitationPaper);
    this->font.loadFromFile("media/fonts/circhand.ttf");

    this->text.setFont(font);
    this->text.setColor(sf::Color::Black);
    this->text.setPosition(INVITE_X + 20, INVITE_Y + 20);
    this->text.setCharacterSize(30U);
    this->text.setString(" \nhas invited you to a match. \nDo you accept?");

    acceptButton.text.setFont(font);
    acceptButton.text.setCharacterSize(45U);
    declineButton.text.setFont(font);
    declineButton.text.setCharacterSize(45U);

    okButton.text.setFont(font);
    okButton.text.setCharacterSize(45U);
    invited = false;
    inviting = false;
    name = "";
}


void Invite::setText(){
    text.setString(name + " \nhas invited you to a casual\n" + getMatchOptionsText() + " match. \nDo you accept?");
}

string Invite::getMatchOptionsText(){
    string result = "";
    if(isPublic)
        result += "public ";
    else
        result += "private ";
    switch(gameMode){
        case 0:
            result += "Classic ";
        break;
        case 1:
            result += "Fischer ";
        break;
        case 2:
            result += "Capa ";
        break;
    }
    switch(gameTime){
        case 300:
            result += "(5 min)";
        break;
        case 900:
            result += "(15 min)";
        break;
        case 1800:
            result += "(30 min)";
        break;
    }
    return result;
}

bool Invite::handleInput(int x, int y){
    if(inviteRejected){
        if(okButton.clicked(x,y)){
            inviteRejected = false;
            invited = false;
            return true;
        }
        return true;
    }

    if(acceptButton.clicked(x, y)){
        network.sendInviteConfirmation(name, gameMode, gameTime, isPublic);
        cout << "Invite confirmation sended to " << name << endl;
        return true;
    }
    if(declineButton.clicked(x, y)){
        return false;
    }
    return true;
}

void Invite::draw(){
    mainWindow.draw(image);
    mainWindow.draw(text);
    if(inviteRejected){
        mainWindow.draw(okButton.text);
    }
    else{
        mainWindow.draw(acceptButton.text);
        mainWindow.draw(acceptButton.square);
        mainWindow.draw(declineButton.text);
        mainWindow.draw(declineButton.square);
    }

}

void Invite::setRejectedText(string user){
    text.setString(user + " rejected your invite.");

}
