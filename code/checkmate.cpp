#include <SFML/Graphics.hpp>
#include "headers/checkmate.h"

using namespace std;

int color;
//Extremely sensitive, enormous and complex algorithm. Do not touch, as only God knows what lies below this comment!

void CheckMate::resetAttackBoard(Piece board[8][10]){
    int i, j, k, p;
    for(i = 0; i < 8; i++){
        for(j = 0; j < columns; j++){
            for(k = 0; k < 8; k++){
                for(p = 0; p < columns; p++){
                    board[i][j].attackBoard[k][p] = 0;
                }
            }

        }
    }
}

bool CheckMate::testCheck(Piece pieces[8][10], int color){ //color is the opposite color of the king I want to check if it is in check.
    int i, j, iKing, jKing;

    for(i = 0; i < 8; i++){
        for(j = 0; j < columns; j++){
            if(pieces[i][j].color != color && pieces[i][j].type == KING){
                iKing = i;
                jKing = j;
                break;
            }
        }
    }
    for(i = 0; i < 8; i++){
        for(j = 0; j < columns; j++){
            if(pieces[i][j].color == color){ //use the color to test only for my pieces, instead of all pieces.
                if(testKingAttack(pieces[i][j], iKing, jKing)) return true;
            }
        }
    }
    return false;
}

