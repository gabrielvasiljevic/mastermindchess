#ifndef _CAPABOARD
#define _CAPABOARD
#include "capapiece.h"

#define CBOARD_X 195 //position of the board
#define CBOARD_Y 90

class Capaboard{
    public:
        capapiece pieces[8][10]; //The board is a 8x10 matrix made of pieces
        void Initialize(int board_x, int board_y);
        void InitializeBlack(int board_x, int board_y);
        void Highlight(CAPATYPE t, int i, int j);
        void HighlightTower(int i, int j);
        void HighlightBishop(int i, int j);
        void HighlightKnight(int i, int j);
        void HighlightKing(int i, int j);
        void HighlightCastling(int i, int j);
        Capaboard(int board_x, int board_y, int color);
};

#endif

