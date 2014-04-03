#ifndef _BUTTON
#define _BUTTON
#include "GUI.h"
#include <iostream>

class Button : public Interface_Element{
    public:
        void action();
        Button(int x, int y, int size_x, int size_y, std::string desc, ButtonStyle style);
};


#endif // _BUTTON
