#include <SFML/Graphics.hpp>
#include "headers/capapiece.h"
#include "headers/capaboard.h"

#define SIZE_PIECE 55
using namespace std;

Capaboard::Capaboard(int board_x, int board_y, int color){
    if(color == 1)
        Initialize(board_x, board_y);
    else
        InitializeBlack(board_x, board_y);
}

//Changing a single number in this code will destroy the entire game. Be careful!


void Capaboard::Initialize(int board_x, int board_y){
    capapiece pawns(CAPAPAWN);
    capapiece towers(CAPATOWER);
    capapiece bishops(CAPABISHOP);
    capapiece knights(CAPAKNIGHT);
    capapiece queens(CAPAQUEEN);
    capapiece archbishops(ARCHBISHOP);
    capapiece chancelers(CHANCELER);
    capapiece kings(CAPAKING);
    capapiece blanks(CAPABLANK);
    for(int i = 2; i < 6; i++){ //The middle pieces are all blanks in the beginning
        for(int j = 0; j < 10; j++){
            pieces[i][j] = blanks;
            pieces[i][j].color = -1;
            pieces[i][j].image.setPosition(board_x + SIZE_PIECE*(j), (board_y + SIZE_PIECE*5) - SIZE_PIECE*(i-2));
            pieces[i][j].square.setPosition(board_x + SIZE_PIECE*(j), (board_y + SIZE_PIECE*5) - SIZE_PIECE*(i-2)); //initial point + (wanted square)*(size of square)
            sf::FloatRect squareRect(pieces[i][j].square.getPosition().x, pieces[i][j].square.getPosition().y,
                         pieces[i][j].square.getSize().x, pieces[i][j].square.getSize().y);
            pieces[i][j].rectSquare = squareRect; //Creates the FloatRect in the same position
            pieces[i][j].border.setPosition(board_x + SIZE_PIECE*(j), (board_y + SIZE_PIECE*5) - SIZE_PIECE*(i-2));
        }
    }
        //Towers
        pieces[0][0] = towers;
        pieces[0][0].color = 1;
        pieces[0][9] = towers;
        pieces[0][9].color = 1;

        pieces[7][0] = towers;
        pieces[7][0].color = 0;
        pieces[7][9] = towers;
        pieces[7][9].color = 0;

        //Knights
        pieces[0][1] = knights;
        pieces[0][1].color = 1;
        pieces[0][8] = knights;
        pieces[0][8].color = 1;

        pieces[7][1] = knights;
        pieces[7][1].color = 0;
        pieces[7][8] = knights;
        pieces[7][8].color = 0;

        //Bishops
        pieces[0][3] = bishops;
        pieces[0][3].color = 1;
        pieces[0][6] = bishops;
        pieces[0][6].color = 1;

        pieces[7][3] = bishops;
        pieces[7][3].color = 0;
        pieces[7][6] = bishops;
        pieces[7][6].color = 0;

        //Queens
        pieces[0][4] = queens;
        pieces[0][4].color = 1;

        pieces[7][4] = queens;
        pieces[7][4].color = 0;

        //Archbishops
        pieces[0][2] = archbishops;
        pieces[0][2].color = 1;

        pieces[7][2] = archbishops;
        pieces[7][2].color = 0;

        //Chancelers
        pieces[0][7] = chancelers;
        pieces[0][7].color = 1;

        pieces[7][7] = chancelers;
        pieces[7][7].color = 0;

        //Kings

        pieces[0][5] = kings;
        pieces[0][5].color = 1;

        pieces[7][5] = kings;
        pieces[7][5].color = 0;

    for(int i = 0; i < 10; i++){

        pieces[1][i] = pawns;
        pieces[1][i].color = 1;

        pieces[6][i] = pawns;
        pieces[6][i].color = 0;
    }
    for(int x = 0; x < 10; x++){ //Set the position of the pawns

        pieces[1][x].image.setPosition(board_x + SIZE_PIECE*(x), board_y + 6*SIZE_PIECE); //460
        pieces[1][x].square.setPosition(board_x + SIZE_PIECE*(x), board_y + 6*SIZE_PIECE);
        pieces[1][x].border.setPosition(board_x + SIZE_PIECE*(x), board_y + 6*SIZE_PIECE);
        sf::FloatRect squareRect(pieces[1][x].square.getPosition().x, pieces[1][x].square.getPosition().y,
                                 pieces[1][x].square.getSize().x, pieces[1][x].square.getSize().y);
        pieces[1][x].rectSquare = squareRect;


        pieces[6][x].image.setPosition(board_x + SIZE_PIECE*(x), board_y + SIZE_PIECE);
        pieces[6][x].square.setPosition(board_x + SIZE_PIECE*(x), board_y + SIZE_PIECE);
        pieces[6][x].border.setPosition(board_x + SIZE_PIECE*(x), board_y + SIZE_PIECE);
        sf::FloatRect squareRect2(pieces[6][x].square.getPosition().x, pieces[6][x].square.getPosition().y,
                                  pieces[6][x].square.getSize().x, pieces[6][x].square.getSize().y);
        pieces[6][x].rectSquare = squareRect2;
    }
    for(int i = 0; i < 10; i++){ //Set the position of the other pieces
        pieces[0][i].image.setPosition(board_x + SIZE_PIECE*(i), board_y + 7*SIZE_PIECE); //520
        pieces[0][i].square.setPosition(board_x + SIZE_PIECE*(i), board_y + 7*SIZE_PIECE);
        pieces[0][i].border.setPosition(board_x + SIZE_PIECE*(i), board_y + 7*SIZE_PIECE);
        sf::FloatRect squareRect0(pieces[0][i].square.getPosition().x, pieces[0][i].square.getPosition().y,
                                 pieces[0][i].square.getSize().x, pieces[0][i].square.getSize().y);
        pieces[0][i].rectSquare = squareRect0;

        pieces[7][i].image.setPosition(board_x + SIZE_PIECE*(i), board_y);
        pieces[7][i].square.setPosition(board_x + SIZE_PIECE*(i), board_y);
        pieces[7][i].border.setPosition(board_x + SIZE_PIECE*(i), board_y);
        sf::FloatRect squareRect1(pieces[7][i].square.getPosition().x, pieces[7][i].square.getPosition().y,
                                 pieces[7][i].square.getSize().x, pieces[7][i].square.getSize().y);
        pieces[7][i].rectSquare = squareRect1;

    }
}

