#include <SFML/Graphics.hpp>
#include "headers/capapiece.h"
#include "headers/capacheckmate.h"
#include <iostream>
#include <math.h>
using namespace std;

CapaCheckMate testCapaCheck;

CAPATYPE typeCapaChange;
int colorCapaChange;
string codeCapaChange;

/*Castling conditions:
1 - The king and the chosen rook are on the player's first rank.
2 - Neither the king nor the chosen rook have previously moved.
3 - There are no pieces between the king and the chosen rook.
4 - The king is not currently in check.
5 - The king does not pass through a square that is attacked by an enemy piece.
6 - The king does not end up in check. (True of any legal move.)
*/

void capapiece::changePiece(capapiece board[8][10], int i, int j, int iP, int jP){
    typeCapaChange = board[i][j].type;
    colorCapaChange = board[i][j].color;
    codeCapaChange = board[i][j].code;

    board[i][j].type = board[iP][jP].type;
    board[i][j].code = board[iP][jP].code;
    board[i][j].color = board[iP][jP].color;

    board[iP][jP].type = CAPABLANK;
    board[iP][jP].code = "";
    board[iP][jP].color = -1;
}

void capapiece::changeBack(capapiece board[8][10], int i, int j, int iP, int jP){
    board[iP][jP].type = board[i][j].type;
    board[iP][jP].code = board[i][j].code;
    board[iP][jP].color = board[i][j].color;

    board[i][j].type = typeCapaChange;
    board[i][j].code = codeCapaChange;
    board[i][j].color = colorCapaChange;
}

bool capapiece::pawnMovement(capapiece board[8][10], int i, int j, int iP, int jP, bool check){
    if(board[iP][jP].color == 1){
        if((i == iP + 1 && j == jP) || (iP == 1 && i == iP + 2 && j == jP)){
            changePiece(board, i, j, iP, jP);
            testCapaCheck.updateAttackBoard(board);
            if(testCapaCheck.testCheck(board, !board[i][j].color)){
                changeBack(board, i, j, iP, jP);
                testCapaCheck.updateAttackBoard(board);
                cout << "You must not stay in check!" << endl;
                return false;
            }
            moves++;
            return true;
        }
        if(iP == 4 && i == iP + 1){
            if(jP > 0 && j == jP - 1 && board[iP][jP-1].color == 0 && board[iP][jP-1].moves == 1 && board[iP][jP-1].type == CAPAPAWN){
                changePiece(board, i, j, iP, jP);
                testCapaCheck.updateAttackBoard(board);
                if(testCapaCheck.testCheck(board, !board[i][j].color)){
                    changeBack(board, i, j, iP, jP);
                    testCapaCheck.updateAttackBoard(board);
                    cout << "You must not stay in check!" << endl;
                    return false;
                }
                board[iP][jP-1].color = -1;
                board[iP][jP-1].code = "";
                board[iP][jP-1].type = CAPABLANK;
                return true;
            }
            else if(jP < 7 && j == jP + 1 && board[iP][jP+1].color == 0 && board[iP][jP+1].moves == 1 && board[iP][jP+1].type == CAPAPAWN){ //En Passant
                changePiece(board, i, j, iP, jP);
                testCapaCheck.updateAttackBoard(board);
                if(testCapaCheck.testCheck(board, !board[i][j].color)){
                    changeBack(board, i, j, iP, jP);
                    testCapaCheck.updateAttackBoard(board);
                    cout << "You must not stay in check!" << endl;
                    return false;
                }
                board[iP][jP+1].color = -1;
                board[iP][jP+1].code = "";
                board[iP][jP+1].type = CAPABLANK;
                return true;
            }
        }
        return false;
    }
    else{
        if((i == iP - 1 && j == jP) || (iP == 6 && i == iP - 2 && j == jP)){
            changePiece(board, i, j, iP, jP);
            testCapaCheck.updateAttackBoard(board);
            if(testCapaCheck.testCheck(board, !board[i][j].color)){
                changeBack(board, i, j, iP, jP);
                testCapaCheck.updateAttackBoard(board);
                cout << "You must not stay in check!" << endl;
                return false;
            }
            moves++;
            return true;
        }
        if(iP == 3 && i == iP - 1 ){
            if(jP > 0 && j == jP - 1 && board[iP][jP-1].color == 0 && board[iP][jP-1].moves == 1 && board[iP][jP-1].type == CAPAPAWN){
                changePiece(board, i, j, iP, jP);
                testCapaCheck.updateAttackBoard(board);
                if(testCapaCheck.testCheck(board, !board[i][j].color)){
                    changeBack(board, i, j, iP, jP);
                    testCapaCheck.updateAttackBoard(board);
                    cout << "You must not stay in check!" << endl;
                    return false;
                }
                board[iP][jP-1].color = -1;
                board[iP][jP-1].code = "";
                board[iP][jP-1].type = CAPABLANK;
                return true;
            }
            else if(jP < 7 && j == jP + 1 && board[iP][jP+1].color == 0 && board[iP][jP+1].moves == 1 && board[iP][jP+1].type == CAPAPAWN){ //En Passant
                changePiece(board, i, j, iP, jP);
                testCapaCheck.updateAttackBoard(board);
                if(testCapaCheck.testCheck(board, !board[i][j].color)){
                    changeBack(board, i, j, iP, jP);
                    testCapaCheck.updateAttackBoard(board);
                    cout << "You must not stay in check!" << endl;
                    return false;
                }
                board[iP][jP+1].color = -1;
                board[iP][jP+1].code = "";
                board[iP][jP+1].type = CAPABLANK;
                return true;
            }
        }
        return false;
    }
}

