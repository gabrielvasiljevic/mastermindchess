#include <SFML/Graphics.hpp>
#include "pieces.h"
#include "board.h"


using namespace std;

Board::Board(){
    Piece pawns(PAWN);
    Piece towers(TOWER);
    Piece bishops(BISHOP);
    Piece knights(KNIGHT);
    Piece queens(QUEEN);
    Piece kings(KING);
    Piece blanks(BLANK);
    for(int i = 2; i < 6; i++){ //The middle pieces are all blanks in the beginning
        for(int j = 0; j < 8; j++){
            pieces[i][j] = blanks;
            pieces[i][j].color = -1;
            pieces[i][j].image.setPosition(220+60*(j), 400 - 60*(i-2)); //The board stars at (220, 100), and each piece is a 60x60 square
            pieces[i][j].square.setPosition(220+60*(j), 400 - 60*(i-2));
            sf::FloatRect squareRect(pieces[i][j].square.getPosition().x, pieces[i][j].square.getPosition().y,
                                 pieces[i][j].square.getSize().x, pieces[i][j].square.getSize().y);
            pieces[i][j].rectSquare = squareRect; //Creates the FloatRect in the same position
        }
    }
        //Towers
        pieces[0][0] = towers;
        pieces[0][0].color = 1;
        pieces[0][7] = towers;
        pieces[0][7].color = 1;

        pieces[7][0] = towers;
        pieces[7][0].color = 0;
        pieces[7][7] = towers;
        pieces[7][7].color = 0;

        //Knights
        pieces[0][1] = knights;
        pieces[0][1].color = 1;
        pieces[0][6] = knights;
        pieces[0][6].color = 1;

        pieces[7][1] = knights;
        pieces[7][1].color = 0;
        pieces[7][6] = knights;
        pieces[7][6].color = 0;

        //Bishops
        pieces[0][2] = bishops;
        pieces[0][2].color = 1;
        pieces[0][5] = bishops;
        pieces[0][5].color = 1;

        pieces[7][2] = bishops;
        pieces[7][2].color = 0;
        pieces[7][5] = bishops;
        pieces[7][5].color = 0;

        //Queens
        pieces[0][3] = queens;
        pieces[0][3].color = 1;

        pieces[7][3] = queens;
        pieces[7][3].color = 0;


        //Kings

        pieces[0][4] = kings;
        pieces[0][4].color = 1;

        pieces[7][4] = kings;
        pieces[7][4].color = 0;

    for(int i = 0; i < 8; i++){

        pieces[1][i] = pawns;
        pieces[1][i].color = 1;

        pieces[6][i] = pawns;
        pieces[6][i].color = 0;
    }
    for(int x = 0; x < 8; x++){ //Set the position of the pawns

        pieces[1][x].image.setPosition(220+60*(x), 460);
        pieces[1][x].square.setPosition(220+60*(x), 460);
        sf::FloatRect squareRect(pieces[1][x].square.getPosition().x, pieces[1][x].square.getPosition().y,
                                 pieces[1][x].square.getSize().x, pieces[1][x].square.getSize().y);
        pieces[1][x].rectSquare = squareRect;

        pieces[6][x].image.setPosition(220+60*(x), 160);
        pieces[6][x].square.setPosition(220+60*(x), 160);
        sf::FloatRect squareRect2(pieces[6][x].square.getPosition().x, pieces[6][x].square.getPosition().y,
                                  pieces[6][x].square.getSize().x, pieces[6][x].square.getSize().y);
        pieces[6][x].rectSquare = squareRect2;
    }
    for(int i = 0; i < 8; i++){ //Set the position of the other pieces
        pieces[0][i].image.setPosition(220+60*(i), 520);
        pieces[0][i].square.setPosition(220+60*(i), 520);
        sf::FloatRect squareRect0(pieces[0][i].square.getPosition().x, pieces[0][i].square.getPosition().y,
                                 pieces[0][i].square.getSize().x, pieces[0][i].square.getSize().y);
        pieces[0][i].rectSquare = squareRect0;

        pieces[7][i].image.setPosition(220+60*(i), 100);
        pieces[7][i].square.setPosition(220+60*(i), 100);
        sf::FloatRect squareRect1(pieces[7][i].square.getPosition().x, pieces[7][i].square.getPosition().y,
                                 pieces[7][i].square.getSize().x, pieces[7][i].square.getSize().y);
        pieces[7][i].rectSquare = squareRect1;

    }
}