//For the black pieces, do the same as the white, but setting the position in an inverse way, starting from the end
void Capaboard::InitializeBlack(int board_x, int board_y){
    capapiece pawns(CAPAPAWN);
    capapiece towers(CAPATOWER);
    capapiece bishops(CAPABISHOP);
    capapiece knights(CAPAKNIGHT);
    capapiece queens(CAPAQUEEN);
    capapiece archbishops(ARCHBISHOP);
    capapiece chancelers(CHANCELER);
    capapiece kings(CAPAKING);
    capapiece blanks(CAPABLANK);
    for(int i = 2; i < 6; i++){ //The middle pieces are all blanks in the beginning
        for(int j = 0; j < 10; j++){
            pieces[i][j] = blanks;
            pieces[i][j].color = -1;
            pieces[i][j].image.setPosition(board_x + SIZE_PIECE*(9 - j), (board_y + SIZE_PIECE*5) - SIZE_PIECE*(5-i));
            pieces[i][j].square.setPosition(board_x + SIZE_PIECE*(9 - j), (board_y + SIZE_PIECE*5) - SIZE_PIECE*(5-i)); //initial point + (wanted square)*(size of square)
            sf::FloatRect squareRect(pieces[i][j].square.getPosition().x, pieces[i][j].square.getPosition().y,
                         pieces[i][j].square.getSize().x, pieces[i][j].square.getSize().y);
            pieces[i][j].rectSquare = squareRect; //Creates the FloatRect in the same position
            pieces[i][j].border.setPosition(board_x + SIZE_PIECE*(9 - j), (board_y + SIZE_PIECE*5) - SIZE_PIECE*(5-i));
        }
    }
        //Towers
        pieces[0][0] = towers;
        pieces[0][0].color = 1;
        pieces[0][9] = towers;
        pieces[0][9].color = 1;

        pieces[7][0] = towers;
        pieces[7][0].color = 0;
        pieces[7][9] = towers;
        pieces[7][9].color = 0;

        //Knights
        pieces[0][1] = knights;
        pieces[0][1].color = 1;
        pieces[0][8] = knights;
        pieces[0][8].color = 1;

        pieces[7][1] = knights;
        pieces[7][1].color = 0;
        pieces[7][8] = knights;
        pieces[7][8].color = 0;

        //Bishops
        pieces[0][3] = bishops;
        pieces[0][3].color = 1;
        pieces[0][6] = bishops;
        pieces[0][6].color = 1;

        pieces[7][3] = bishops;
        pieces[7][3].color = 0;
        pieces[7][6] = bishops;
        pieces[7][6].color = 0;

        //Queens
        pieces[0][4] = queens;
        pieces[0][4].color = 1;

        pieces[7][4] = queens;
        pieces[7][4].color = 0;

        //Archbishops
        pieces[0][2] = archbishops;
        pieces[0][2].color = 1;

        pieces[7][2] = archbishops;
        pieces[7][2].color = 0;

        //Chancelers
        pieces[0][7] = chancelers;
        pieces[0][7].color = 1;

        pieces[7][7] = chancelers;
        pieces[7][7].color = 0;

        //Kings

        pieces[0][5] = kings;
        pieces[0][5].color = 1;

        pieces[7][5] = kings;
        pieces[7][5].color = 0;

    for(int i = 0; i < 10; i++){

        pieces[1][i] = pawns;
        pieces[1][i].color = 1;

        pieces[6][i] = pawns;
        pieces[6][i].color = 0;
    }
    for(int x = 0; x < 10; x++){ //Set the position of the pawns

        pieces[1][x].image.setPosition(board_x + SIZE_PIECE*(9 - x), board_y + SIZE_PIECE);
        pieces[1][x].square.setPosition(board_x + SIZE_PIECE*(9 - x), board_y + SIZE_PIECE);
        pieces[1][x].border.setPosition(board_x + SIZE_PIECE*(9 - x), board_y + SIZE_PIECE);
        sf::FloatRect squareRect(pieces[1][x].square.getPosition().x, pieces[1][x].square.getPosition().y,
                                 pieces[1][x].square.getSize().x, pieces[1][x].square.getSize().y);
        pieces[1][x].rectSquare = squareRect;


        pieces[6][x].image.setPosition(board_x + SIZE_PIECE*(9 - x), board_y + 6*SIZE_PIECE);
        pieces[6][x].square.setPosition(board_x + SIZE_PIECE*(9 - x), board_y + 6*SIZE_PIECE);
        pieces[6][x].border.setPosition(board_x + SIZE_PIECE*(9 - x), board_y + 6*SIZE_PIECE);
        sf::FloatRect squareRect2(pieces[6][x].square.getPosition().x, pieces[6][x].square.getPosition().y,
                                  pieces[6][x].square.getSize().x, pieces[6][x].square.getSize().y);
        pieces[6][x].rectSquare = squareRect2;
    }
    for(int i = 0; i < 10; i++){ //Set the position of the other pieces
        pieces[0][i].image.setPosition(board_x + SIZE_PIECE*(9 - i), board_y);
        pieces[0][i].square.setPosition(board_x + SIZE_PIECE*(9 - i), board_y);
        pieces[0][i].border.setPosition(board_x + SIZE_PIECE*(9 - i), board_y);
        sf::FloatRect squareRect0(pieces[0][i].square.getPosition().x, pieces[0][i].square.getPosition().y,
                                 pieces[0][i].square.getSize().x, pieces[0][i].square.getSize().y);
        pieces[0][i].rectSquare = squareRect0;

        pieces[7][i].image.setPosition(board_x + SIZE_PIECE*(9 - i), board_y + 7*SIZE_PIECE);
        pieces[7][i].square.setPosition(board_x + SIZE_PIECE*(9 - i), board_y + 7*SIZE_PIECE);
        pieces[7][i].border.setPosition(board_x + SIZE_PIECE*(9 - i), board_y + 7*SIZE_PIECE);
        sf::FloatRect squareRect1(pieces[7][i].square.getPosition().x, pieces[7][i].square.getPosition().y,
                                 pieces[7][i].square.getSize().x, pieces[7][i].square.getSize().y);
        pieces[7][i].rectSquare = squareRect1;

    }

}


