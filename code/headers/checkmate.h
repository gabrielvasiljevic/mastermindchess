#ifndef _CHECKMATE
#define _CHECKMATE

#include <SFML/Graphics.hpp>
#include "board.h"
#include <iostream>
#include <math.h>


class CheckMate{
    public:
        void resetAttackBoard(Piece board[8][8]);
        void updateAttackBoard(Piece board[8][8]);
        void updateBoard(Piece pieces[8][8], TYPE t, int i, int j);
        void updateBishop(Piece pieces[8][8], int i, int j);
        void updateKnight(Piece pieces[8][8], int i, int j);
        void updateTower(Piece pieces[8][8], int i, int j);
        void updateKing(Piece pieces[8][8], int i, int j);
        bool testCheck(Piece pieces[8][8], int color);
        bool testCheckMate(Piece pieces[8][8], int color);
        bool testKingMove(Piece pieces[8][8], int iKing, int jKing);
        bool testBlockMove(Piece pieces[8][8], int iKing, int jKing);
        bool testBlockQueen(Piece pieces[8][8], int iQueen, int jQueen, int iKing, int jKing);
        bool testBlockTower(Piece pieces[8][8], int iTower, int jTower, int iKing, int jKing);
        bool testBlockBishop(Piece pieces[8][8], int iBishop, int jBishop, int iKing, int jKing);
        bool testCaptureMove(Piece pieces[8][8], int iKing, int jKing);
        bool testCapture(Piece pieces[8][8], int iX, int jX);
        bool testKingAttack(Piece piece, int iKing, int jKing);
};


#endif
