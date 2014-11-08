#ifndef PIECEHOLDER
#define PIECEHOLDER
#include <iostream>

#include "Pieces.h"
#include "dataTypes.h"
//#include "textures.h"

#define BOX_X 730
#define BOX_Y 20

class PieceHolder{
    public:
    enum {KNIGHT1 = 0, KNIGHT2, BISHOP1, BISHOP2, ROOK1, ROOK2, QUEEN1,
          BKNIGHT1, BKNIGHT2, BBISHOP1, BBISHOP2, BROOK1, BROOK2, BQUEEN1,
          CHANCELER1, ARCHBISHOP1, BCHANCELER1, BARCHBISHOP1};
    bool capt_pawns[10], capt_bpawns[10], capt_pieces[18];
    int posPawn, posKnight, posBishop, posRook;
    int posBPawn, posBKnight, posBBishop, posBRook;
    sf::Texture* pawn;
    sf::Texture* bpawn;
    sf::Texture* tower;
    sf::Texture* btower;
    sf::Texture* knight;
    sf::Texture* bknight;
    sf::Texture* bishop;
    sf::Texture* bbishop;
    sf::Texture* queen;
    sf::Texture* bqueen;
    sf::Texture* king;
    sf::Texture* bking;
    sf::Texture* blank;


        sf::Sprite         box;
        sf::Texture*       boxTexture;

        sf::Sprite         pawns[10];
        sf::Sprite         bishop1;
        sf::Sprite         bishop2;
        sf::Sprite         knight1;
        sf::Sprite         knight2;
        sf::Sprite         rook1;
        sf::Sprite         rook2;
        sf::Sprite         queen1;

        sf::Sprite         bpawns[10];
        sf::Sprite         bbishop1;
        sf::Sprite         bbishop2;
        sf::Sprite         bknight1;
        sf::Sprite         bknight2;
        sf::Sprite         brook1;
        sf::Sprite         brook2;
        sf::Sprite         bqueen1;


        sf::RenderWindow &mainWindow;


        void add        (TYPE piece, int color);
        void reset      ();
        void draw       ();

        PieceHolder(sf::RenderWindow &window);
};


#endif // PIECEHOLDER

