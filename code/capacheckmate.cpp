#include <SFML/Graphics.hpp>
#include "headers/capacheckmate.h"

using namespace std;

int capacolor;
//Extremely sensitive, enormous and complex algorithm. Do not touch, as only God knows what lies below this comment!

void CapaCheckMate::resetAttackBoard(capapiece board[8][10]){
    int i, j, k, p;
    for(i = 0; i < 8; i++){
        for(j = 0; j < 10; j++){
            for(k = 0; k < 8; k++){
                for(p = 0; p < 10; p++){
                    board[i][j].attackBoard[k][p] = 0;
                }
            }

        }
    }
}

bool CapaCheckMate::testIfStillInCheck(capapiece pieces[8][10], int i, int j, int iX, int iY){
    int color = pieces[i][j].color;
    if(pieces[i][j].type == CAPAKING) return true;
    pieces[i][j].changePiece(pieces, i, j, iX, iY);
    updateAttackBoard(pieces);
    if(testCheck(pieces, !color)){
        pieces[i][j].changeBack(pieces, i, j, iX, iY);
        updateAttackBoard(pieces);
        return true; //yes, still in check
    }
    pieces[i][j].changeBack(pieces, i, j, iX, iY);
    updateAttackBoard(pieces);
    return false;
}

void CapaCheckMate::updateBoard(capapiece pieces[8][10], CAPATYPE t, int i, int j){
    bool stop = false;
    switch(t){
        case CAPAPAWN:
            if(pieces[i][j].color == 1){
               if(i < 7){ //Do not pass the board!
                    if(i + 1 < 8 && j + 1 < 10){ //test if the sides are inside the board
                        if(pieces[i+1][j+1].type != CAPABLANK && pieces[i+1][j+1].color != pieces[i][j].color){ //if the diagonal squares are from a different color
                            pieces[i][j].attackBoard[i+1][j+1] = 1;
                        }
                        if(j - 1 >= 0){ //same here
                            if(pieces[i+1][j-1].type != CAPABLANK && pieces[i+1][j-1].color != pieces[i][j].color){
                                pieces[i][j].attackBoard[i+1][j-1] = 1;
                            }
                        }
                    }
                    if(j == 9){
                        if(pieces[i+1][j-1].type != CAPABLANK && pieces[i+1][j-1].color != pieces[i][j].color){
                            pieces[i][j].attackBoard[i+1][j-1] = 1;
                        }
                    }
                }
            }
            else{
                if(i > 0){ //Do not pass the board!
                    if(i - 1 > -1 && j + 1 < 10){ //test if the sides are inside the board
                        if(pieces[i-1][j+1].type != CAPABLANK && pieces[i-1][j+1].color != pieces[i][j].color){ //if the diagonal squares are from a different color
                            pieces[i][j].attackBoard[i-1][j+1] = 1;
                        }
                        if(j - 1 >= 0){ //same here
                            if(pieces[i-1][j-1].type != CAPABLANK && pieces[i-1][j-1].color != pieces[i][j].color){
                                pieces[i][j].attackBoard[i-1][j-1] = 1;
                            }
                        }
                    }
                    if(j == 9){
                        if(pieces[i-1][j-1].type != CAPABLANK && pieces[i-1][j-1].color != pieces[i][j].color){
                            pieces[i][j].attackBoard[i-1][j-1] = 1;
                        }
                    }
                }
            }

        break;
        case CAPATOWER:
            updateTower(pieces, i, j);
        break;
        case CAPABISHOP:
            updateBishop(pieces, i, j);
        break;
        case CAPAQUEEN:
            updateTower(pieces, i, j);
            updateBishop(pieces, i, j);
        break;
        case CAPAKNIGHT:
            updateKnight(pieces, i, j);
        break;
        case ARCHBISHOP:
            updateBishop(pieces, i, j);
            updateKnight(pieces, i, j);
        break;
        case CHANCELER:
            updateTower(pieces, i, j);
            updateKnight(pieces, i, j);
        break;
        case CAPAKING:
            updateKing(pieces, i, j);
        break;
    }

}

