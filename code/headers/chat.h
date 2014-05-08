#ifndef _CHAT
#define _CHAT
#include "GUI.h"
#include "networkHandler.h"
#include "inputBox.h"
#include <iostream>
#include <deque>

class Chat{
    public:
        std::size_t historyLength;
        float height;
        float length;
        int charSize;
        bool active;

        sf::Sprite image;
        sf::Texture* texture;

        sf::Font chatFont;

        std::string inputBuffer;
        sf::Text inputMessage;
        sf::Text historyText;

        sf::RectangleShape chatBox;
        sf::FloatRect rectChatBox;

        sf::RectangleShape inputBox;
        sf::FloatRect rectInputBox;

        std::deque<std::string> history;
        void handleInput(NetworkHandler &Network, char input);
        void action();
        void draw(sf::RenderWindow & window);
        void receiveMessage(string messsage);
        Chat(int x, int y, int size_x, int size_y, int input_x, int input_y, ChatStyle style);
};


#endif // _CHAT

