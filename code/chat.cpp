#include "headers/chat.h"
#include <string>
#include <iostream>


Chat::Chat(int x, int y, int size_x, int size_y, int input_x, int input_y, ChatStyle style){
    this->charSize = 15U;
    this->height = 5;
    this->historyLength = 4;
    this->chatFont.loadFromFile("media/fonts/AGENCYB.TTF");
    this->inputMessage.setFont(this->chatFont);
    this->inputMessage.setPosition(input_x, input_y);
    this->inputMessage.setString("");
    this->inputMessage.setCharacterSize(this->charSize);
    this->inputMessage.setColor(sf::Color::Black);

    this->historyText.setFont(this->chatFont);
    this->historyText.setColor(sf::Color::Black);
    this->historyText.setCharacterSize(this->charSize);


    this->image.setPosition(x, y);
    this->texture = new sf::Texture();
    this->texture->loadFromFile("media/images/chat.png");
    this->image.setTexture(*this->texture);
    sf::RectangleShape shape(sf::Vector2f(size_x, size_y));
    shape.setPosition(x, y);
    sf::FloatRect squareRect(shape.getPosition().x, shape.getPosition().y, shape.getSize().x, shape.getSize().y);
    this->rectChatBox = squareRect;

    this->chatBox = shape;
    this->active = false;
}


void Chat::draw(sf::RenderWindow & window){
	window.draw(chatBox);
	window.draw(inputBox);
	window.draw(image);
	window.draw(inputMessage);

	float x = chatBox.getGlobalBounds().left + 5;
	float y = chatBox.getGlobalBounds().top + chatBox.getGlobalBounds().height - 3*height - 2*charSize;

	for(std::size_t i = 0; i < history.size(); ++i){
		historyText.setString(history[i]);
		historyText.setPosition(x, y - i*charSize - i*height - height);
		window.draw(historyText);
	}
}

void Chat::receiveMessage(string message){
    history.push_front(message);
        if(history.size() > historyLength)
            history.pop_back();
}

void Chat::handleInput(NetworkHandler &Network, char input){
    if(input == 13){ //enter
        if(active){
            if(inputBuffer.size() > 0){
                history.push_front(Network.myName + ": " + inputBuffer);
                if(history.size() > historyLength)
                    history.pop_back();
                Network.sendChat(inputBuffer);
                inputBuffer.clear();
                inputMessage.setString("");
            }
            active = false;
        }
        else{
            active = true;
        }
    }
    else if(active){
        if(input == '\b'){
            if(inputBuffer.size() > 0){
                inputBuffer.pop_back();
                inputMessage.setString(inputBuffer);
            }
        }
        else{
            inputBuffer.push_back(input);
            inputMessage.setString(inputBuffer);
        }
    }

}