void CapaCheckMate::updateTower(capapiece pieces[8][10], int i, int j){
    bool stop = false;
    int k;
    if(i < 7){ //front
        for(k = i+1; k <= 7 && !stop; k++){ //while  in the board and we've not found an enemy yet
            if(pieces[k][j].type == CAPABLANK){
                pieces[i][j].attackBoard[k][j] = 1;
            }
            else if(pieces[k][j].color != pieces[i][j].color){ //enemy piece
                pieces[i][j].attackBoard[k][j] = 1;
                stop = true;
                if(pieces[k][j].type == CAPAKING)
                    stop = false;

            }
            else{ //ally piece
                stop = true;
            }
        }
    }   //do the same for the three other sides of the tower
    if(i > 0){ //below
        stop = false;
        for(k = i - 1; k >= 0 && !stop; k--){
            if(pieces[k][j].type == CAPABLANK){
                pieces[i][j].attackBoard[k][j] = 1;
            }
            else if(pieces[k][j].color != pieces[i][j].color){ //enemy piece
                pieces[i][j].attackBoard[k][j] = 1;
                stop = true;
                if(pieces[k][j].type == CAPAKING)
                    stop = false;
            }
            else{ //ally piece
                stop = true;
            }
        }
    }
    stop = false;
    if(j < 9){ //Right
        for(k = j + 1; k <= 7 && !stop; k++){
            if(pieces[i][k].type == CAPABLANK){
                pieces[i][j].attackBoard[i][k] = 1;
            }
            else if(pieces[i][k].color != pieces[i][j].color){ //enemy piece
                pieces[i][j].attackBoard[i][k] = 1;
                stop = true;
                if(pieces[i][k].type == CAPAKING)
                    stop = false;
            }
            else{ //ally piece
                stop = true;
            }
        }
    }
    stop = false;
    if(j > 0){ //Left
        for(k = j - 1; k >= 0 && !stop; k--){
            if(pieces[i][k].type == CAPABLANK){
                pieces[i][j].attackBoard[i][k] = 1;
            }
            else if(pieces[i][k].color != pieces[i][j].color){ //enemy piece
                pieces[i][j].attackBoard[i][k] = 1;
                stop = true;
                if(pieces[i][k].type == CAPAKING)
                    stop = false;
            }
            else{ //ally piece
                stop = true;
            }
        }
    }
}

void CapaCheckMate::updateBishop(capapiece pieces[8][10], int i, int j){
    int k, p;
    bool stop = false;
    if(i < 7){ //front
        if(j < 9){ //front-right
            for(k = i + 1, p = j + 1; k <= 7 && p <= 7 && !stop; k++, p++){
                if(pieces[k][p].type == CAPABLANK){
                    pieces[i][j].attackBoard[k][p] = 1;
                }
                else if(pieces[k][p].color != pieces[i][j].color){ //enemy piece
                    pieces[i][j].attackBoard[k][p] = 1;
                    stop = true;
                    if(pieces[k][p].type == CAPAKING)
                        stop = false;
                }
                else{ //ally piece
                    stop = true;
                }
            }
        }
        stop = false;
        if(j > 0){ //front-left
            for(k = i + 1, p = j - 1; k <= 7 && p >= 0 && !stop; k++, p--){
                if(pieces[k][p].type == CAPABLANK){
                    pieces[i][j].attackBoard[k][p] = 1;
                }
                else if(pieces[k][p].color != pieces[i][j].color){ //enemy piece
                    pieces[i][j].attackBoard[k][p] = 1;
                    stop = true;
                    if(pieces[k][p].type == CAPAKING)
                        stop = false;
                }
                else{ //ally piece
                    stop = true;
                }
            }
        }
    }
    stop = false;
    if(i > 0){ //back
        if(j < 9){ //back-right
            for(k = i - 1, p = j + 1; k >= 0 && p <= 7 && !stop; k--, p++){
                if(pieces[k][p].type == CAPABLANK){
                    pieces[i][j].attackBoard[k][p] = 1;
                }
                else if(pieces[k][p].color != pieces[i][j].color){ //enemy piece
                    pieces[i][j].attackBoard[k][p] = 1;
                    stop = true;
                    if(pieces[k][p].type == CAPAKING)
                        stop = false;
                }
                else{ //ally piece
                    stop = true;
                }
            }
        }
        stop = false;
        if(j > 0){ //back-right
            for(k = i - 1, p = j - 1; k >= 0 && p >= 0 && !stop; k--, p--){
                if(pieces[k][p].type == CAPABLANK){
                    pieces[i][j].attackBoard[k][p] = 1;
                }
                else if(pieces[k][p].color != pieces[i][j].color){ //enemy piece
                    pieces[i][j].attackBoard[k][p] = 1;
                    stop = true;
                    if(pieces[k][p].type == CAPAKING)
                        stop = false;
                }
                else{ //ally piece
                    stop = true;
                }
            }
        }
        stop = false;
    }
}

