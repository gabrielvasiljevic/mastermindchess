#ifndef _CAPAPIECES
#define _CAPAPIECES
#include <iostream>

//A piece can be a regular chess piece, or a blank square
enum CAPATYPE {CAPABLANK, CAPAPAWN, CAPAKNIGHT, CAPABISHOP, CAPATOWER, CAPAQUEEN, CAPAKING, ARCHBISHOP, CHANCELER};

#define PIECE_SIZE 64

class capapiece{
    public:
        CAPATYPE type;
        int gametype;
        int columns;
        sf::Sprite image; //The image of the piece itself
        sf::Sprite border;
        sf::Sprite grayborder;

        bool clicked; //To check if the piece was clicked
        bool highlighted;
        bool selected;
        bool hasMoved;

        bool movement(capapiece board[8][10], int i, int j, int iP, int jP, bool check);
        bool pawnMovement(capapiece board[8][10], int i, int j, int iP, int jP, bool check);
        bool towerMovement(capapiece board[8][10], int i, int j, int iP, int jP, bool check);
        bool bishopMovement(capapiece board[8][10], int i, int j, int iP, int jP, bool check);
        bool knightMovement(capapiece board[8][10], int i, int j, int iP, int jP, bool check);
        bool capture(capapiece board[8][10], int i, int j, int iP, int jP, bool check);
        void changePiece(capapiece board[8][10], int i, int j, int iP, int jP);
        void changeBack(capapiece board[8][10], int i, int j, int iP, int jP);
        bool testSmallCastling(capapiece board[8][10], int i, int j, int iP, int jP);
        bool testBigCastling(capapiece board[8][10], int i, int j, int iP, int jP);
        int color; //The color of the piece: black or white
        int moves;
        int attackBoard[8][10];
        std::string code;
        sf::RectangleShape square; //The geometric figure that define the shape of the piece
        sf::FloatRect rectSquare; //A FloatRect structure allows to test if a coordinate (the click of the mouse) was inside it.
                                  //Thus, we use it along the square, with the same position of it.
        capapiece();
        capapiece(CAPATYPE tipo);
};


#endif // _PIECES

