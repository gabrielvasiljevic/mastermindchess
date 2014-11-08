#ifndef _PIECES
#define _PIECES
#include <iostream>
#include "dataTypes.h"


#define PIECE_SIZE 64

class Piece{
    public:
        TYPE type;
        sf::Sprite image; //The image of the piece itself
        sf::Sprite border;
        sf::Sprite grayborder;
        sf::Sprite yellowborder;
        sf::Sprite redborder;

        sf::Texture* borderTexture;
        sf::Texture* grayborderTexture;
        sf::Texture* yellowborderTexture;
        sf::Texture* redborderTexture;

        bool clicked; //To check if the piece was clicked
        bool highlighted;
        bool selected;
        bool attacked;
        bool current;

        bool hasMoved;
        bool movement(Piece board[8][10], int i, int j, int iP, int jP, bool check);
        bool pawnMovement(Piece board[8][10], int i, int j, int iP, int jP, bool check);
        bool towerMovement(Piece board[8][10], int i, int j, int iP, int jP, bool check);
        bool bishopMovement(Piece board[8][10], int i, int j, int iP, int jP, bool check);
        bool knightMovement(Piece board[8][10], int i, int j, int iP, int jP, bool check);
        bool capture(Piece board[8][10], int i, int j, int iP, int jP, bool check);
        void changePiece(Piece board[8][10], int i, int j, int iP, int jP);
        void changeType(std::string code);
        void changeType(TYPE type);
        void changeType(TYPE type, int color);
        void changeBack(Piece board[8][10], int i, int j, int iP, int jP);
        bool testSmallCastling(Piece board[8][10], int i, int j, int iP, int jP);
        bool testBigCastling(Piece board[8][10], int i, int j, int iP, int jP);
        int color; //The color of the piece: black or white
        int moves;
        int gametype, columns;
        int attackBoard[8][10];
        std::string code;
        sf::RectangleShape square; //The geometric figure that define the shape of the piece
        sf::FloatRect rectSquare; //A FloatRect structure allows to test if a coordinate (the click of the mouse) was inside it.
                                  //Thus, we use it along the square, with the same position of it.
        Piece();
        Piece(TYPE tipo);
};


#endif // _PIECES
