#ifndef GAME
#define GAME
#include "board.h"
#include "checkbox.h"

#define BOARD_X 220 //position of the board
#define BOARD_Y 100

class Game{
    public:
        Board b;
        Checkbox Hint;
        sf::Sprite board;
        sf::Texture* texture;
        sf::RenderWindow &mainWindow;
        int i, j, iPiece, jPiece;
        int turn, myColor;
        bool HandleInput(int x, int y);
        void draw();
        void Initialize_Texture(Piece pieces[8][8]);
        int Run();
        Game(sf::RenderWindow& window);
};


#endif // GAME