bool capapiece::towerMovement(capapiece board[8][10], int i, int j, int iP, int jP, bool check){
    bool control = false;
    int k;
    if(i == iP){ //same row
        if(j > jP){ //to the right
            for(k = jP + 1; k < j && !control; k++){ //loop until reach the piece clicked
                if(board[i][k].type != CAPABLANK){ //test if all the pieces between the two are blank
                    control = true; //stop the loop
                }
            }
            if(!control){ //if they are, the piece can be captured
                changePiece(board, i, j, iP, jP);
                testCapaCheck.updateAttackBoard(board);
                if(testCapaCheck.testCheck(board, !board[i][j].color)){
                    changeBack(board, i, j, iP, jP);
                    testCapaCheck.updateAttackBoard(board);
                    cout << "You must not stay in check!" << endl;
                    return false;
                }
                return true;
            }
        }
        else{ //to the left
            for(k = jP - 1; k > j && !control; k--){ //loop until reach the piece clicked
                if(board[i][k].type != CAPABLANK){ //test if all the pieces between the two are blank
                    control = true; //stop the loop
                }
            }
            if(!control){ //if they are, the piece can be captured
                changePiece(board, i, j, iP, jP);
              //  if(check){
                    testCapaCheck.updateAttackBoard(board);
                    if(testCapaCheck.testCheck(board, !board[i][j].color)){
                        changeBack(board, i, j, iP, jP);
                        testCapaCheck.updateAttackBoard(board);
                        cout << "You must not stay in check!" << endl;
                        return false;
                    }
              //  }
                return true;
            }
        }
    }
    else if(j == jP){ //same column
        if(i > iP){ //to the front
            for(k = iP + 1; k < i && !control; k++){ //loop until reach the piece clicked
                if(board[k][j].type != CAPABLANK){ //test if all the pieces between the two are blank
                    control = true; //stop the loop
                }
            }
            if(!control){ //if they are, the piece can be captured
                changePiece(board, i, j, iP, jP);
              //  if(check){
                    testCapaCheck.updateAttackBoard(board);
                    if(testCapaCheck.testCheck(board, !board[i][j].color)){
                        changeBack(board, i, j, iP, jP);
                        testCapaCheck.updateAttackBoard(board);
                        cout << "You must not stay in check!" << endl;
                        return false;
                    }
             //   }
                return true;
            }
        }
        else{ //to the left
            for(k = iP - 1; k > i && !control; k--){ //loop until reach the piece clicked
                if(board[k][j].type != CAPABLANK){ //test if all the pieces between the two are blank
                    control = true; //stop the loop
                }
            }
            if(!control){ //if they are, the piece can be captured
                changePiece(board, i, j, iP, jP);
             //   if(check){
                    testCapaCheck.updateAttackBoard(board);
                    if(testCapaCheck.testCheck(board, !board[i][j].color)){
                        changeBack(board, i, j, iP, jP);
                        testCapaCheck.updateAttackBoard(board);
                        cout << "You must not stay in check!" << endl;
                        return false;
                    }
              //  }
                return true;
            }
        }

    }
    return false;
}

