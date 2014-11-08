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
        int cursorPosition;
        int charSize;
        bool active;
        bool spectate;

        ChatStyle style;

        sf::Sprite image;
        sf::Texture* texture;

        sf::Font chatFont;
        sf::Clock chatClock;
        std::string inputBuffer;
        sf::Text inputMessage;
        sf::Text historyText;

        sf::RectangleShape chatBox;
        sf::FloatRect rectChatBox;

        sf::RectangleShape inputBox;
        sf::FloatRect rectInputBox;

        std::deque<std::string> history;
        void handleInput(char input);
        void action();
        void Clear();
        void draw(sf::RenderWindow & window);
        void receiveMessage(string messsage);
        string fitIntoBox(string message);
        void setAllColors(int R, int G, int B, int alpha);
        Chat(int x, int y, int size_x, int size_y, int input_x, int input_y, ChatStyle style);
};


#endif // _CHAT

