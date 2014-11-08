#include "headers/chat.h"
#include "headers/networkHandler.h"
#include <string>
#include <iostream>


Chat::Chat(int x, int y, int size_x, int size_y, int input_x, int input_y, ChatStyle style){
    height = 2;
    cursorPosition = 0;
    this->style = style;
    if(style == ChatStyle::SpectateChat){
        spectate = true;
        historyLength = 6;
        charSize = 30U;
        chatFont.loadFromFile("media/fonts/anilin_regular.ttf");
        historyText.setColor(sf::Color(0, 220, 0));
        length = 500;
    }
    else{
        spectate = false;
        historyLength = 3;
        charSize = 25U;
        chatFont.loadFromFile("media/fonts/circhand.ttf");
        historyText.setColor(sf::Color::Black);
        length = 115;
    }

    inputMessage.setFont(this->chatFont);
    inputMessage.setPosition(input_x, input_y);
    inputMessage.setString("");
    inputMessage.setCharacterSize(this->charSize + 20);
    inputMessage.setColor(sf::Color(0, 220, 0));

    historyText.setFont(this->chatFont);

    historyText.setCharacterSize(this->charSize);


    image.setPosition(x, y);
    texture = new sf::Texture();
    texture->loadFromFile("media/images/chat.png");
    image.setTexture(*texture);
    sf::RectangleShape shape(sf::Vector2f(size_x, size_y));
    shape.setPosition(x, y);
    sf::FloatRect squareRect(shape.getPosition().x, shape.getPosition().y, shape.getSize().x, shape.getSize().y);
    this->rectChatBox = squareRect;

    this->chatBox = shape;
    this->active = false;
}


void Chat::draw(sf::RenderWindow & window){
    int cl = 0;
	//window.draw(chatBox);
	window.draw(inputBox);
	//window.draw(image);
	window.draw(inputMessage);

    if(style == ChatStyle::SpectateChat){
        if(active) chatClock.restart();
        cl = 255 - static_cast<int>(chatClock.getElapsedTime().asSeconds()*32);

        if(cl < 0) cl = 0;
        if(cl > 255) cl = 0;

        setAllColors(0, 0, 0, cl);
    }


	float x = chatBox.getGlobalBounds().left + 15;
	float y = chatBox.getGlobalBounds().top + chatBox.getGlobalBounds().height - 3*height - 2*charSize;
	for(std::size_t i = 0; i < history.size(); i++){
		historyText.setString(fitIntoBox(history[i]));
		historyText.setPosition(x, y - i*2*charSize - i*height - height);
		window.draw(historyText);
	}
}


string Chat::fitIntoBox(string message){
    sf::Text textAux;
    textAux.setCharacterSize(charSize);
    textAux.setFont(chatFont);
    string aux = "";
    for(int i = 0; i < message.size(); i++){
        textAux.setString(aux + message[i]);
        if(textAux.getGlobalBounds().width >= length){
            aux += "\n";
        }
        aux += message[i];
    }
    return aux;
}

void Chat::receiveMessage(string message){
    history.push_front(message);
    chatClock.restart();
        if(history.size() > historyLength)
            history.pop_back();
}

void Chat::handleInput(char input){
    if(input == 13){ //enter
        if(active){
            if(inputBuffer.size() > 0){
                history.push_front("Me:\n" + inputBuffer);
                if(history.size() > historyLength)
                    history.pop_back();
                network.sendChat(inputBuffer, spectate);
                inputBuffer.clear();
                inputMessage.setString("");
            }
            else{
                inputMessage.setString("");
            }
            active = false;
        }
        else{
            active = true;
            inputMessage.setString("|");
        }
    }
    else if(active){
        if(input == '\b'){
            if(inputBuffer.size() > 0){
                inputBuffer.pop_back();
                inputMessage.setString(inputBuffer + "|");
            }
        }
        else{
            inputBuffer.push_back(input);
            inputMessage.setString(inputBuffer + "|");
        }
    }

}

void Chat::setAllColors(int R, int G, int B, int alpha){
    inputMessage.setColor(sf::Color(R, G, B, alpha));
    historyText.setColor(sf::Color(R, G, B, alpha));
}

void Chat::Clear(){
    inputMessage.setString("");
    historyText.setString("");
    history.clear();
}