bool capapiece::bishopMovement(capapiece board[8][10], int i, int j, int iP, int jP, bool check){
    bool control = false;
    int k, p;
    if(abs(i - iP) == abs(j - jP)){ //if the difference is the same, they are on the same diagonal
        if(i > iP){ // front
            if(j > jP){ //front-right
                for(k = iP + 1, p = jP + 1; k < i && p < j && !control ; k++, p++){
                    if(board[k][p].type != CAPABLANK){ //test if all the pieces between the two are blank
                        control = true; //stop the loop
                    }
                }
                if(!control){ //if they are, the piece can be captured
                    changePiece(board, i, j, iP, jP);
                    testCapaCheck.updateAttackBoard(board);
                 //   if(check){
                        if(testCapaCheck.testCheck(board, !board[i][j].color)){
                            changeBack(board, i, j, iP, jP);
                            testCapaCheck.updateAttackBoard(board);
                            cout << "You must not stay in check!" << endl;
                            return false;
                        }
                    //}
                    return true;
                }
            }
            else{ //front-left
                for(k = iP + 1, p = jP - 1; k < i && p > j && !control ; k++, p--){
                    if(board[k][p].type != CAPABLANK){ //test if all the pieces between the two are blank
                        control = true; //stop the loop
                    }
                }
                if(!control){ //if they are, the piece can be captured
                    changePiece(board, i, j, iP, jP);
                    testCapaCheck.updateAttackBoard(board);
                  //  if(check){
                        if(testCapaCheck.testCheck(board, !board[i][j].color)){
                            changeBack(board, i, j, iP, jP);
                            testCapaCheck.updateAttackBoard(board);
                            cout << "You must not stay in check!" << endl;
                            return false;
                        }
                 //   }
                    return true;
                }
            }
        }
        else{ //back
            if(j > jP){ //back-right
                for(k = iP - 1, p = jP + 1; k > i && p < j && !control ; k--, p++){
                    if(board[k][p].type != CAPABLANK){ //test if all the pieces between the two are blank
                        control = true; //stop the loop
                    }
                }
                if(!control){ //if they are, the piece can be captured
                    changePiece(board, i, j, iP, jP);
                    testCapaCheck.updateAttackBoard(board);
                 //   if(check){
                        if(testCapaCheck.testCheck(board, !board[i][j].color)){
                            changeBack(board, i, j, iP, jP);
                            testCapaCheck.updateAttackBoard(board);
                            cout << "You must not stay in check!" << endl;
                            return false;
                        }
                   // }
                    return true;
                }
            }
            else{ //back-left
                for(k = iP - 1, p = jP - 1; k > i && p > j && !control ; k--, p--){
                    if(board[k][p].type != CAPABLANK){ //test if all the pieces between the two are blank
                        control = true; //stop the loop
                    }
                }
                if(!control){ //if they are, the piece can be captured
                    changePiece(board, i, j, iP, jP);
                    testCapaCheck.updateAttackBoard(board);
                //    if(check){
                        if(testCapaCheck.testCheck(board, !board[i][j].color)){
                            changeBack(board, i, j, iP, jP);
                            testCapaCheck.updateAttackBoard(board);
                            cout << "You must not stay in check!" << endl;
                            return false;
                        }
                 //   }
                    return true;
                }
            }
        }
    }
    return false;
}

bool capapiece::knightMovement(capapiece board[8][10], int i, int j, int iP, int jP, bool check){
    if(   (i == iP + 1 && j == jP + 2) || (i == iP + 2 && j == jP + 1)
       || (i == iP + 1 && j == jP - 2) || (i == iP + 2 && j == jP - 1)
       || (i == iP - 1 && j == jP + 2) || (i == iP - 2 && j == jP + 1)
       || (i == iP - 1 && j == jP - 2) || (i == iP - 2 && j == jP - 1)){
        changePiece(board, i, j, iP, jP);
        testCapaCheck.updateAttackBoard(board);
        if(testCapaCheck.testCheck(board, !board[i][j].color)){
            changeBack(board, i, j, iP, jP);
            testCapaCheck.updateAttackBoard(board);
            cout << "You must not stay in check!" << endl;
            return false;
        }
        return true;
    }
    return false;
}