void Capaboard::Highlight(CAPATYPE t, int i, int j){
    bool stop = false;
    switch(t){
        case CAPAPAWN:
            if(this->pieces[i][j].color == 1){
               if(i < 7){ //Do not pass the board!
                    if(this->pieces[i + 1][j].type == CAPABLANK){ //if the square in front of the pawn is blank
                        //this->pieces[i + 1][j].square.setFillColor(sf::Color::Green); //highlight it in green
                        this->pieces[i + 1][j].highlighted = true;
                        if(i == 1){ //if is the first move of the paw
                            if(this->pieces[i + 2][j].type == CAPABLANK){
                                //this->pieces[i + 2][j].square.setFillColor(sf::Color::Green); //highlight the second one too!
                                this->pieces[i + 2][j].highlighted = true;
                            }
                        }
                    }
                    if(i + 1 < 8 && j + 1 < 8){ //test if the sides are inside the board
                        if(this->pieces[i+1][j+1].type != CAPABLANK && this->pieces[i+1][j+1].color != this->pieces[i][j].color){ //if the diagonal squares are from a different color
                            this->pieces[i+1][j+1].square.setFillColor(sf::Color::Red); //its a enemy piece! highlight it in red
                        }
                        if(j - 1 >= 0){ //same here
                            if(this->pieces[i+1][j-1].type != CAPABLANK && this->pieces[i+1][j-1].color != this->pieces[i][j].color){
                                this->pieces[i+1][j-1].square.setFillColor(sf::Color::Red);
                            }
                        }
                    }
                    if(j == 9){
                        if(this->pieces[i+1][j-1].type != CAPABLANK && this->pieces[i+1][j-1].color != this->pieces[i][j].color){
                            this->pieces[i+1][j-1].square.setFillColor(sf::Color::Red);
                        }
                    }
                    if(i == 4){ //en passant
                        if(j > 0){
                            if(this->pieces[i+1][j-1].type == CAPABLANK && this->pieces[i][j-1].color == 0 && this->pieces[i][j-1].type == CAPAPAWN && this->pieces[i][j-1].moves == 1){
                                this->pieces[i+1][j-1].square.setFillColor(sf::Color::Red);
                            }
                        }
                        if(j < 9){
                            if(this->pieces[i+1][j+1].type == CAPABLANK && this->pieces[i][j+1].color == 0 && this->pieces[i][j+1].type == CAPAPAWN && this->pieces[i][j+1].moves == 1){
                                this->pieces[i+1][j+1].square.setFillColor(sf::Color::Red);
                            }
                        }
                    }
                }
            }
            else{
                if(i > 0){ //Do not pass the board!
                    if(this->pieces[i - 1][j].type == CAPABLANK){ //if the square in front of the pawn is blank
                        //this->pieces[i + 1][j].square.setFillColor(sf::Color::Green); //highlight it in green
                        this->pieces[i - 1][j].highlighted = true;
                        if(i == 6){ //if is the first move of the paw
                            if(this->pieces[i - 2][j].type == CAPABLANK){
                                //this->pieces[i + 2][j].square.setFillColor(sf::Color::Green); //highlight the second one too!
                                this->pieces[i - 2][j].highlighted = true;
                            }
                        }
                    }
                    if(i - 1 > -1 && j + 1 < 8){ //test if the sides are inside the board
                        if(this->pieces[i-1][j+1].type != CAPABLANK && this->pieces[i-1][j+1].color != this->pieces[i][j].color){ //if the diagonal squares are from a different color
                            this->pieces[i-1][j+1].square.setFillColor(sf::Color::Red); //its a enemy piece! highlight it in red
                        }
                        if(j - 1 >= 0){ //same here
                            if(this->pieces[i-1][j-1].type != CAPABLANK && this->pieces[i-1][j-1].color != this->pieces[i][j].color){
                                this->pieces[i-1][j-1].square.setFillColor(sf::Color::Red);
                            }
                        }
                    }
                    if(j == 9){
                        if(this->pieces[i-1][j-1].type != CAPABLANK && this->pieces[i-1][j-1].color != this->pieces[i][j].color){
                            this->pieces[i-1][j-1].square.setFillColor(sf::Color::Red);
                        }
                    }
                    if(i == 3){ //en passant
                        if(j > 0){
                            if(this->pieces[i-1][j-1].type == CAPABLANK && this->pieces[i][j-1].color == 0 && this->pieces[i][j-1].type == CAPAPAWN && this->pieces[i][j-1].moves == 1){
                                this->pieces[i-1][j-1].square.setFillColor(sf::Color::Red);
                            }
                        }
                        if(j < 9){
                            if(this->pieces[i-1][j+1].type == CAPABLANK && this->pieces[i][j+1].color == 0 && this->pieces[i][j+1].type == CAPAPAWN && this->pieces[i][j+1].moves == 1){
                                this->pieces[i-1][j+1].square.setFillColor(sf::Color::Red);
                            }
                        }
                    }
                }
            }

        break;
        case CAPATOWER:
            this->HighlightTower(i, j);
        break;
        case CAPABISHOP:
            this->HighlightBishop(i, j);
        break;
        case CAPAQUEEN:
            HighlightTower(i, j);
            HighlightBishop(i, j);
        break;
        case CAPAKNIGHT:
            HighlightKnight(i, j);
        break;
        case ARCHBISHOP:
            HighlightBishop(i, j);
            HighlightKnight(i, j);
        break;
        case CHANCELER:
            HighlightKnight(i, j);
            HighlightTower(i, j);
        break;
        case CAPAKING:
            HighlightKing(i, j);
        break;
    }

}