void CapaCheckMate::updateKnight(capapiece pieces[8][10], int i, int j){
    if(i + 1 < 7){//north squares
        if(j < 9){
            if(pieces[i+2][j+1].type == CAPABLANK){ //front square
                pieces[i][j].attackBoard[i+2][j+1] = 1;
            }
            else if(pieces[i+2][j+1].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i+2][j+1] = 1;
            }
        }
        if(j > 0){
            if(pieces[i+2][j-1].type == CAPABLANK){ //front square
                pieces[i][j].attackBoard[i+2][j-1] = 1;
            }
            else if(pieces[i+2][j-1].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i+2][j-1] = 1;
            }
        }
    }
    if(i - 1 > 0){//south squares
        if(j < 9){
            if(pieces[i-2][j+1].type == CAPABLANK){ //front square
                pieces[i][j].attackBoard[i-2][j+1] = 1;
            }
            else if(pieces[i-2][j+1].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i-2][j+1] = 1;
            }
        }
        if(j > 0){
            if(pieces[i-2][j-1].type == CAPABLANK){ //front square
                pieces[i][j].attackBoard[i-2][j-1] = 1;
            }
            else if(pieces[i-2][j-1].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i-2][j-1] = 1;
            }
        }
    }
    if(i < 7){
        if(j + 1 < 9){
            if(pieces[i+1][j+2].type == CAPABLANK){ //front square
                pieces[i][j].attackBoard[i+1][j+2] = 1;
            }
            else if(pieces[i+1][j+2].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i+1][j+2] = 1;
            }
        }
        if(j - 1 > 0){
            if(pieces[i+1][j-2].type == CAPABLANK){ //front square
                pieces[i][j].attackBoard[i+1][j-2] = 1;
            }
            else if(pieces[i+1][j-2].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i+1][j-2] = 1;
            }
        }
    }
    if(i > 0){
        if(j + 1 < 9){
            if(pieces[i-1][j+2].type == CAPABLANK){ //front square
                pieces[i][j].attackBoard[i-1][j+2] = 1;
            }
            else if(pieces[i-1][j+2].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i-1][j+2] = 1;
            }
        }
        if(j - 1 > 0){
            if(pieces[i-1][j-2].type == CAPABLANK){ //front square
                pieces[i][j].attackBoard[i-1][j-2] = 1;
            }
            else if(pieces[i-1][j-2].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i-1][j-2] = 1;
            }
        }
    }
}

