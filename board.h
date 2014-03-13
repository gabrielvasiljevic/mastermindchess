#ifndef _BOARD
#define _BOARD
#include "Pieces.h"

class Board{
    public:
        Piece pieces[8][8]; //The board is a 8x8 matrix made of pieces
        Board();
};

#endif
