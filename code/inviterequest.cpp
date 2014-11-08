#include "headers/inviterequest.h"

extern sf::RenderWindow window;

InviteRequest& InviteRequest::getInviteRequest(){
    static InviteRequest instance(window);
    return instance;
}


InviteRequest::InviteRequest(sf::RenderWindow& window) : mainWindow(window),
                                           Interface_Element    (INVITE_X,          INVITE_Y,       300, 235),
                                           sendButton           (INVITE_X + 180,    INVITE_Y + 190, 60, 30, "Send", "", ButtonStyle::NoImage),
                                           cancelButton         (INVITE_X + 50,     INVITE_Y + 190, 68, 30, "Cancel", "", ButtonStyle::NoImage),
                                           selectClassicButton  (INVITE_X + 50,     INVITE_Y + 90,  50, 25, "Classic"),
                                           selectFischerButton  (INVITE_X + 50,     INVITE_Y + 110, 50, 25, "Fischer"),
                                           selectCapaButton     (INVITE_X + 50,     INVITE_Y + 130, 50, 25, "Capa"),
                                           select5MinutesButton (INVITE_X + 180,    INVITE_Y + 90,  50, 25, "5min"),
                                           select15MinutesButton(INVITE_X + 180,    INVITE_Y + 110, 50, 25, "15min"),
                                           select30MinutesButton(INVITE_X + 180,    INVITE_Y + 130, 50, 25, "30min"),
                                           selectPublicButton   (INVITE_X + 50,     INVITE_Y + 160, 50, 25, "Public"),
                                           selectPrivateButton  (INVITE_X + 180,    INVITE_Y + 160, 50, 25, "Private"){
    this->image.setTexture(*Textures::invitationPaper);
    this->font.loadFromFile("media/fonts/circhand.ttf");

    this->text.setFont(font);
    this->text.setColor(sf::Color::Black);
    this->text.setPosition(INVITE_X + 20, INVITE_Y + 20);
    this->text.setCharacterSize(30U);
    this->text.setString("You are inviting\n XYZ to a match.");

    this->checkTexture = new sf::Texture();
    this->checkTexture->loadFromFile("media/images/check.png");

    this->checkMode.setTexture(*this->checkTexture);
    this->checkTime.setTexture(*this->checkTexture);
    this->checkPublic.setTexture(*this->checkTexture);

    sendButton.text.setFont(font);
    sendButton.text.setCharacterSize(40U);

    selectClassicButton.text.setFont(font);
    selectFischerButton.text.setFont(font);
    selectCapaButton.text.setFont(font);

    select5MinutesButton.text.setFont(font);
    select15MinutesButton.text.setFont(font);
    select30MinutesButton.text.setFont(font);

    selectClassicButton.text.setCharacterSize(30U);
    selectFischerButton.text.setCharacterSize(30U);
    selectCapaButton.text.setCharacterSize(30U);

    select5MinutesButton.text.setCharacterSize(30U);
    select15MinutesButton.text.setCharacterSize(30U);
    select30MinutesButton.text.setCharacterSize(30U);

    selectPublicButton.text.setCharacterSize(25U);
    selectPrivateButton.text.setCharacterSize(25U);

    selectPublicButton.text.setFont(font);
    selectPrivateButton.text.setFont(font);


    cancelButton.text.setFont(font);
    cancelButton.text.setCharacterSize(40U);

    gameTime = 300;
    select5MinutesButton.mark();
    select15MinutesButton.unmark();
    select30MinutesButton.unmark();
    checkTime.setPosition(select5MinutesButton.pos_x - 5, select5MinutesButton.pos_y);

    gameMode = 0;
    selectClassicButton.mark();
    selectFischerButton.unmark();
    selectCapaButton.unmark();
    checkMode.setPosition(selectClassicButton.pos_x - 5, selectClassicButton.pos_y);

    inviting = false;
    isPublic = true;
    checkPublic.setPosition(selectPublicButton.pos_x - 5, selectPublicButton.pos_y);
}

