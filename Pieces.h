#ifndef _PIECES
#define _PIECES

//A piece can be a regular chess piece, or a blank square
enum TYPE {BLANK, PAWN, KNIGHT, BISHOP, TOWER, QUEEN, KING};

class Piece{
    public:
    TYPE type;
    sf::Sprite image; //The image of the piece itself
    void movement(Piece board[8][8], int i, int j, int iP, int jP);
    void capture(Piece board[8][8], int i, int j, int iP, int jP);
    int color; //The color of the piece: black or white
    bool clicked; //To check if the piece was clicked
    sf::RectangleShape square; //The geometric figure that define the shape of the piece
    sf::FloatRect rectSquare; //A FloatRect structure allows to test if a coordinate (the click of the mouse) was inside it.
                              //Thus, we use it along the square, with the same position of it.
    Piece();
    Piece(TYPE tipo);
};


#endif // _PIECES
