#ifndef _PIECES
#define _PIECES
#include <iostream>

//A piece can be a regular chess piece, or a blank square
enum TYPE {BLANK, PAWN, KNIGHT, BISHOP, TOWER, QUEEN, KING};

#define PIECE_SIZE 55

class Piece{
    public:
        TYPE type;
        sf::Sprite image; //The image of the piece itself
        sf::Sprite border;
        bool clicked; //To check if the piece was clicked
        bool highlighted;
        bool hasMoved;
        bool movement(Piece board[8][8], int i, int j, int iP, int jP, bool check);
        bool capture(Piece board[8][8], int i, int j, int iP, int jP, bool check);
        void changePiece(Piece board[8][8], int i, int j, int iP, int jP);
        void changeBack(Piece board[8][8], int i, int j, int iP, int jP);
        bool testSmallCastling(Piece board[8][8], int i, int j, int iP, int jP);
        bool testBigCastling(Piece board[8][8], int i, int j, int iP, int jP);
        int color; //The color of the piece: black or white
        int attackBoard[8][8];
        std::string code;
        sf::RectangleShape square; //The geometric figure that define the shape of the piece
        sf::FloatRect rectSquare; //A FloatRect structure allows to test if a coordinate (the click of the mouse) was inside it.
                                  //Thus, we use it along the square, with the same position of it.
        Piece();
        Piece(TYPE tipo);
};


#endif // _PIECES
