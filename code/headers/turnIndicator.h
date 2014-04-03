#ifndef _INDI
#define _INDI
#include "GUI.h"
#include <string>

class turnIndicator : public Interface_Element {
    public:
        bool turn;
        void changeTurn();
        turnIndicator(int x, int y, int size_x, int size_y);
};

#endif // _GUI