bool capapiece::movement(capapiece board[8][10], int i, int j, int iP, int jP, bool check){ //iP and jP = piece clicked. i and j = current square clicked.
    bool control = false; //control loops
    int k, p;
    switch(board[iP][jP].type){
        case CAPAPAWN:
            return pawnMovement(board, i, j, iP, jP, check);
        break;
        case CAPATOWER:
            return towerMovement(board, i, j, iP, jP, check);
        break;
        case CAPABISHOP:
            return bishopMovement(board, i, j, iP, jP, check);
        break;
        case CAPAKNIGHT:
            return knightMovement(board, i, j, iP, jP, check);
        break;
        case CAPAQUEEN:
            return (towerMovement(board, i, j, iP, jP, check) || bishopMovement(board, i, j, iP, jP, check));
        break;
        case ARCHBISHOP:
            return (bishopMovement(board, i, j, iP, jP, check) || knightMovement(board, i, j, iP, jP, check));
        break;
        case CHANCELER:
            return (towerMovement(board, i, j, iP, jP, check) || knightMovement(board, i, j, iP, jP, check));
        break;
        case CAPAKING:
            if(    ((i == iP + 1) && (j == jP + 1 || j == jP - 1 || j == jP))
                || ((i == iP - 1) && (j == jP + 1 || j == jP - 1 || j == jP))
                || ((i == iP)     && (j == jP + 1 || j == jP - 1)          )){ //right or left
                changePiece(board, i, j, iP, jP);
               // if(check){
                    testCapaCheck.updateAttackBoard(board);
                    if(testCapaCheck.testCheck(board, !board[i][j].color)){
                        changeBack(board, i, j, iP, jP);
                        testCapaCheck.updateAttackBoard(board);
                        cout << "You must not get or stay in check!" << endl;
                        return false;
                    }
              //  }
                return true;
            }
            else if(i == iP && j == jP + 3){
                if(check){
                    cout << "You must not stay in check!" << endl;
                }
                else if(testSmallCastling(board, i, j, iP, jP)){
                    changePiece(board, i, j, iP, jP);
                    changePiece(board, i, jP+2, iP, j+1);
                    testCapaCheck.updateAttackBoard(board);
                    return true;
                }
            }
            else if(i == iP && j == jP - 3){
                if(check){
                    cout << "You must not stay in check!" << endl;
                }
                else if(testBigCastling(board, i, j, iP, jP)){
                    changePiece(board, i, j, iP, jP);
                    changePiece(board, i, jP-2, iP, j-2);
                    testCapaCheck.updateAttackBoard(board);
                    return true;
                }
            }
            return false;
        break;
        default:
            cout << "Not a valid square!" << endl;
            return false;
        break;
    }
}

bool capapiece::testSmallCastling(capapiece board[8][10], int i, int j, int iP, int jP){
    int k, p, color = board[iP][jP].color;
    if(board[iP][jP].hasMoved || board[iP][jP+4].hasMoved || board[iP][jP+4].type != CAPATOWER){ //Neither of the pieces must have been moved
        return false;
    }
    if(board[iP][jP+1].type != CAPABLANK || board[iP][jP+2].type != CAPABLANK || board[iP][jP+3].type != CAPABLANK){ //the middle pieces must be blanks
        return false;
    }
    for(k = 0; k < 8; k++){
        for(p = 0; p < 10; p++){
            if(board[k][p].color != board[iP][jP].color){
                if(board[k][p].attackBoard[iP][jP+1] == 1 || board[k][p].attackBoard[iP][jP+2] == 1 || board[k][p].attackBoard[iP][jP+3] == 1){ //No piece that the king will pass must be attacked
                    return false;
                }
            }
        }
    }
    return true;

}