bool CheckMate::testCheckMate(Piece pieces[8][10], int color){
    int i, j, iKing, jKing;
    bool stop = false;
    cout << "Testing checkmate for king (" << !color << "). \n";
    for(i = 0; i < 8; i++){
        for(j = 0; j < columns; j++){
            if(pieces[i][j].color == !color && pieces[i][j].type == KING){
                cout << "Found the king!\n";
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
    cout << "Test failed!\n";
    return false;
}

bool CheckMate::testIfStillInCheck(Piece pieces[8][10], int i, int j, int iX, int iY){
    int color = pieces[i][j].color;
    if(pieces[i][j].type == KING) return true;
    cout << "Type: " << static_cast<int>(pieces[i][j].type) << endl;
    pieces[i][j].changePiece(pieces, iX, iY, i, j);
    updateAttackBoard(pieces);
    for(int k = 0; k < 8; k++){
        for(int p = 0; p < 8; p++){
            cout << pieces[4][4].attackBoard[k][p];
        }
        cout << endl;
    }
    if(testCheck(pieces, !color)){
        pieces[i][j].changeBack(pieces, iX, iY, i, j);
        updateAttackBoard(pieces);
        return true; //yes, still in check
    }
    pieces[i][j].changeBack(pieces, iX, iY, i, j);
    updateAttackBoard(pieces);
    return false;
}

void CheckMate::updateBoard(Piece pieces[8][10], TYPE t, int i, int j){
    bool stop = false;
    switch(t){
        case PAWN:
            if(pieces[i][j].color == 1){//The test is inverted for the black and white pawn
               if(i + 1 < 8){ //The pawn can attack the two diagonal squares directly in front of him until the 7th rank
                    if(j + 1 < columns){ //test if the sides are inside the board
                        if(pieces[i+1][j+1].color != pieces[i][j].color){ //if the diagonal squares are from a different color
                            pieces[i][j].attackBoard[i+1][j+1] = 1;
                        }
                        if(j - 1 >= 0){ //same here
                            if(pieces[i+1][j-1].color != pieces[i][j].color){
                                pieces[i][j].attackBoard[i+1][j-1] = 1;
                            }
                        }
                    }
                }
            }
            else{
                if(i - 1 >= 0){ //Do not pass the board! //MODIFY!!!!!!!!!!!!!! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    if(j + 1 < columns){ //test if the sides are inside the board
                        if(pieces[i-1][j+1].color != pieces[i][j].color){ //if the diagonal squares are from a different color
                            pieces[i][j].attackBoard[i-1][j+1] = 1;
                        }
                        if(j - 1 >= 0){ //same here
                            if(pieces[i-1][j-1].color != pieces[i][j].color){
                                pieces[i][j].attackBoard[i-1][j-1] = 1;
                            }
                        }
                    }
                }
            }

        break;
        case TOWER:
            updateTower(pieces, i, j);
        break;
        case BISHOP:
            updateBishop(pieces, i, j);
        break;
        case QUEEN:
            updateTower(pieces, i, j);
            updateBishop(pieces, i, j);
        break;
        case KNIGHT:
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
        case KING:
            updateKing(pieces, i, j);
        break;
    }

}

void CheckMate::updateTower(Piece pieces[8][10], int i, int j){
    bool stop = false;
    int k;
    if(i < 7){ //front
        for(k = i+1; k <= 7 && !stop; k++){ //while  in the board and we've not found an enemy yet
            if(pieces[k][j].type == BLANK){
                pieces[i][j].attackBoard[k][j] = 1;
            }
            else if(pieces[k][j].color != pieces[i][j].color){ //enemy piece
                pieces[i][j].attackBoard[k][j] = 1;
                stop = true;
                if(pieces[k][j].type == KING)
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
            if(pieces[k][j].type == BLANK){
                pieces[i][j].attackBoard[k][j] = 1;
            }
            else if(pieces[k][j].color != pieces[i][j].color){ //enemy piece
                pieces[i][j].attackBoard[k][j] = 1;
                stop = true;
                if(pieces[k][j].type == KING)
                    stop = false;
            }
            else{ //ally piece
                stop = true;
            }
        }
    }
    stop = false;
    if(j < columns - 1){ //Right
        for(k = j + 1; k <= columns - 1 && !stop; k++){
            if(pieces[i][k].type == BLANK){
                pieces[i][j].attackBoard[i][k] = 1;
            }
            else if(pieces[i][k].color != pieces[i][j].color){ //enemy piece
                pieces[i][j].attackBoard[i][k] = 1;
                stop = true;
                if(pieces[i][k].type == KING)
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
            if(pieces[i][k].type == BLANK){
                pieces[i][j].attackBoard[i][k] = 1;
            }
            else if(pieces[i][k].color != pieces[i][j].color){ //enemy piece
                pieces[i][j].attackBoard[i][k] = 1;
                stop = true;
                if(pieces[i][k].type == KING)
                    stop = false;
            }
            else{ //ally piece
                stop = true;
            }
        }
    }
}

void CheckMate::updateBishop(Piece pieces[8][10], int i, int j){
    int k, p;
    bool stop = false;
    if(i < 7){ //front
        if(j < columns - 1){ //front-right
            for(k = i + 1, p = j + 1; k <= 7 && p <= columns - 1 && !stop; k++, p++){
                if(pieces[k][p].type == BLANK){
                    pieces[i][j].attackBoard[k][p] = 1;
                }
                else if(pieces[k][p].color != pieces[i][j].color){ //enemy piece
                    pieces[i][j].attackBoard[k][p] = 1;
                    stop = true;
                    if(pieces[k][p].type == KING)
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
                if(pieces[k][p].type == BLANK){
                    pieces[i][j].attackBoard[k][p] = 1;
                }
                else if(pieces[k][p].color != pieces[i][j].color){ //enemy piece
                    pieces[i][j].attackBoard[k][p] = 1;
                    stop = true;
                    if(pieces[k][p].type == KING)
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
        if(j < 7){ //back-right
            for(k = i - 1, p = j + 1; k >= 0 && p <= columns - 1 && !stop; k--, p++){
                if(pieces[k][p].type == BLANK){
                    pieces[i][j].attackBoard[k][p] = 1;
                }
                else if(pieces[k][p].color != pieces[i][j].color){ //enemy piece
                    pieces[i][j].attackBoard[k][p] = 1;
                    stop = true;
                    if(pieces[k][p].type == KING)
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
                if(pieces[k][p].type == BLANK){
                    pieces[i][j].attackBoard[k][p] = 1;
                }
                else if(pieces[k][p].color != pieces[i][j].color){ //enemy piece
                    pieces[i][j].attackBoard[k][p] = 1;
                    stop = true;
                    if(pieces[k][p].type == KING)
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

void CheckMate::updateKnight(Piece pieces[8][10], int i, int j){
    if(i + 1 < 7){//north squares
        if(j < columns - 1){
            if(pieces[i+2][j+1].type == BLANK){ //front square
                pieces[i][j].attackBoard[i+2][j+1] = 1;
            }
            else if(pieces[i+2][j+1].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i+2][j+1] = 1;
            }
        }
        if(j > 0){
            if(pieces[i+2][j-1].type == BLANK){ //front square
                pieces[i][j].attackBoard[i+2][j-1] = 1;
            }
            else if(pieces[i+2][j-1].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i+2][j-1] = 1;
            }
        }
    }
    if(i - 1 > 0){//south squares
        if(j < columns - 1){
            if(pieces[i-2][j+1].type == BLANK){ //front square
                pieces[i][j].attackBoard[i-2][j+1] = 1;
            }
            else if(pieces[i-2][j+1].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i-2][j+1] = 1;
            }
        }
        if(j > 0){
            if(pieces[i-2][j-1].type == BLANK){ //front square
                pieces[i][j].attackBoard[i-2][j-1] = 1;
            }
            else if(pieces[i-2][j-1].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i-2][j-1] = 1;
            }
        }
    }
    if(i < 7){
        if(j + 1 < columns - 1){
            if(pieces[i+1][j+2].type == BLANK){ //front square
                pieces[i][j].attackBoard[i+1][j+2] = 1;
            }
            else if(pieces[i+1][j+2].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i+1][j+2] = 1;
            }
        }
        if(j - 1 > 0){
            if(pieces[i+1][j-2].type == BLANK){ //front square
                pieces[i][j].attackBoard[i+1][j-2] = 1;
            }
            else if(pieces[i+1][j-2].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i+1][j-2] = 1;
            }
        }
    }
    if(i > 0){
        if(j + 1 < columns - 1){
            if(pieces[i-1][j+2].type == BLANK){ //front square
                pieces[i][j].attackBoard[i-1][j+2] = 1;
            }
            else if(pieces[i-1][j+2].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i-1][j+2] = 1;
            }
        }
        if(j - 1 > 0){
            if(pieces[i-1][j-2].type == BLANK){ //front square
                pieces[i][j].attackBoard[i-1][j-2] = 1;
            }
            else if(pieces[i-1][j-2].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i-1][j-2] = 1;
            }
        }
    }
}

void CheckMate::updateKing(Piece pieces[8][10], int i, int j){
    if(i < 7){ //for the king, test individually the 8 possible squares he can go
        if(pieces[i+1][j].type == BLANK){ //front square
            pieces[i][j].attackBoard[i+1][j] = 1;
        }
        else if(pieces[i+1][j].color != pieces[i][j].color){
            pieces[i][j].attackBoard[i+1][j] = 1;
        }
        if(j < columns - 1){ //front-right square
            if(pieces[i+1][j+1].type == BLANK){
                pieces[i][j].attackBoard[i+1][j+1] = 1;
            }
            else if(pieces[i+1][j+1].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i+1][j+1] = 1;
            }
        }
        if(j > 0){ //front-left square
            if(pieces[i+1][j-1].type == BLANK){
                pieces[i][j].attackBoard[i+1][j-1] = 1;
            }
            else if(pieces[i+1][j-1].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i+1][j-1] = 1;
            }
        }
    }
    if(j < columns - 1){ //right square
        if(pieces[i][j+1].type == BLANK){
            pieces[i][j].attackBoard[i][j+1] = 1;
        }
        else if(pieces[i][j+1].color != pieces[i][j].color){
            pieces[i][j].attackBoard[i][j+1] = 1;
        }
    }
    if(j > 0){ //left square
        if(pieces[i][j-1].type == BLANK){
                pieces[i][j].attackBoard[i][j-1] = 1;
            }
            else if(pieces[i][j-1].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i][j-1] = 1;
            }
    }
    if(i > 0){
        if(pieces[i-1][j].type == BLANK){ //back square
            pieces[i][j].attackBoard[i-1][j] = 1;
        }
        else if(pieces[i-1][j].color != pieces[i][j].color){
            pieces[i][j].attackBoard[i-1][j] = 1;
        }
        if(j < columns - 1){ //back-right square
            if(pieces[i-1][j+1].type == BLANK){
                pieces[i][j].attackBoard[i-1][j+1] = 1;
            }
            else if(pieces[i-1][j+1].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i-1][j+1] = 1;
            }
        }
        if(j > 0){ //back-left square
            if(pieces[i-1][j-1].type == BLANK){
                pieces[i][j].attackBoard[i-1][j-1] = 1;
            }
            else if(pieces[i-1][j-1].color != pieces[i][j].color){
                pieces[i][j].attackBoard[i-1][j-1] = 1;
            }
        }
    }
}

//for each piece, update the matrix indicating what squares they are attacking
void CheckMate::updateAttackBoard(Piece board[8][10]){
    int i, j;
    resetAttackBoard(board);
    for(i = 0; i < 8; i++){
        for(j = 0; j < columns; j++){
            if(board[i][j].type != BLANK){
                updateBoard(board, board[i][j].type, i, j);
            }
        }
    }
}



bool CheckMate::testKingMove(Piece pieces[8][10], int iKing, int jKing){
    int squares = 8, i, j;
    int color = pieces[iKing][jKing].color;
    if(iKing + 1 < 8){
        if(pieces[iKing + 1][jKing].type == BLANK){
            for(i = 0; i < 8; i++){
                for(j = 0; j < columns; j++){
                    if(pieces[i][j].color != color && pieces[i][j].attackBoard[iKing+1][jKing]){
                        squares--;
                        i = 8;
                        j = columns;
                    }
                }
            }
        }
        else squares--;
        if(jKing - 1 > 0){
            if(pieces[iKing + 1][jKing - 1].type == BLANK){
                for(i = 0; i < 8; i++){
                    for(j = 0; j < columns; j++){
                        if(pieces[i][j].color == !color && pieces[i][j].attackBoard[iKing+1][jKing-1]){
                            squares--;
                            i = 8;
                            j = columns;
                        }
                    }
                }
            }
            else squares--;
        }
        else squares--;
        if(jKing + 1 < columns){
            if(pieces[iKing + 1][jKing + 1].type == BLANK){
                for(i = 0; i < 8; i++){
                    for(j = 0; j < columns; j++){
                        if(pieces[i][j].color == !color && pieces[i][j].attackBoard[iKing+1][jKing+1]){
                            squares--;
                            i = 8;
                            j = columns;
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
        if(pieces[iKing - 1][jKing].type == BLANK){
            for(i = 0; i < 8; i++){
                for(j = 0; j < columns; j++){
                    if(pieces[i][j].color == !color && pieces[i][j].attackBoard[iKing-1][jKing]){
                        squares--;
                        i = 8;
                        j = columns;
                    }
                }
            }
        }
        else squares--;
        if(jKing - 1 > 0){
            if(pieces[iKing - 1][jKing - 1].type == BLANK){
                for(i = 0; i < 8; i++){
                    for(j = 0; j < columns; j++){
                        if(pieces[i][j].color == !color && pieces[i][j].attackBoard[iKing-1][jKing-1]){
                            squares--;
                            i = 8;
                            j = columns;
                        }
                    }
                }
            }
            else squares--;
        }
        else squares--;
        if(jKing + 1 < columns){
            if(pieces[iKing - 1][jKing + 1].type == BLANK){
                for(i = 0; i < 8; i++){
                    for(j = 0; j < columns; j++){
                        if(pieces[i][j].color == !color && pieces[i][j].attackBoard[iKing-1][jKing+1]){
                            squares--;
                            i = 8;
                            j = columns;
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
    if(jKing + 1 < columns){
        if(pieces[iKing][jKing + 1].type == BLANK){
            for(i = 0; i < 8; i++){
                for(j = 0; j < columns; j++){
                    if(pieces[i][j].color == !color && pieces[i][j].attackBoard[iKing][jKing+1]){
                        squares--;
                        i = 8;
                        j = columns;
                    }
                }
            }
        }
        else squares--;
    }
    else squares--;
    if(jKing - 1 > 0){
        if(pieces[iKing][jKing - 1].type == BLANK){
            for(i = 0; i < 8; i++){
                for(j = 0; j < columns; j++){
                    if(pieces[i][j].color == !color && pieces[i][j].attackBoard[iKing][jKing-1]){
                        squares--;
                        i = 8;
                        j = columns;
                    }
                }
            }
        }
        else squares--;
    }
    else squares--;
    if(squares > 0) return true;
    return false;
}

bool CheckMate::testBlockQueen(Piece pieces[8][10], int iQueen, int jQueen, int iKing, int jKing){
    if(testBlockBishop(pieces, iQueen, jQueen, iKing, jKing) ||
       testBlockTower(pieces, iQueen, jQueen, iKing, jKing)){
        return true;
    }
    return false;
}

bool CheckMate::testBlockTower(Piece pieces[8][10], int iTower, int jTower, int iKing, int jKing){
    int i, j, k;
    int color = pieces[iKing][jKing].color;
    if(iTower == iKing){
        if(jTower < jKing){
            for(i = 0; i < 8; i++){
                for(j = 0; j < columns; j++){
                    if(pieces[i][j].color == color && pieces[i][j].type != KING){
                        for(k = jTower + 1; k < jKing; k++){
                            if(pieces[i][j].attackBoard[iTower][k] == 1){
                                if(testIfStillInCheck(pieces, i, j, iTower, k)) return false;
                                return true;
                            }
                            else if(pieces[i][j].type == PAWN){
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
                for(j = 0; j < columns; j++){
                    if(pieces[i][j].color == color && pieces[i][j].type != KING){
                        for(k = jTower - 1; k > jKing; k--){
                            if(pieces[i][j].attackBoard[iTower][k] == 1){
                                if(testIfStillInCheck(pieces, i, j, iTower, k)) return false;
                                return true;
                            }
                            else if(pieces[i][j].type == PAWN){
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
                for(j = 0; j < columns; j++){
                    if(pieces[i][j].color == color && pieces[i][j].type != KING){
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
                for(j = 0; j < columns; j++){
                    if(pieces[i][j].color == color && pieces[i][j].type != KING){
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

bool CheckMate::testBlockBishop(Piece pieces[8][10], int iBishop, int jBishop, int iKing, int jKing){
    int i, j, k, p;
    int color = pieces[iKing][jKing].color;
    if(iKing > iBishop){
        if(jKing > jBishop){
            for(i = 0; i < 8; i++){
                for(j = 0; j < columns; j++){
                    if(pieces[i][j].color == color){
                        for(k = iBishop + 1, p = jBishop + 1; k < iKing && p < jKing; k++, p++){
                            if(pieces[i][j].attackBoard[k][p] == 1){
                                if(testIfStillInCheck(pieces, i, j, k, p)) return false;
                                return true;
                            }
                            else if(pieces[i][j].type == PAWN){
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
                for(j = 0; j < columns; j++){
                    if(pieces[i][j].color == color){
                        for(k = iBishop + 1, p = jBishop - 1; k < iKing && p > jKing; k++, p--){
                            if(pieces[i][j].attackBoard[k][p] == 1){
                                if(testIfStillInCheck(pieces, i, j, k, p)) return false;
                                return true;
                            }
                            else if(pieces[i][j].type == PAWN){
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
                for(j = 0; j < columns; j++){
                    if(pieces[i][j].color == color){
                        for(k = iBishop - 1, p = jBishop + 1; k > iKing && p < jKing; k--, p++){
                            if(pieces[i][j].attackBoard[k][p] == 1){
                                if(testIfStillInCheck(pieces, i, j, k, p)) return false;
                                return true;
                            }
                            else if(pieces[i][j].type == PAWN){
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
                for(j = 0; j < columns; j++){
                    if(pieces[i][j].color == color){
                        for(k = iBishop - 1, p = jBishop - 1; k > iKing && p > jKing; k--, p--){
                            if(pieces[i][j].attackBoard[k][p] == 1){
                                if(testIfStillInCheck(pieces, i, j, k, p)) return false;
                                return true;
                            }
                            else if(pieces[i][j].type == PAWN){
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
bool CheckMate::testBlockMove(Piece pieces[8][10], int iKing, int jKing){
    int i, j;
    int color = pieces[iKing][jKing].color;
    for(i = 0; i < 8; i++){
        for(j = 0; j < columns; j++){
            if(pieces[i][j].color != color && pieces[i][j].attackBoard[iKing][jKing] == 1){ //find the piece that is attacking the king.
                switch(pieces[i][j].type){
                    case QUEEN:
                        return testBlockQueen(pieces, i, j, iKing, jKing);
                    break;
                    case TOWER:
                        return testBlockTower(pieces, i, j, iKing, jKing);
                    break;
                    case BISHOP:
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
bool CheckMate::testCaptureMove(Piece pieces[8][10], int iKing, int jKing){
    int i, j;
    bool canCapture = false;
    int color = pieces[iKing][jKing].color;
    for(i = 0; i < 8; i++){
        for(j = 0; j < columns; j++){
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
bool CheckMate::testCapture(Piece pieces[8][10], int iX, int jX){
    int i, j;
    int color = pieces[iX][jX].color;
    for(i = 0; i < 8; i++){
        for(j = 0; j < columns; j++){
            if(pieces[i][j].color != color && pieces[i][j].attackBoard[iX][jX] == 1){
                if(pieces[i][j].type == KING){
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

bool CheckMate::testKingAttack(Piece piece, int iKing, int jKing){
    if(piece.attackBoard[iKing][jKing] == 1) return true;
    return false;
}
