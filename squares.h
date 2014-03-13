#ifndef _SQUARES
#define _SQUARES


class Square{
    public:
        int color;
        int x;
        int y;
        bool clicked;
        sf::RectangleShape square;
        sf::FloatRect rectSquare;
        bool verify_click(int x, int y);
        Square();
};

#endif