void InviteRequest::handleInput(sf::Event::KeyEvent key, STATE& state){

    if(key.code == sf::Keyboard::Escape){
        inviting = false;
    }
}

bool InviteRequest::handleInput(int x, int y){
    if(sendButton.clicked(x, y)){
        inviting = false;
        network.sendMatchInvite(name, gameMode, gameTime, isPublic);//send invite
        cout << "Invite sended to " << name << endl;
        return true;
    }
    if(cancelButton.clicked(x, y)){
        inviting = false;
        return false;
    }
    if(select5MinutesButton.clicked(x, y) && gameTime != 300){
        checkTime.setPosition(select5MinutesButton.pos_x - 10, select5MinutesButton.pos_y + 5);
        select5MinutesButton.mark();
        select15MinutesButton.unmark();
        select30MinutesButton.unmark();
        gameTime = 300;

    }
    if(select15MinutesButton.clicked(x, y) && gameTime != 900){
        checkTime.setPosition(select15MinutesButton.pos_x - 10, select15MinutesButton.pos_y + 5);
        select5MinutesButton.unmark();
        select15MinutesButton.mark();
        select30MinutesButton.unmark();
        gameTime = 900;

    }
    if(select30MinutesButton.clicked(x, y) && gameTime != 1800){
        checkTime.setPosition(select30MinutesButton.pos_x - 10, select30MinutesButton.pos_y + 5);
        select5MinutesButton.unmark();
        select15MinutesButton.unmark();
        select30MinutesButton.mark();
        gameTime = 1800;

    }

    if(selectClassicButton.clicked(x, y) && gameMode != 0){
        checkMode.setPosition(selectClassicButton.pos_x - 10, selectClassicButton.pos_y + 5);
        selectClassicButton.mark();
        selectCapaButton.unmark();
        selectFischerButton.unmark();
        gameMode = 0;

    }
    if(selectCapaButton.clicked(x, y) && gameMode != 2){
        checkMode.setPosition(selectCapaButton.pos_x - 10, selectCapaButton.pos_y + 5);
        selectClassicButton.unmark();
        selectCapaButton.mark();
        selectFischerButton.unmark();
        gameMode = 2;

    }
    if(selectFischerButton.clicked(x, y) && gameMode != 1){
        checkMode.setPosition(selectFischerButton.pos_x - 10, selectFischerButton.pos_y + 5);
        selectClassicButton.unmark();
        selectCapaButton.unmark();
        selectFischerButton.mark();
        gameMode = 1;

    }

    if(selectPublicButton.clicked(x, y) && isPublic == false){
        checkPublic.setPosition(selectPublicButton.pos_x - 10, selectPublicButton.pos_y + 5);
        selectPrivateButton.unmark();
        selectPublicButton.mark();
        isPublic = true;
    }

    if(selectPrivateButton.clicked(x, y) && isPublic == true){
        checkPublic.setPosition(selectPrivateButton.pos_x - 10, selectPrivateButton.pos_y + 5);
        selectPrivateButton.mark();
        selectPublicButton.unmark();
        isPublic = false;
    }

    return true;
}

void InviteRequest::CreateRequest(string name){
    this->name = name;
    text.setString("You are inviting\n " + name + " to a match.");
    inviting = true;
}

void InviteRequest::draw(){
    mainWindow.draw(image);
    mainWindow.draw(text);

    mainWindow.draw(sendButton.square);
    mainWindow.draw(sendButton.text);

    mainWindow.draw(cancelButton.square);
    mainWindow.draw(cancelButton.text);


    mainWindow.draw(select5MinutesButton.text);
    mainWindow.draw(select15MinutesButton.text);
    mainWindow.draw(select30MinutesButton.text);

    mainWindow.draw(selectClassicButton.text);
    mainWindow.draw(selectFischerButton.text);
    mainWindow.draw(selectCapaButton.text);

    mainWindow.draw(selectPrivateButton.text);
    mainWindow.draw(selectPublicButton.text);

    mainWindow.draw(checkMode);
    mainWindow.draw(checkTime);
    mainWindow.draw(checkPublic);
}

