#ifndef _CAPACHECKMATE
#define _CAPACHECKMATE

#include <SFML/Graphics.hpp>
#include "capaboard.h"
#include <iostream>
#include <math.h>


class CapaCheckMate{
    public:
        void resetAttackBoard(capapiece board[8][10]);
        void updateAttackBoard(capapiece board[8][10]);
        void updateBoard(capapiece pieces[8][10], CAPATYPE t, int i, int j);
        void updateBishop(capapiece pieces[8][10], int i, int j);
        void updateKnight(capapiece pieces[8][10], int i, int j);
        void updateTower(capapiece pieces[8][10], int i, int j);
        void updateKing(capapiece pieces[8][10], int i, int j);
        bool testCheck(capapiece pieces[8][10], int color);
        bool testCheckMate(capapiece pieces[8][10], int color);
        bool testKingMove(capapiece pieces[8][10], int iKing, int jKing);
        bool testBlockMove(capapiece pieces[8][10], int iKing, int jKing);
        bool testBlockQueen(capapiece pieces[8][10], int iQueen, int jQueen, int iKing, int jKing);
        bool testBlockTower(capapiece pieces[8][10], int iTower, int jTower, int iKing, int jKing);
        bool testBlockBishop(capapiece pieces[8][10], int iBishop, int jBishop, int iKing, int jKing);
        bool testIfStillInCheck(capapiece pieces[8][10], int i, int j, int iX, int iY);
        bool testCaptureMove(capapiece pieces[8][10], int iKing, int jKing);
        bool testCapture(capapiece pieces[8][10], int iX, int jX);
        bool testKingAttack(capapiece piece, int iKing, int jKing);

};

#endif
