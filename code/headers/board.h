#ifndef _BOARD
#define _BOARD
#include "Pieces.h"


class Board{
    public:
        int columns;
        int gametype;
        Piece pieces[8][10]; //The board is a 8x8 matrix made of pieces
        void randomizePieces();
        void Initialize(int board_x, int board_y, int gametype);
        void InitializeBlack(int board_x, int board_y, int gametype);
        void organizePieces(int color, int gametype);
        void setBoard(std::string newBoard[8][10]);
        void Highlight(TYPE t, int i, int j);
        void HighlightTower(int i, int j);
        void HighlightBishop(int i, int j);
        void HighlightKnight(int i, int j);
        void HighlightKing(int i, int j);
        void HighlightCastling(int i, int j);
        Board(int board_x, int board_y, int color, int gametype);
};

#endif
