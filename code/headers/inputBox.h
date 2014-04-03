#ifndef _INPUTBOX
#define _INPUTBOX
#include "GUI.h"
#include <iostream>

class inputBox : public Interface_Element{
    public:
        void action();
        sf::Text inputText;
        inputBox(int x, int y, int size_x, int size_y, std::string desc, int text_x, int text_y);
};


#endif // _INPUTBOX
