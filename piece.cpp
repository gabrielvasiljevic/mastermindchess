#include <SFML/Graphics.hpp>
#include "Pieces.h"
#include <iostream>
#include <math.h>
using namespace std;

#define PIECE_SIZE 60

void Piece::movement(Piece board[8][8], int i, int j, int iP, int jP){ //iP and jP = piece clicked. i and j = current square clicked.
    bool control = false; //control loops
    int k, p;
    switch(board[iP][jP].type){
        case PAWN:
            if(i == iP+1 && j == jP){
                board[iP][jP].type = BLANK;
                board[i][j].color = board[iP][jP].color;
                board[i][j].type = PAWN;
                board[iP][jP].color = -1;
            }
            else if(iP == 1 && i == iP + 2 && j == jP){
                board[iP][jP].type = BLANK;
                board[i][j].color = board[iP][jP].color;
                board[i][j].type = PAWN;
                board[iP][jP].color = -1;
            }
        break;
        case TOWER:
            if(i == iP){ //same row
                if(j > jP){ //to the right
                    for(k = jP + 1; k < j && !control; k++){ //loop until reach the piece clicked
                        if(board[i][k].type != BLANK){ //test if all the pieces between the two are blank
                            control = true; //stop the loop
                        }
                    }
                    if(!control){ //if they are, the piece can be captured
                        board[iP][jP].type = BLANK;
                        board[i][j].color = board[iP][jP].color;
                        board[i][j].type = TOWER;
                        board[iP][jP].color = -1;
                    }
                }
                else{ //to the left
                    for(k = jP - 1; k > j && !control; k--){ //loop until reach the piece clicked
                        if(board[i][k].type != BLANK){ //test if all the pieces between the two are blank
                            control = true; //stop the loop
                        }
                    }
                    if(!control){ //if they are, the piece can be captured
                        board[iP][jP].type = BLANK;
                        board[i][j].color = board[iP][jP].color;
                        board[i][j].type = TOWER;
                        board[iP][jP].color = -1;
                    }
                }
            }
            else if(j == jP){ //same column
                if(i > iP){ //to the front
                    for(k = iP + 1; k < i && !control; k++){ //loop until reach the piece clicked
                        if(board[k][j].type != BLANK){ //test if all the pieces between the two are blank
                            control = true; //stop the loop
                        }
                    }
                    if(!control){ //if they are, the piece can be captured
                        board[iP][jP].type = BLANK;
                        board[i][j].color = board[iP][jP].color;
                        board[i][j].type = TOWER;
                        board[iP][jP].color = -1;
                    }
                }
                else{ //to the left
                    for(k = iP - 1; k > i && !control; k--){ //loop until reach the piece clicked
                        if(board[k][j].type != BLANK){ //test if all the pieces between the two are blank
                            control = true; //stop the loop
                        }
                    }
                    if(!control){ //if they are, the piece can be captured
                        board[iP][jP].type = BLANK;
                        board[i][j].color = board[iP][jP].color;
                        board[i][j].type = TOWER;
                        board[iP][jP].color = -1;
                    }
                }

            }
        break;
        case BISHOP:
            control = false;
            if(abs(i - iP) == abs(j - jP)){ //if the difference is the same, they are on the same diagonal
                if(i > iP){ // front
                    if(j > jP){ //front-right
                        for(k = iP + 1, p = jP + 1; k < i && p < j && !control ; k++, p++){
                            if(board[k][p].type != BLANK){ //test if all the pieces between the two are blank
                                control = true; //stop the loop
                            }
                        }
                        if(!control){ //if they are, the piece can be captured
                            board[iP][jP].type = BLANK;
                            board[i][j].color = board[iP][jP].color;
                            board[i][j].type = BISHOP;
                            board[iP][jP].color = -1;
                        }
                    }
                    else{ //front-left
                        for(k = iP + 1, p = jP - 1; k < i && p > j && !control ; k++, p--){
                            if(board[k][p].type != BLANK){ //test if all the pieces between the two are blank
                                control = true; //stop the loop
                            }
                        }
                        if(!control){ //if they are, the piece can be captured
                            board[iP][jP].type = BLANK;
                            board[i][j].color = board[iP][jP].color;
                            board[i][j].type = BISHOP;
                            board[iP][jP].color = -1;
                        }
                    }
                }
                else{ //back
                    if(j > jP){ //back-right
                        for(k = iP - 1, p = jP + 1; k > i && p < j && !control ; k--, p++){
                            if(board[k][p].type != BLANK){ //test if all the pieces between the two are blank
                                control = true; //stop the loop
                            }
                        }
                        if(!control){ //if they are, the piece can be captured
                            board[iP][jP].type = BLANK;
                            board[i][j].color = board[iP][jP].color;
                            board[i][j].type = BISHOP;
                            board[iP][jP].color = -1;
                        }
                    }
                    else{ //back-left
                        for(k = iP - 1, p = jP - 1; k > i && p > j && !control ; k--, p--){
                            if(board[k][p].type != BLANK){ //test if all the pieces between the two are blank
                                control = true; //stop the loop
                            }
                        }
                        if(!control){ //if they are, the piece can be captured
                            board[iP][jP].type = BLANK;
                            board[i][j].color = board[iP][jP].color;
                            board[i][j].type = BISHOP;
                            board[iP][jP].color = -1;
                        }
                    }
                }
            }
        break;
        case QUEEN:
            if(i == iP){ //same row
                if(j > jP){ //to the right
                    for(k = jP + 1; k < j && !control; k++){ //loop until reach the piece clicked
                        if(board[i][k].type != BLANK){ //test if all the pieces between the two are blank
                            control = true; //stop the loop
                        }
                    }
                    if(!control){ //if they are, the piece can be captured
                        board[iP][jP].type = BLANK;
                        board[i][j].color = board[iP][jP].color;
                        board[i][j].type = QUEEN;
                        board[iP][jP].color = -1;
                    }
                }
                else{ //to the left
                    for(k = jP - 1; k > j && !control; k--){ //loop until reach the piece clicked
                        if(board[i][k].type != BLANK){ //test if all the pieces between the two are blank
                            control = true; //stop the loop
                        }
                    }
                    if(!control){ //if they are, the piece can be captured
                        board[iP][jP].type = BLANK;
                        board[i][j].color = board[iP][jP].color;
                        board[i][j].type = QUEEN;
                        board[iP][jP].color = -1;
                    }
                }
            }
            else if(j == jP){ //same column
                if(i > iP){ //to the front
                    for(k = iP + 1; k < i && !control; k++){ //loop until reach the piece clicked
                        if(board[k][j].type != BLANK){ //test if all the pieces between the two are blank
                            control = true; //stop the loop
                        }
                    }
                    if(!control){ //if they are, the piece can be captured
                        board[iP][jP].type = BLANK;
                        board[i][j].color = board[iP][jP].color;
                        board[i][j].type = QUEEN;
                        board[iP][jP].color = -1;
                    }
                }
                else{ //to the left
                    for(k = iP - 1; k > i && !control; k--){ //loop until reach the piece clicked
                        if(board[k][j].type != BLANK){ //test if all the pieces between the two are blank
                            control = true; //stop the loop
                        }
                    }
                    if(!control){ //if they are, the piece can be captured
                        board[iP][jP].type = BLANK;
                        board[i][j].color = board[iP][jP].color;
                        board[i][j].type = QUEEN;
                        board[iP][jP].color = -1;
                    }
                }

            }
            control = false;
            if(abs(i - iP) == abs(j - jP)){ //if the difference is the same, they are on the same diagonal
                if(i > iP){ // front
                    if(j > jP){ //front-right
                        for(k = iP + 1, p = jP + 1; k < i && p < j && !control ; k++, p++){
                            if(board[k][p].type != BLANK){ //test if all the pieces between the two are blank
                                control = true; //stop the loop
                            }
                        }
                        if(!control){ //if they are, the piece can be captured
                            board[iP][jP].type = BLANK;
                            board[i][j].color = board[iP][jP].color;
                            board[i][j].type = QUEEN;
                            board[iP][jP].color = -1;
                        }
                    }
                    else{ //front-left
                        for(k = iP + 1, p = jP - 1; k < i && p > j && !control ; k++, p--){
                            if(board[k][p].type != BLANK){ //test if all the pieces between the two are blank
                                control = true; //stop the loop
                            }
                        }
                        if(!control){ //if they are, the piece can be captured
                            board[iP][jP].type = BLANK;
                            board[i][j].color = board[iP][jP].color;
                            board[i][j].type = QUEEN;
                            board[iP][jP].color = -1;
                        }
                    }
                }
                else{ //back
                    if(j > jP){ //back-right
                        for(k = iP - 1, p = jP + 1; k > i && p < j && !control ; k--, p++){
                            if(board[k][p].type != BLANK){ //test if all the pieces between the two are blank
                                control = true; //stop the loop
                            }
                        }
                        if(!control){ //if they are, the piece can be captured
                            board[iP][jP].type = BLANK;
                            board[i][j].color = board[iP][jP].color;
                            board[i][j].type = QUEEN;
                            board[iP][jP].color = -1;
                        }
                    }
                    else{ //back-left
                        for(k = iP - 1, p = jP - 1; k > i && p > j && !control ; k--, p--){
                            if(board[k][p].type != BLANK){ //test if all the pieces between the two are blank
                                control = true; //stop the loop
                            }
                        }
                        if(!control){ //if they are, the piece can be captured
                            board[iP][jP].type = BLANK;
                            board[i][j].color = board[iP][jP].color;
                            board[i][j].type = QUEEN;
                            board[iP][jP].color = -1;
                        }
                    }
                }
            }
        break;
        case KING:
            if(i == iP + 1 && (j == jP + 1 || j == jP - 1 || j == jP)){ //front
                board[iP][jP].type = BLANK;
                board[i][j].color = board[iP][jP].color;
                board[i][j].type = KING;
                board[iP][jP].color = -1;
            }
            else if(i == iP - 1 && (j == jP + 1 || j == jP - 1 || j == jP)){ //back
                board[iP][jP].type = BLANK;
                board[i][j].color = board[iP][jP].color;
                board[i][j].type = KING;
                board[iP][jP].color = -1;
            }
            else if(i == iP && (j == jP + 1 || j == jP - 1)){ //right or left
                board[iP][jP].type = BLANK;
                board[i][j].color = board[iP][jP].color;
                board[i][j].type = KING;
                board[iP][jP].color = -1;
            }
        break;
        case KNIGHT:
            if(   (i == iP + 1 && j == jP + 2) || (i == iP + 2 && j == jP + 1)
               || (i == iP + 1 && j == jP - 2) || (i == iP + 2 && j == jP - 1)
               || (i == iP - 1 && j == jP + 2) || (i == iP - 2 && j == jP + 1)
               || (i == iP - 1 && j == jP - 2) || (i == iP - 2 && j == jP - 1)){
                board[iP][jP].type = BLANK;
                board[i][j].color = board[iP][jP].color;
                board[i][j].type = KNIGHT;
                board[iP][jP].color = -1;
            }
        break;

        default:
            cout << "Not a valid square!" << endl;
        break;
    }
}

