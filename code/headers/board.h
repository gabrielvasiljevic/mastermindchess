#ifndef _BOARD
#define _BOARD
#include "Pieces.h"

#define BOARD_X 250 //position of the board
#define BOARD_Y 100

class Board{
    public:
        Piece pieces[8][8]; //The board is a 8x8 matrix made of pieces
        void Initialize(int board_x, int board_y);
        void InitializeBlack(int board_x, int board_y);
        void Highlight(TYPE t, int i, int j);
        void HighlightTower(int i, int j);
        void HighlightBishop(int i, int j);
        void HighlightKnight(int i, int j);
        void HighlightKing(int i, int j);
        void HighlightCastling(int i, int j);
        Board(int board_x, int board_y, int color);
};

#endif