void CapaCheckMate::updateKing(capapiece pieces[8][10], int i, int j){
    if(i < 7){ //for the king, test individually the 8 possible squares he can go
        if(pieces[i+1][j].type == CAPABLANK){ //front square
            pieces[i][j].attackBoard[i+1][j] = 1;
        }
        else if(pieces[i+1][j].color != pieces[i][j].color){
            pieces[i][j].attackBoard[i+1][j] = 1;
        }
        if(j < 9){ //front-right square
            if(pieces[i+1][j+1].type == CAPABLANK){
                pieces[i][j].attackBoard[i+1][j+1] = 1;
            }
            else if(pieces[i+1][j+1].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i+1][j+1] = 1;
            }
        }
        if(j > 0){ //front-left square
            if(pieces[i+1][j-1].type == CAPABLANK){
                pieces[i][j].attackBoard[i+1][j-1] = 1;
            }
            else if(pieces[i+1][j-1].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i+1][j-1] = 1;
            }
        }
    }
    if(j < 9){ //right square
        if(pieces[i][j+1].type == CAPABLANK){
                pieces[i][j].attackBoard[i][j+1] = 1;
            }
            else if(pieces[i][j+1].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i][j+1] = 1;
            }
    }
    if(j > 0){ //left square
        if(pieces[i][j-1].type == CAPABLANK){
                pieces[i][j].attackBoard[i][j-1] = 1;
            }
            else if(pieces[i][j-1].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i][j-1] = 1;
            }
    }
    if(i > 0){
        if(pieces[i-1][j].type == CAPABLANK){ //back square
            pieces[i][j].attackBoard[i-1][j] = 1;
        }
        else if(pieces[i-1][j].color != pieces[i][j].color){
            pieces[i][j].attackBoard[i-1][j] = 1;
        }
        if(j < 9){ //back-right square
            if(pieces[i-1][j+1].type == CAPABLANK){
                pieces[i][j].attackBoard[i-1][j+1] = 1;
            }
            else if(pieces[i-1][j+1].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i-1][j+1] = 1;
            }
        }
        if(j > 0){ //back-left square
            if(pieces[i-1][j-1].type == CAPABLANK){
                pieces[i][j].attackBoard[i-1][j-1] = 1;
            }
            else if(pieces[i-1][j-1].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i-1][j-1] = 1;
            }
        }
    }
}

//for each piece, update the matrix indicating what squares they are attacking
void CapaCheckMate::updateAttackBoard(capapiece board[8][10]){
    int i, j;
    resetAttackBoard(board);
    for(i = 0; i < 8; i++){
        for(j = 0; j < 10; j++){
            if(board[i][j].type != CAPABLANK){
                updateBoard(board, board[i][j].type, i, j);
            }
        }
    }
}

bool CapaCheckMate::testCheck(capapiece pieces[8][10], int color){ //color is the opposite color of the king I want to check if it is in check.
    int i, j, iKing, jKing;
    for(i = 0; i < 8; i++){
        for(j = 0; j < 10; j++){
            if(pieces[i][j].color != color && pieces[i][j].type == CAPAKING){
                iKing = i;
                jKing = j;
                break;
            }
        }
    }
    for(i = 0; i < 8; i++){
        for(j = 0; j < 10; j++){
            if(pieces[i][j].color == color){ //use the color to test only for my pieces, instead of all pieces.
                if(testKingAttack(pieces[i][j], iKing, jKing)) return true;
            }
        }
    }
    return false;
}

bool CapaCheckMate::testCheckMate(capapiece pieces[8][10], int color){
    int i, j, iKing, jKing;
    bool stop = false;
    for(i = 0; i < 8; i++){
        for(j = 0; j < 10; j++){
            if(pieces[i][j].color == !color && pieces[i][j].type == CAPAKING){
                iKing = i;
                jKing = j;
                break;
            }
        }
    }
    cout << "The king is at " << iKing << " " << jKing << endl;
    if(!testKingMove(pieces, iKing, jKing)){
        if(!testCaptureMove(pieces, iKing, jKing)){
            if(!testBlockMove(pieces, iKing, jKing)){
                cout << "No one can block" << endl;
                return true;
            }
            cout << "No one can capture" << endl;
        }
        cout << "King cant move" << endl;
    }
    return false;
}