void Piece::capture(Piece board[8][8], int i, int j, int iP, int jP){ //iP and jP = piece clicked. i and j = current square clicked.
    switch(board[iP][jP].type){
        case PAWN:
            if( ( (i == iP+1 && j == jP+1) || (i == iP+1 && j == jP-1) )){ //The piece clicked is in red mens you can capture it
                board[iP][jP].type = BLANK;
                board[i][j].color = board[iP][jP].color;
                board[i][j].type = PAWN;
                board[iP][jP].color = -1;
            }
        break;
        default:
            board[iP][jP].movement(board, i, j, iP, jP); //the conditions of movement are the same of capture
        break;
    }
}
Piece::Piece(){
    sf::RectangleShape shape(sf::Vector2f(PIECE_SIZE, PIECE_SIZE));
    this->square = shape;
    sf::FloatRect squareRect(this->square.getPosition().x, this->square.getPosition().y, this->square.getSize().x, this->square.getSize().y);
    this->rectSquare = squareRect;
    clicked = false;
    highlighted = false;
}

Piece::Piece(TYPE tipo){
    sf::RectangleShape shape(sf::Vector2f(PIECE_SIZE, PIECE_SIZE)); //Create the shape of a square of size 60x60 pixels
    this->square = shape;
    sf::FloatRect squareRect(this->square.getPosition().x, this->square.getPosition().y, this->square.getSize().x, this->square.getSize().y);
    this->rectSquare = squareRect; //The FloatRect is made in the same position and of the same size of the square
    clicked = false;
    highlighted = false;
    sf::Texture* border = new sf::Texture();
    border->loadFromFile("images/border.png");
    this->border.setTexture(*border);

    this->type = tipo;
    switch(tipo){
        case PAWN:
            this->code = 'P';
        break;
        case TOWER:
            this->code = 'T';
        break;
        case KNIGHT:
            this->code = 'K';
        break;
        case BISHOP:
            this->code = 'B';
        break;
        case QUEEN:
            this->code = 'Q';
        break;
        case KING:
            this->code = 'K';
        break;
    }
}

