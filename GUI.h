#include <SFML/Graphics.hpp>
#ifndef _GUI
#define _GUI

class Interface_Element{
    public:
    int pos_x;
    int pos_y;
    sf::Text text;
    sf::Font font;
    sf::Sprite image;
    sf::Texture* texture;
    sf::RectangleShape square; //The geometric figure that define the shape of the element
    sf::FloatRect rectSquare; //A FloatRect structure allows to test if a coordinate (the click of the mouse) was inside it.
                              //Thus, we use it along the square, with the same position of it.
    Interface_Element(int x, int y, int size_x, int size_y);
    bool clicked(int x, int y);
};

#endif // _GUI