bool capapiece::testBigCastling(capapiece board[8][10], int i, int j, int iP, int jP){
    int k, p, color = board[iP][jP].color;
    if(board[iP][jP].hasMoved || board[iP][jP-5].hasMoved || board[iP][jP-5].type != CAPATOWER){ //Neither of the pieces must have been moved
        return false;
    }
    if(board[iP][jP-1].type != CAPABLANK || board[iP][jP-2].type != CAPABLANK || board[iP][jP-3].type != CAPABLANK || board[iP][jP-4].type != CAPABLANK){ //the middle pieces must be blanks
        return false;
    }
    for(k = 0; k < 8; k++){
        for(p = 0; p < 10; p++){
            if(board[k][p].color == !color && board[k][p].type == CAPABISHOP){
                if(board[k][p].attackBoard[iP][jP-1] == 1 || board[k][p].attackBoard[iP][jP-2] == 1 || board[k][p].attackBoard[iP][jP-3] == 1){ //No piece that the king will pass must be attacked
                    return false;
                }
            }
        }
    }
    return true;

}

//actually, this function was created so I does not have to test the pawn capture condition in the movement function.
bool capapiece::capture(capapiece board[8][10], int i, int j, int iP, int jP, bool check){ //iP and jP = piece clicked. i and j = current square clicked.
    switch(board[iP][jP].type){
        case CAPAPAWN:
            if(board[iP][jP].color == 1){
               if( ( (i == iP+1 && j == jP+1) || (i == iP+1 && j == jP-1) )){ //The piece clicked is in red mens you can capture it
                    changePiece(board, i, j, iP, jP);
                    if(check){
                        testCapaCheck.updateAttackBoard(board);
                        if(testCapaCheck.testCheck(board, !board[i][j].color)){
                            changeBack(board, i, j, iP, jP);
                            testCapaCheck.updateAttackBoard(board);
                            cout << "You must not stay in check!" << endl;
                            return false;
                        }
                    }
                    return true;
                }
            return false;
            }
            else{
                if( ( (i == iP-1 && j == jP+1) || (i == iP-1 && j == jP-1) )){ //The piece clicked is in red mens you can capture it
                    changePiece(board, i, j, iP, jP);
                    if(check){
                        testCapaCheck.updateAttackBoard(board);
                        if(testCapaCheck.testCheck(board, !board[i][j].color)){
                            changeBack(board, i, j, iP, jP);
                            testCapaCheck.updateAttackBoard(board);
                            cout << "You must not stay in check!" << endl;
                            return false;
                        }
                    }
                    return true;
                }
            return false;
            }
        break;
        default:
            return board[iP][jP].movement(board, i, j, iP, jP, check); //the conditions of movement are the same of capture
        break;
    }
}



capapiece::capapiece(){
    sf::RectangleShape shape(sf::Vector2f(PIECE_SIZE, PIECE_SIZE));
    this->square = shape;
    sf::FloatRect squareRect(this->square.getPosition().x, this->square.getPosition().y, this->square.getSize().x, this->square.getSize().y);
    this->rectSquare = squareRect;
    clicked = false;
    highlighted = false;
}

capapiece::capapiece(CAPATYPE tipo){
    int i, j;
    sf::RectangleShape shape(sf::Vector2f(PIECE_SIZE, PIECE_SIZE)); //Create the shape of a square of size 60x60 pixels
    this->square = shape;
    sf::FloatRect squareRect(this->square.getPosition().x, this->square.getPosition().y, this->square.getSize().x, this->square.getSize().y);
    this->rectSquare = squareRect; //The FloatRect is made in the same position and of the same size of the square
    clicked = false;
    highlighted = false;
    sf::Texture* border = new sf::Texture();
    border->loadFromFile("media/images/border55.png");
    this->border.setTexture(*border);
    this->type = tipo;
    this->moves = 0;
    hasMoved = false;
    switch(tipo){
        case CAPAPAWN:
            this->code = "";
        break;
        case CAPATOWER:
            this->code = 'R';
        break;
        case CAPAKNIGHT:
            this->code = 'N';
        break;
        case CAPABISHOP:
            this->code = 'B';
        break;
        case CAPAQUEEN:
            this->code = 'Q';
        break;
        case ARCHBISHOP:
            this->code = 'A';
        break;
        case CHANCELER:
            this->code = 'C';
        break;
        case CAPAKING:
            this->code = 'K';
        break;
    }


    for(i = 0; i < 8; i++){
        for(j = 0; j < 10; j++){
            this->attackBoard[i][j] = 0;
        }
    }
}