bool CapaCheckMate::testKingMove(capapiece pieces[8][10], int iKing, int jKing){
    int squares = 8, i, j;
    int color = pieces[iKing][jKing].color;
    if(iKing + 1 < 8){
        if(pieces[iKing + 1][jKing].type == CAPABLANK){
            for(i = 0; i < 8; i++){
                for(j = 0; j < 10; j++){
                    if(pieces[i][j].color != color && pieces[i][j].attackBoard[iKing+1][jKing]){
                        squares--;
                        i = 8;
                        j = 10;
                    }
                }
            }
        }
        else squares--;
        if(jKing - 1 > 0){
            if(pieces[iKing + 1][jKing - 1].type == CAPABLANK){
                for(i = 0; i < 8; i++){
                    for(j = 0; j < 10; j++){
                        if(pieces[i][j].color == !color && pieces[i][j].attackBoard[iKing+1][jKing-1]){
                            squares--;
                            i = 8;
                            j = 10;
                        }
                    }
                }
            }
            else squares--;
        }
        else squares--;
        if(jKing + 1 < 10){
            if(pieces[iKing + 1][jKing + 1].type == CAPABLANK){
                for(i = 0; i < 8; i++){
                    for(j = 0; j < 10; j++){
                        if(pieces[i][j].color == !color && pieces[i][j].attackBoard[iKing+1][jKing+1]){
                            squares--;
                            i = 8;
                            j = 10;
                        }
                    }
                }
            }
            else squares--;
        }
        else squares--;
    }
    else{
        squares -= 3;
    }
    if(iKing - 1 > 0){
        if(pieces[iKing - 1][jKing ].type == CAPABLANK){
            for(i = 0; i < 8; i++){
                for(j = 0; j < 10; j++){
                    if(pieces[i][j].color == !color && pieces[i][j].attackBoard[iKing-1][jKing]){
                        squares--;
                        i = 8;
                        j = 10;
                    }
                }
            }
        }
        else squares--;
        if(jKing - 1 > 0){
            if(pieces[iKing - 1][jKing - 1].type == CAPABLANK){
                for(i = 0; i < 8; i++){
                    for(j = 0; j < 10; j++){
                        if(pieces[i][j].color == !color && pieces[i][j].attackBoard[iKing-1][jKing-1]){
                            squares--;
                            i = 8;
                            j = 10;
                        }
                    }
                }
            }
            else squares--;
        }
        else squares--;
        if(jKing + 1 < 10){
            if(pieces[iKing - 1][jKing + 1].type == CAPABLANK){
                for(i = 0; i < 8; i++){
                    for(j = 0; j < 10; j++){
                        if(pieces[i][j].color == !color && pieces[i][j].attackBoard[iKing-1][jKing+1]){
                            squares--;
                            i = 8;
                            j = 10;
                        }
                    }
                }
            }
            else squares--;
        }
        else squares--;
    }
    else{
        squares -= 3;
    }
    if(jKing + 1 < 10){
        if(pieces[iKing][jKing + 1].type == CAPABLANK){
            for(i = 0; i < 8; i++){
                for(j = 0; j < 10; j++){
                    if(pieces[i][j].color == !color && pieces[i][j].attackBoard[iKing][jKing+1]){
                        squares--;
                        i = 8;
                        j = 10;
                    }
                }
            }
        }
        else squares--;
    }
    else squares--;
    if(jKing - 1 > 0){
        if(pieces[iKing][jKing - 1].type == CAPABLANK){
            for(i = 0; i < 8; i++){
                for(j = 0; j < 10; j++){
                    if(pieces[i][j].color == !color && pieces[i][j].attackBoard[iKing][jKing-1]){
                        squares--;
                        i = 8;
                        j = 10;
                    }
                }
            }
        }
        else squares--;
    }
    if(squares > 0) return true;
    return false;
}

bool CapaCheckMate::testBlockQueen(capapiece pieces[8][10], int iQueen, int jQueen, int iKing, int jKing){
    if(testBlockBishop(pieces, iQueen, jQueen, iKing, jKing) ||
       testBlockTower(pieces, iQueen, jQueen, iKing, jKing)){
        return true;
    }
    return false;
}

