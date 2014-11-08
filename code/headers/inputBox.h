#ifndef _INPUTBOX
#define _INPUTBOX
#include "GUI.h"
#include <iostream>

class inputBox : public Interface_Element{
    public:
        bool selected;
        void action();
        sf::Text inputText;
        sf::Sprite background;
        void select();
        void deselect();
        std::string getLastLetters(std::string input, int letters);
        inputBox(int x, int y, int size_x, int size_y, std::string desc, int text_x, int text_y, int size);
};


#endif // _INPUTBOX
