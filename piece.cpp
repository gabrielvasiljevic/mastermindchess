#include <SFML/Graphics.hpp>
#include "Pieces.h"
#include <iostream>

using namespace std;


void Piece::movement(Piece board[8][8], int i, int j, int iP, int jP){ //iP and jP = piece clicked. i and j = current square clicked.
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
    }
}
Piece::Piece(){
    sf::RectangleShape shape(sf::Vector2f(60, 60));
    this->square = shape;
    sf::FloatRect squareRect(this->square.getPosition().x, this->square.getPosition().y, this->square.getSize().x, this->square.getSize().y);
    this->rectSquare = squareRect;
    clicked = false;
}

Piece::Piece(TYPE tipo){
    sf::RectangleShape shape(sf::Vector2f(60, 60)); //Create the shape of a square of size 60x60 pixels
    this->square = shape;
    sf::FloatRect squareRect(this->square.getPosition().x, this->square.getPosition().y, this->square.getSize().x, this->square.getSize().y);
    this->rectSquare = squareRect; //The FloatRect is made in the same position and of the same size of the square
    clicked = false;
    this->type = tipo;
}