void Capaboard::HighlightTower(int i, int j){
    bool stop = false;
    int k;
    if(i < 7){ //front
        for(k = i+1; k <= 7 && !stop; k++){ //while  in the board and we've not found an enemy yet
            if(this->pieces[k][j].type == CAPABLANK){
                this->pieces[k][j].square.setFillColor(sf::Color::Green); //blank piece
            }
            else if(this->pieces[k][j].color != this->pieces[i][j].color){ //enemy piece
                this->pieces[k][j].square.setFillColor(sf::Color::Red);
                stop = true;
            }
            else{ //ally piece
                stop = true;
            }
        }
    }   //do the same for the three other sides of the tower
    if(i > 0){ //below
        stop = false;
        for(k = i - 1; k >= 0 && !stop; k--){
            if(this->pieces[k][j].type == CAPABLANK){
                this->pieces[k][j].square.setFillColor(sf::Color::Green); //blank piece
            }
            else if(this->pieces[k][j].color != this->pieces[i][j].color){ //enemy piece
                this->pieces[k][j].square.setFillColor(sf::Color::Red);
                stop = true;
            }
            else{ //ally piece
                stop = true;
            }
        }
    }
    stop = false;
    if(j < 9){ //Right
        for(k = j + 1; k <= 9 && !stop; k++){
            if(this->pieces[i][k].type == CAPABLANK){
                this->pieces[i][k].square.setFillColor(sf::Color::Green); //blank piece
            }
            else if(this->pieces[i][k].color != this->pieces[i][j].color){ //enemy piece
                this->pieces[i][k].square.setFillColor(sf::Color::Red);
                stop = true;
            }
            else{ //ally piece
                stop = true;
            }
        }
    }
    stop = false;
    if(j > 0){ //Left
        for(k = j - 1; k >= 0 && !stop; k--){
            if(this->pieces[i][k].type == CAPABLANK){
                this->pieces[i][k].square.setFillColor(sf::Color::Green); //blank piece
            }
            else if(this->pieces[i][k].color != this->pieces[i][j].color){ //enemy piece
                this->pieces[i][k].square.setFillColor(sf::Color::Red);
                stop = true;
            }
            else{ //ally piece
                stop = true;
            }
        }
    }
}