bool CapaCheckMate::testBlockTower(capapiece pieces[8][10], int iTower, int jTower, int iKing, int jKing){
    int i, j, k;
    int color = pieces[iKing][jKing].color;
    if(iTower == iKing){
        if(jTower < jKing){
            for(i = 0; i < 8; i++){
                for(j = 0; j < 10; j++){
                    if(pieces[i][j].color == color && pieces[i][j].type != CAPAKING){
                        for(k = jTower + 1; k < jKing; k++){
                            if(pieces[i][j].attackBoard[iTower][k] == 1){
                                if(testIfStillInCheck(pieces, i, j, iTower, k)) return false;
                                return true;
                            }
                            else if(pieces[i][j].type == CAPAPAWN){
                                if(pieces[i][j].color == 1){
                                    if(i + 1 == iTower && j == k){
                                        if(testIfStillInCheck(pieces, i, j, iTower, k)) return false;
                                        return true;
                                    }
                                    else if(!pieces[i][j].hasMoved && i + 2 == iTower && j == k){
                                        if(testIfStillInCheck(pieces, i, j, iTower, k)) return false;
                                        return true;
                                    }
                                }
                                else{
                                    if(i - 1 == iTower && j == k){
                                        if(testIfStillInCheck(pieces, i, j, iTower, k)) return false;
                                        return true;
                                    }
                                    else if(!pieces[i][j].hasMoved && i - 2 == iTower && j == k){
                                        if(testIfStillInCheck(pieces, i, j, iTower, k)) return false;
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            return false;
        }
        else{
            for(i = 0; i < 8; i++){
                for(j = 0; j < 10; j++){
                    if(pieces[i][j].color == color && pieces[i][j].type != CAPAKING){
                        for(k = jTower - 1; k > jKing; k--){
                            if(pieces[i][j].attackBoard[iTower][k] == 1){
                                if(testIfStillInCheck(pieces, i, j, iTower, k)) return false;
                                return true;
                            }
                            else if(pieces[i][j].type == CAPAPAWN){
                                if(pieces[i][j].color == 1){
                                    if(i + 1 == iTower && j == k){
                                        if(testIfStillInCheck(pieces, i, j, iTower, k)) return false;
                                        return true;
                                    }
                                    else if(!pieces[i][j].hasMoved && i + 2 == iTower && j == k){
                                        if(testIfStillInCheck(pieces, i, j, iTower, k)) return false;
                                        return true;
                                    }
                                }
                                else{
                                    if(i - 1 == iTower && j == k){
                                        if(testIfStillInCheck(pieces, i, j, iTower, k)) return false;
                                        return true;
                                    }
                                    else if(!pieces[i][j].hasMoved && i - 2 == iTower && j == k){
                                        if(testIfStillInCheck(pieces, i, j, iTower, k)) return false;
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            return false;
        }
    }
    else if(jTower == jKing){
        if(iTower < iKing){
            for(i = 0; i < 8; i++){
                for(j = 0; j < 10; j++){
                    if(pieces[i][j].color == color && pieces[i][j].type != CAPAKING){
                        for(k = iTower + 1; k < iKing; k++){
                            if(pieces[i][j].attackBoard[k][jTower] == 1){
                                if(testIfStillInCheck(pieces, i, j, k, jTower)) return false;
                                return true;
                            }

                        }
                    }
                }
            }
            return false;
        }
        else{
            for(i = 0; i < 8; i++){
                for(j = 0; j < 10; j++){
                    if(pieces[i][j].color == color && pieces[i][j].type != CAPAKING){
                        for(k = iTower - 1; k > iKing; k--){
                            if(pieces[i][j].attackBoard[k][jTower] == 1){
                               if(testIfStillInCheck(pieces, i, j, k, jTower)) return false;
                                return true;
                            }
                        }
                    }
                }
            }
            return false;
        }
    }
    return false;
}

bool CapaCheckMate::testBlockBishop(capapiece pieces[8][10], int iBishop, int jBishop, int iKing, int jKing){
    int i, j, k, p;
    int color = pieces[iKing][jKing].color;
    if(iKing > iBishop){
        if(jKing > jBishop){
            for(i = 0; i < 8; i++){
                for(j = 0; j < 10; j++){
                    if(pieces[i][j].color == color){
                        for(k = iBishop + 1, p = jBishop + 1; k < iKing && p < jKing; k++, p++){
                            if(pieces[i][j].attackBoard[k][p] == 1){
                                if(testIfStillInCheck(pieces, i, j, k, p)) return false;
                                return true;
                            }
                            else if(pieces[i][j].type == CAPAPAWN){
                                if(pieces[i][j].color == 1){
                                    if(i + 1 == k && j == p){
                                        if(testIfStillInCheck(pieces, i, j, k, p)) return false;
                                        return true;
                                    }
                                    else if(!pieces[i][j].hasMoved && i + 2 == k && j == p){
                                        if(testIfStillInCheck(pieces, i, j, k, p)) return false;
                                        return true;
                                    }
                                }
                                else{
                                    if(i - 1 == k && j == p){
                                        if(testIfStillInCheck(pieces, i, j, k, p)) return false;
                                        return true;
                                    }
                                    else if(!pieces[i][j].hasMoved && i - 2 == k && j == p){
                                        if(testIfStillInCheck(pieces, i, j, k, p)) return false;
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            return false;
        }
        else{
            for(i = 0; i < 8; i++){
                for(j = 0; j < 10; j++){
                    if(pieces[i][j].color == color){
                        for(k = iBishop + 1, p = jBishop - 1; k < iKing && p > jKing; k++, p--){
                            if(pieces[i][j].attackBoard[k][p] == 1){
                                if(testIfStillInCheck(pieces, i, j, k, p)) return false;
                                return true;
                            }
                            else if(pieces[i][j].type == CAPAPAWN){
                                if(pieces[i][j].color == 1){
                                    if(i + 1 == k && j == p){
                                        if(testIfStillInCheck(pieces, i, j, k, p)) return false;
                                        return true;
                                    }
                                    else if(!pieces[i][j].hasMoved && i + 2 == k && j == p){
                                        if(testIfStillInCheck(pieces, i, j, k, p)) return false;
                                        return true;
                                    }
                                }
                                else{
                                    if(i - 1 == k && j == p){
                                        if(testIfStillInCheck(pieces, i, j, k, p)) return false;
                                        return true;
                                    }
                                    else if(!pieces[i][j].hasMoved && i - 2 == k && j == p){
                                        if(testIfStillInCheck(pieces, i, j, k, p)) return false;
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            return false;
        }
    }
    else if(iKing < iBishop){
        if(jKing > jBishop){
            for(i = 0; i < 8; i++){
                for(j = 0; j < 10; j++){
                    if(pieces[i][j].color == color){
                        for(k = iBishop - 1, p = jBishop + 1; k > iKing && p < jKing; k--, p++){
                            if(pieces[i][j].attackBoard[k][p] == 1){
                                if(testIfStillInCheck(pieces, i, j, k, p)) return false;
                                return true;
                            }
                            else if(pieces[i][j].type == CAPAPAWN){
                                if(pieces[i][j].color == 1){
                                    if(i + 1 == k && j == p){
                                        if(testIfStillInCheck(pieces, i, j, k, p)) return false;
                                        return true;
                                    }
                                    else if(!pieces[i][j].hasMoved && i + 2 == k && j == p){
                                        if(testIfStillInCheck(pieces, i, j, k, p)) return false;
                                        return true;
                                    }
                                }
                                else{
                                    if(i - 1 == k && j == p){
                                        if(testIfStillInCheck(pieces, i, j, k, p)) return false;
                                        return true;
                                    }
                                    else if(!pieces[i][j].hasMoved && i - 2 == k && j == p){
                                        if(testIfStillInCheck(pieces, i, j, k, p)) return false;
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            return false;
        }
        else{
            for(i = 0; i < 8; i++){
                for(j = 0; j < 10; j++){
                    if(pieces[i][j].color == color){
                        for(k = iBishop - 1, p = jBishop - 1; k > iKing && p > jKing; k--, p--){
                            if(pieces[i][j].attackBoard[k][p] == 1){
                                if(testIfStillInCheck(pieces, i, j, k, p)) return false;
                                return true;
                            }
                            else if(pieces[i][j].type == CAPAPAWN){
                                if(pieces[i][j].color == 1){
                                    if(i + 1 == k && j == p){
                                        if(testIfStillInCheck(pieces, i, j, k, p)) return false;
                                        return true;
                                    }
                                    else if(!pieces[i][j].hasMoved && i + 2 == k && j == p){
                                        if(testIfStillInCheck(pieces, i, j, k, p)) return false;
                                        return true;
                                    }
                                }
                                else{
                                    if(i - 1 == k && j == p){
                                        if(testIfStillInCheck(pieces, i, j, k, p)) return false;
                                        return true;
                                    }
                                    else if(!pieces[i][j].hasMoved && i - 2 == k && j == p){
                                        if(testIfStillInCheck(pieces, i, j, k, p)) return false;
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            return false;
        }
    }
    return false;
}

//The most complicated test. Test if any of the enemy pieces can block the path that is attacking the king.
bool CapaCheckMate::testBlockMove(capapiece pieces[8][10], int iKing, int jKing){
    int i, j;
    int color = pieces[iKing][jKing].color;
    for(i = 0; i < 8; i++){
        for(j = 0; j < 10; j++){
            if(pieces[i][j].color != color && pieces[i][j].attackBoard[iKing][jKing] == 1){ //find the piece that is attacking the king.
                switch(pieces[i][j].type){
                    case CAPAQUEEN:
                        return testBlockQueen(pieces, i, j, iKing, jKing);
                    break;
                    case CAPATOWER:
                        return testBlockTower(pieces, i, j, iKing, jKing);
                    break;
                    case CAPABISHOP:
                        return testBlockBishop(pieces, i, j, iKing, jKing);
                    break;
                    case ARCHBISHOP:
                        return testBlockBishop(pieces, i, j, iKing, jKing);
                    break;
                    case CHANCELER:
                        return testBlockTower(pieces, i, j, iKing, jKing);
                    break;
                }
            }
        }
    }
    return false;
}

//Test if any enemy piece can capture the piece that is attacking the king
bool CapaCheckMate::testCaptureMove(capapiece pieces[8][10], int iKing, int jKing){
    int i, j;
    bool canCapture = false;
    int color = pieces[iKing][jKing].color;
    for(i = 0; i < 8; i++){
        for(j = 0; j < 10; j++){
            if(pieces[i][j].color != color && pieces[i][j].attackBoard[iKing][jKing] == 1){
                if(testCapture(pieces, i, j)){
                    canCapture = true;
                }
                else{
                    return false;
                }
            }
        }
    }
    return canCapture;
}

//Basically the same algorithm as testCaptureMove, but testing if any of the enemy pieces can capture each piece attacking the king
bool CapaCheckMate::testCapture(capapiece pieces[8][10], int iX, int jX){
    int i, j;
    int color = pieces[iX][jX].color;
    for(i = 0; i < 8; i++){
        for(j = 0; j < 10; j++){
            if(pieces[i][j].color != color && pieces[i][j].attackBoard[iX][jX] == 1){
                if(pieces[i][j].type == CAPAKING){
                    pieces[i][j].changePiece(pieces, iX, jX, i, j);
                    updateAttackBoard(pieces);
                    if(testCheck(pieces, color)){
                        pieces[iX][jX].changeBack(pieces, iX, jX, i, j);
                        updateAttackBoard(pieces);
                        return false;
                    }
                    pieces[iX][jX].changeBack(pieces, iX, jX, i, j);
                    updateAttackBoard(pieces);
                }
                return true;
            }
        }
    }
    return false;
}

bool CapaCheckMate::testKingAttack(capapiece piece, int iKing, int jKing){
    if(piece.attackBoard[iKing][jKing] == 1) return true;
    return false;
}

