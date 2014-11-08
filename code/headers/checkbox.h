#ifndef _CHECK
#define _CHECK
#include "GUI.h"
#include <string>

class Checkbox : public Interface_Element {
    public:
        bool checked;
        void action();
        void unmark();
        void mark();
        Checkbox(int x, int y, int size_x, int size_y, std::string desc);
};

#endif // _GUI