void Capaboard::HighlightBishop(int i, int j){
    int k, p;
    bool stop = false;
    if(i < 7){ //front
        if(j < 9){ //front-right
            for(k = i + 1, p = j + 1; k <= 9 && p <= 9 && !stop; k++, p++){
                if(this->pieces[k][p].type == CAPABLANK){
                    this->pieces[k][p].square.setFillColor(sf::Color::Green); //blank piece
                }
                else if(this->pieces[k][p].color != this->pieces[i][j].color){ //enemy piece
                    this->pieces[k][p].square.setFillColor(sf::Color::Red);
                    stop = true;
                }
                else{ //ally piece
                    stop = true;
                }
            }
        }
        stop = false;
        if(j > 0){ //front-left
            for(k = i + 1, p = j - 1; k <= 7 && p >= 0 && !stop; k++, p--){
                if(this->pieces[k][p].type == CAPABLANK){
                    this->pieces[k][p].square.setFillColor(sf::Color::Green); //blank piece
                }
                else if(this->pieces[k][p].color != this->pieces[i][j].color){ //enemy piece
                    this->pieces[k][p].square.setFillColor(sf::Color::Red);
                    stop = true;
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
                if(this->pieces[k][p].type == CAPABLANK){
                    this->pieces[k][p].square.setFillColor(sf::Color::Green); //blank piece
                }
                else if(this->pieces[k][p].color != this->pieces[i][j].color){ //enemy piece
                    this->pieces[k][p].square.setFillColor(sf::Color::Red);
                    stop = true;
                }
                else{ //ally piece
                    stop = true;
                }
            }
        }
        stop = false;
        if(j > 0){ //back-right
            for(k = i - 1, p = j - 1; k >= 0 && p >= 0 && !stop; k--, p--){
                if(this->pieces[k][p].type == CAPABLANK){
                    this->pieces[k][p].square.setFillColor(sf::Color::Green); //blank piece
                }
                else if(this->pieces[k][p].color != this->pieces[i][j].color){ //enemy piece
                    this->pieces[k][p].square.setFillColor(sf::Color::Red);
                    stop = true;
                }
                else{ //ally piece
                    stop = true;
                }
            }
        }
        stop = false;
    }
}

void Capaboard::HighlightKnight(int i, int j){
    if(i + 1 < 7){//north squares
        if(j < 9){
            if(this->pieces[i+2][j+1].type == CAPABLANK){ //front square
                this->pieces[i+2][j+1].square.setFillColor(sf::Color::Green);
            }
            else if(this->pieces[i+2][j+1].color != this->pieces[i][j].color){
                this->pieces[i+2][j+1].square.setFillColor(sf::Color::Red);
            }
        }
        if(j > 0){
            if(this->pieces[i+2][j-1].type == CAPABLANK){ //front square
                this->pieces[i+2][j-1].square.setFillColor(sf::Color::Green);
            }
            else if(this->pieces[i+2][j-1].color != this->pieces[i][j].color){
                this->pieces[i+2][j-1].square.setFillColor(sf::Color::Red);
            }
        }
    }
    if(i - 1 > 0){//south squares
        if(j < 9){
            if(this->pieces[i-2][j+1].type == CAPABLANK){ //front square
                this->pieces[i-2][j+1].square.setFillColor(sf::Color::Green);
            }
            else if(this->pieces[i-2][j+1].color != this->pieces[i][j].color){
                this->pieces[i-2][j+1].square.setFillColor(sf::Color::Red);
            }
        }
        if(j > 0){
            if(this->pieces[i-2][j-1].type == CAPABLANK){ //front square
                this->pieces[i-2][j-1].square.setFillColor(sf::Color::Green);
            }
            else if(this->pieces[i-2][j-1].color != this->pieces[i][j].color){
                this->pieces[i-2][j-1].square.setFillColor(sf::Color::Red);
            }
        }
    }
    if(i < 7){
        if(j + 1 < 9){
            if(this->pieces[i+1][j+2].type == CAPABLANK){ //front square
                this->pieces[i+1][j+2].square.setFillColor(sf::Color::Green);
            }
            else if(this->pieces[i+1][j+2].color != this->pieces[i][j].color){
                this->pieces[i+1][j+2].square.setFillColor(sf::Color::Red);
            }
        }
        if(j - 1 > 0){
            if(this->pieces[i+1][j-2].type == CAPABLANK){ //front square
                this->pieces[i+1][j-2].square.setFillColor(sf::Color::Green);
            }
            else if(this->pieces[i+1][j-2].color != this->pieces[i][j].color){
                this->pieces[i+1][j-2].square.setFillColor(sf::Color::Red);
            }
        }
    }
    if(i > 0){
        if(j + 1 < 9){
            if(this->pieces[i-1][j+2].type == CAPABLANK){ //front square
                this->pieces[i-1][j+2].square.setFillColor(sf::Color::Green);
            }
            else if(this->pieces[i-1][j+2].color != this->pieces[i][j].color){
                this->pieces[i-1][j+2].square.setFillColor(sf::Color::Red);
            }
        }
        if(j - 1 > 0){
            if(this->pieces[i-1][j-2].type == CAPABLANK){ //front square
                this->pieces[i-1][j-2].square.setFillColor(sf::Color::Green);
            }
            else if(this->pieces[i-1][j-2].color != this->pieces[i][j].color){
                this->pieces[i-1][j-2].square.setFillColor(sf::Color::Red);
            }
        }
    }
}

void Capaboard::HighlightKing(int i, int j){
    if(i < 7){ //for the king, test individually the 8 possible squares he can go
        if(this->pieces[i+1][j].type == CAPABLANK){ //front square
            this->pieces[i+1][j].square.setFillColor(sf::Color::Green);
        }
        else if(this->pieces[i+1][j].color != this->pieces[i][j].color){
            this->pieces[i+1][j].square.setFillColor(sf::Color::Red);
        }
        if(j < 9){ //front-right square
            if(this->pieces[i+1][j+1].type == CAPABLANK){
                this->pieces[i+1][j+1].square.setFillColor(sf::Color::Green);
            }
            else if(this->pieces[i+1][j+1].color != this->pieces[i][j].color){
                this->pieces[i+1][j+1].square.setFillColor(sf::Color::Red);
            }
        }
        if(j > 0){ //front-left square
            if(this->pieces[i+1][j-1].type == CAPABLANK){
                this->pieces[i+1][j-1].square.setFillColor(sf::Color::Green);
            }
            else if(this->pieces[i+1][j-1].color != this->pieces[i][j].color){
                this->pieces[i+1][j-1].square.setFillColor(sf::Color::Red);
            }
        }
    }
    if(j < 9){ //right square
        if(this->pieces[i][j+1].type == CAPABLANK){
                this->pieces[i][j+1].square.setFillColor(sf::Color::Green);
            }
            else if(this->pieces[i][j+1].color != this->pieces[i][j].color){
                this->pieces[i][j+1].square.setFillColor(sf::Color::Red);
            }
    }
    if(j > 0){ //left square
        if(this->pieces[i][j-1].type == CAPABLANK){
                this->pieces[i][j-1].square.setFillColor(sf::Color::Green);
            }
            else if(this->pieces[i][j-1].color != this->pieces[i][j].color){
                this->pieces[i][j-1].square.setFillColor(sf::Color::Red);
            }
    }
    if(i > 0){
        if(this->pieces[i-1][j].type == CAPABLANK){ //back square
            this->pieces[i-1][j].square.setFillColor(sf::Color::Green);
        }
        else if(this->pieces[i-1][j].color != this->pieces[i][j].color){
            this->pieces[i-1][j].square.setFillColor(sf::Color::Red);
        }
        if(j < 9){ //back-right square
            if(this->pieces[i-1][j+1].type == CAPABLANK){
                this->pieces[i-1][j+1].square.setFillColor(sf::Color::Green);
            }
            else if(this->pieces[i-1][j+1].color != this->pieces[i][j].color){
                this->pieces[i-1][j+1].square.setFillColor(sf::Color::Red);
            }
        }
        if(j > 0){ //back-left square
            if(this->pieces[i-1][j-1].type == CAPABLANK){
                this->pieces[i-1][j-1].square.setFillColor(sf::Color::Green);
            }
            else if(this->pieces[i-1][j-1].color != this->pieces[i][j].color){
                this->pieces[i-1][j-1].square.setFillColor(sf::Color::Red);
            }
        }
    }
    HighlightCastling(i, j); //Also, highlight the castling, if possible
}

void Capaboard::HighlightCastling(int i, int j){
    if(!this->pieces[i][j].hasMoved && !this->pieces[i][j+4].hasMoved && this->pieces[i][j+4].type == CAPATOWER){ //Neither of the pieces must have been moved
        if(this->pieces[i][j+1].type == CAPABLANK && this->pieces[i][j+2].type == CAPABLANK && this->pieces[i][j+3].type == CAPABLANK){ //the middle pieces must be blanks
            this->pieces[i][j+3].square.setFillColor(sf::Color::Green);
        }
    }
    if(!this->pieces[i][j].hasMoved && !this->pieces[i][j-5].hasMoved && this->pieces[i][j-5].type == CAPATOWER){ //Neither of the pieces must have been moved
        if(this->pieces[i][j-1].type == CAPABLANK && this->pieces[i][j-2].type == CAPABLANK && this->pieces[i][j-3].type == CAPABLANK && this->pieces[i][j-4].type == CAPABLANK){ //the middle pieces must be blanks
            this->pieces[i][j-3].square.setFillColor(sf::Color::Green);
        }
    }
}

