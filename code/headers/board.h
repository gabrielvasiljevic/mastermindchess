#ifndef _BOARD
#define _BOARD
#include "Pieces.h"

class Board{
    public:
        Piece pieces[8][8]; //The board is a 8x8 matrix made of pieces
        void Initialize(int board_x, int board_y);
        void Highlight(TYPE t, int i, int j);
        void HighlightTower(int i, int j);
        void HighlightBishop(int i, int j);
        void HighlightKnight(int i, int j);
        void HighlightKing(int i, int j);
        Board(int board_x, int board_y);
};

#endif
