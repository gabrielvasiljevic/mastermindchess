#include <SFML/Graphics.hpp>
#include "headers/pieces.h"
#include "headers/board.h"

#define SIZE_PIECE 64
using namespace std;

    Piece pawn(PAWN);
    Piece tower(TOWER);
    Piece bishop(BISHOP);
    Piece knight(KNIGHT);
    Piece queen(QUEEN);
    Piece king(KING);
    Piece archbishop(ARCHBISHOP);
    Piece chanceler(CHANCELER);
    Piece blank(BLANK);

Board::Board(int board_x, int board_y, int color, int gametype){
    this->gametype = gametype;
    if(gametype == 2) columns = 10;
    else columns = 8;
    if(color == 1)
        Initialize(board_x, board_y, gametype);
    else
        InitializeBlack(board_x, board_y, gametype);

    if(gametype == 1)
        randomizePieces();

}

//Changing a single number in this code will destroy the entire game. Be careful!


void Board::Initialize(int board_x, int board_y, int gametype){
    this->gametype = gametype;
    organizePieces(1, gametype);
    for(int i = 2; i < 6; i++){ //The middle pieces are all blanks in the beginning
        for(int j = 0; j < columns; j++){
            pieces[i][j] = blank;
            pieces[i][j].color = -1;
            pieces[i][j].gametype = this->gametype;
            pieces[i][j].columns = this->columns;
            pieces[i][j].image.setPosition(board_x + SIZE_PIECE*(j), (board_y + SIZE_PIECE*5) - SIZE_PIECE*(i-2));
            pieces[i][j].square.setPosition(board_x + SIZE_PIECE*(j), (board_y + SIZE_PIECE*5) - SIZE_PIECE*(i-2)); //initial point + (wanted square)*(size of square)
            sf::FloatRect squareRect(pieces[i][j].square.getPosition().x, pieces[i][j].square.getPosition().y,
                         pieces[i][j].square.getSize().x, pieces[i][j].square.getSize().y);
            pieces[i][j].rectSquare = squareRect; //Creates the FloatRect in the same position
            pieces[i][j].border.setPosition(board_x + SIZE_PIECE*(j), (board_y + SIZE_PIECE*5) - SIZE_PIECE*(i-2));
            pieces[i][j].grayborder.setPosition(board_x + SIZE_PIECE*(j), (board_y + SIZE_PIECE*5) - SIZE_PIECE*(i-2));
            pieces[i][j].yellowborder.setPosition(board_x + SIZE_PIECE*(j), (board_y + SIZE_PIECE*5) - SIZE_PIECE*(i-2));
            pieces[i][j].redborder.setPosition(board_x + SIZE_PIECE*(j), (board_y + SIZE_PIECE*5) - SIZE_PIECE*(i-2));
        }
    }

    for(int x = 0; x < columns; x++){ //Set the position of the pawns
        pieces[1][x].gametype = this->gametype;
        pieces[1][x].columns = this->columns;
        pieces[1][x].image.setPosition(board_x + SIZE_PIECE*(x), board_y + 6*SIZE_PIECE); //460
        pieces[1][x].square.setPosition(board_x + SIZE_PIECE*(x), board_y + 6*SIZE_PIECE);
        pieces[1][x].border.setPosition(board_x + SIZE_PIECE*(x), board_y + 6*SIZE_PIECE);
        pieces[1][x].grayborder.setPosition(board_x + SIZE_PIECE*(x), board_y + 6*SIZE_PIECE);
        pieces[1][x].yellowborder.setPosition(board_x + SIZE_PIECE*(x), board_y + 6*SIZE_PIECE);
        pieces[1][x].redborder.setPosition(board_x + SIZE_PIECE*(x), board_y + 6*SIZE_PIECE);
        sf::FloatRect squareRect(pieces[1][x].square.getPosition().x, pieces[1][x].square.getPosition().y,
                                 pieces[1][x].square.getSize().x, pieces[1][x].square.getSize().y);
        pieces[1][x].rectSquare = squareRect;

        pieces[6][x].gametype = this->gametype;
        pieces[6][x].columns = this->columns;
        pieces[6][x].image.setPosition(board_x + SIZE_PIECE*(x), board_y + SIZE_PIECE);
        pieces[6][x].square.setPosition(board_x + SIZE_PIECE*(x), board_y + SIZE_PIECE);
        pieces[6][x].border.setPosition(board_x + SIZE_PIECE*(x), board_y + SIZE_PIECE);
        pieces[6][x].grayborder.setPosition(board_x + SIZE_PIECE*(x), board_y + SIZE_PIECE);
        pieces[6][x].yellowborder.setPosition(board_x + SIZE_PIECE*(x), board_y + SIZE_PIECE);
        pieces[6][x].redborder.setPosition(board_x + SIZE_PIECE*(x), board_y + SIZE_PIECE);
        sf::FloatRect squareRect2(pieces[6][x].square.getPosition().x, pieces[6][x].square.getPosition().y,
                                  pieces[6][x].square.getSize().x, pieces[6][x].square.getSize().y);
        pieces[6][x].rectSquare = squareRect2;
    }

    for(int i = 0; i < columns; i++){ //Set the position of the other pieces
        pieces[0][i].gametype = this->gametype;
        pieces[0][i].columns = this->columns;
        pieces[0][i].image.setPosition(board_x + SIZE_PIECE*(i), board_y + 7*SIZE_PIECE); //520
        pieces[0][i].square.setPosition(board_x + SIZE_PIECE*(i), board_y + 7*SIZE_PIECE);
        pieces[0][i].border.setPosition(board_x + SIZE_PIECE*(i), board_y + 7*SIZE_PIECE);
        pieces[0][i].grayborder.setPosition(board_x + SIZE_PIECE*(i), board_y + 7*SIZE_PIECE);
        pieces[0][i].yellowborder.setPosition(board_x + SIZE_PIECE*(i), board_y + 7*SIZE_PIECE);
        pieces[0][i].redborder.setPosition(board_x + SIZE_PIECE*(i), board_y + 7*SIZE_PIECE);
        sf::FloatRect squareRect0(pieces[0][i].square.getPosition().x, pieces[0][i].square.getPosition().y,
                                 pieces[0][i].square.getSize().x, pieces[0][i].square.getSize().y);
        pieces[0][i].rectSquare = squareRect0;

        pieces[7][i].gametype = this->gametype;
        pieces[7][i].columns = this->columns;
        pieces[7][i].image.setPosition(board_x + SIZE_PIECE*(i), board_y);
        pieces[7][i].square.setPosition(board_x + SIZE_PIECE*(i), board_y);
        pieces[7][i].border.setPosition(board_x + SIZE_PIECE*(i), board_y);
        pieces[7][i].grayborder.setPosition(board_x + SIZE_PIECE*(i), board_y);
        pieces[7][i].yellowborder.setPosition(board_x + SIZE_PIECE*(i), board_y);
        pieces[7][i].redborder.setPosition(board_x + SIZE_PIECE*(i), board_y);
        sf::FloatRect squareRect1(pieces[7][i].square.getPosition().x, pieces[7][i].square.getPosition().y,
                                 pieces[7][i].square.getSize().x, pieces[7][i].square.getSize().y);
        pieces[7][i].rectSquare = squareRect1;

    }
}

//For the black pieces, do the same as the white, but setting the position in an inverse way, starting from the end
void Board::InitializeBlack(int board_x, int board_y, int gametype){
    this->gametype = gametype;
    organizePieces(0, gametype);
    if(gametype == 2) board_x += 130;
    for(int i = 2; i < 6; i++){ //The middle pieces are all blanks in the beginning
        for(int j = 0; j < columns; j++){
            pieces[i][j] = blank;
            pieces[i][j].color = -1;
            pieces[i][j].gametype = this->gametype;
            pieces[i][j].columns = this->columns;
            pieces[i][j].image.setPosition(board_x + SIZE_PIECE*(7 - j), (board_y + SIZE_PIECE*5) - SIZE_PIECE*(5-i));
            pieces[i][j].square.setPosition(board_x + SIZE_PIECE*(7 - j), (board_y + SIZE_PIECE*5) - SIZE_PIECE*(5-i)); //initial point + (wanted square)*(size of square)
            sf::FloatRect squareRect(pieces[i][j].square.getPosition().x, pieces[i][j].square.getPosition().y,
                         pieces[i][j].square.getSize().x, pieces[i][j].square.getSize().y);
            pieces[i][j].rectSquare = squareRect; //Creates the FloatRect in the same position
            pieces[i][j].border.setPosition(board_x + SIZE_PIECE*(7 - j), (board_y + SIZE_PIECE*5) - SIZE_PIECE*(5-i));
            pieces[i][j].grayborder.setPosition(board_x + SIZE_PIECE*(7 - j), (board_y + SIZE_PIECE*5) - SIZE_PIECE*(5-i));
            pieces[i][j].redborder.setPosition(board_x + SIZE_PIECE*(7 - j), (board_y + SIZE_PIECE*5) - SIZE_PIECE*(5-i));
            pieces[i][j].yellowborder.setPosition(board_x + SIZE_PIECE*(7 - j), (board_y + SIZE_PIECE*5) - SIZE_PIECE*(5-i));
        }
    }


    for(int x = 0; x < columns; x++){ //Set the position of the pawns

        pieces[1][x].gametype = this->gametype;
        pieces[1][x].columns = this->columns;
        pieces[1][x].image.setPosition(board_x + SIZE_PIECE*(7 - x), board_y + SIZE_PIECE);
        pieces[1][x].square.setPosition(board_x + SIZE_PIECE*(7 - x), board_y + SIZE_PIECE);
        pieces[1][x].border.setPosition(board_x + SIZE_PIECE*(7 - x), board_y + SIZE_PIECE);
        pieces[1][x].grayborder.setPosition(board_x + SIZE_PIECE*(7 - x), board_y + SIZE_PIECE);
        pieces[1][x].yellowborder.setPosition(board_x + SIZE_PIECE*(7 - x), board_y + SIZE_PIECE);
        pieces[1][x].redborder.setPosition(board_x + SIZE_PIECE*(7 - x), board_y + SIZE_PIECE);
        sf::FloatRect squareRect(pieces[1][x].square.getPosition().x, pieces[1][x].square.getPosition().y,
                                 pieces[1][x].square.getSize().x, pieces[1][x].square.getSize().y);
        pieces[1][x].rectSquare = squareRect;

        pieces[6][x].gametype = this->gametype;
        pieces[6][x].columns = this->columns;
        pieces[6][x].image.setPosition(board_x + SIZE_PIECE*(7 - x), board_y + 6*SIZE_PIECE);
        pieces[6][x].square.setPosition(board_x + SIZE_PIECE*(7 - x), board_y + 6*SIZE_PIECE);
        pieces[6][x].border.setPosition(board_x + SIZE_PIECE*(7 - x), board_y + 6*SIZE_PIECE);
        pieces[6][x].grayborder.setPosition(board_x + SIZE_PIECE*(7 - x), board_y + 6*SIZE_PIECE);
        pieces[6][x].yellowborder.setPosition(board_x + SIZE_PIECE*(7 - x), board_y + 6*SIZE_PIECE);
        pieces[6][x].redborder.setPosition(board_x + SIZE_PIECE*(7 - x), board_y + 6*SIZE_PIECE);
        sf::FloatRect squareRect2(pieces[6][x].square.getPosition().x, pieces[6][x].square.getPosition().y,
                                  pieces[6][x].square.getSize().x, pieces[6][x].square.getSize().y);
        pieces[6][x].rectSquare = squareRect2;
    }
    for(int i = 0; i < columns; i++){ //Set the position of the other pieces
        pieces[0][i].gametype = this->gametype;
        pieces[0][i].columns = this->columns;
        pieces[0][i].image.setPosition(board_x + SIZE_PIECE*(7 - i), board_y);
        pieces[0][i].square.setPosition(board_x + SIZE_PIECE*(7 - i), board_y);
        pieces[0][i].border.setPosition(board_x + SIZE_PIECE*(7 - i), board_y);
        pieces[0][i].grayborder.setPosition(board_x + SIZE_PIECE*(7 - i), board_y);
        pieces[0][i].yellowborder.setPosition(board_x + SIZE_PIECE*(7 - i), board_y);
        pieces[0][i].redborder.setPosition(board_x + SIZE_PIECE*(7 - i), board_y);
        sf::FloatRect squareRect0(pieces[0][i].square.getPosition().x, pieces[0][i].square.getPosition().y,
                                 pieces[0][i].square.getSize().x, pieces[0][i].square.getSize().y);
        pieces[0][i].rectSquare = squareRect0;

        pieces[7][i].gametype = this->gametype;
        pieces[7][i].columns = this->columns;
        pieces[7][i].image.setPosition(board_x + SIZE_PIECE*(7 - i), board_y + 7*SIZE_PIECE);
        pieces[7][i].square.setPosition(board_x + SIZE_PIECE*(7 - i), board_y + 7*SIZE_PIECE);
        pieces[7][i].border.setPosition(board_x + SIZE_PIECE*(7 - i), board_y + 7*SIZE_PIECE);
        pieces[7][i].grayborder.setPosition(board_x + SIZE_PIECE*(7 - i), board_y + 7*SIZE_PIECE);
        pieces[7][i].redborder.setPosition(board_x + SIZE_PIECE*(7 - i), board_y + 7*SIZE_PIECE);
        pieces[7][i].yellowborder.setPosition(board_x + SIZE_PIECE*(7 - i), board_y + 7*SIZE_PIECE);
        sf::FloatRect squareRect1(pieces[7][i].square.getPosition().x, pieces[7][i].square.getPosition().y,
                                 pieces[7][i].square.getSize().x, pieces[7][i].square.getSize().y);
        pieces[7][i].rectSquare = squareRect1;

    }

}

void Board::organizePieces(int color, int gametype){
    for(int i = 0; i < columns; i++){
        pieces[1][i] = pawn;
        pieces[6][i] = pawn;

        pieces[1][i].color = 1;
        pieces[6][i].color = 0;
    }

    if(color){ //Set the position according to the color
        if(gametype == 0){
            //Towers
            pieces[0][0] = tower;
            pieces[0][7] = tower;
            pieces[7][0] = tower;
            pieces[7][7] = tower;

            //Knights
            pieces[0][1] = knight;
            pieces[0][6] = knight;
            pieces[7][1] = knight;
            pieces[7][6] = knight;

            //Bishops
            pieces[0][2] = bishop;
            pieces[0][5] = bishop;
            pieces[7][2] = bishop;
            pieces[7][5] = bishop;

            //Queens
            pieces[0][3] = queen;
            pieces[7][3] = queen;

            //Kings
            pieces[0][4] = king;
            pieces[7][4] = king;
        }
        else{
            //Towers
            pieces[0][0] = tower;
            pieces[0][9] = tower;
            pieces[7][0] = tower;
            pieces[7][9] = tower;

            //Knights
            pieces[0][1] = knight;
            pieces[0][8] = knight;
            pieces[7][1] = knight;
            pieces[7][8] = knight;

            //Bishops
            pieces[0][3] = bishop;
            pieces[0][6] = bishop;
            pieces[7][3] = bishop;
            pieces[7][6] = bishop;

            //Queens
            pieces[0][4] = queen;
            pieces[7][4] = queen;

            //Archbishops
            pieces[0][2] = archbishop;
            pieces[7][2] = archbishop;

            //Chancelers
            pieces[0][7] = chanceler;
            pieces[7][7] = chanceler;

            //Kings
            pieces[0][5] = king;
            pieces[7][5] = king;

        }
    }
    else{
        if(gametype == 0){
            //Towers
            pieces[0][0] = tower;
            pieces[0][7] = tower;
            pieces[7][0] = tower;
            pieces[7][7] = tower;

            //Knights
            pieces[0][1] = knight;
            pieces[0][6] = knight;
            pieces[7][1] = knight;
            pieces[7][6] = knight;

            //Bishops
            pieces[0][2] = bishop;
            pieces[0][5] = bishop;
            pieces[7][2] = bishop;
            pieces[7][5] = bishop;

            //Queens
            pieces[0][3] = queen;
            pieces[7][3] = queen;

            //Kings
            pieces[0][4] = king;
            pieces[7][4] = king;
        }
        else{
            //Towers
            pieces[0][0] = tower;
            pieces[0][9] = tower;
            pieces[7][0] = tower;
            pieces[7][9] = tower;

            //Knights
            pieces[0][1] = knight;
            pieces[0][8] = knight;
            pieces[7][1] = knight;
            pieces[7][8] = knight;

            //Bishops
            pieces[0][3] = bishop;
            pieces[0][6] = bishop;
            pieces[7][3] = bishop;
            pieces[7][6] = bishop;

            //Queens
            pieces[0][4] = queen;
            pieces[7][4] = queen;

            //Archbishops
            pieces[0][2] = archbishop;
            pieces[7][2] = archbishop;

            //Chancelers
            pieces[0][7] = chanceler;
            pieces[7][7] = chanceler;

            //Kings
            pieces[0][5] = king;
            pieces[7][5] = king;
        }
    }
    for(int j = 0; j < columns; j++){
        pieces[0][j].color = 1;
        pieces[7][j].color = 0;
    }
}

void Board::randomizePieces(){
    vector <TYPE> remainingPieces = {BISHOP, QUEEN, KNIGHT, BISHOP, KNIGHT};
    int i, position, rpos, kpos, bcolor;
    for(i = 0; i < 8; i++){
        pieces[0][i].type = BLANK;
    }
    srand(time(NULL));
    //Setup the king in a non-corner square;
    kpos = rand()%6 + 1; //1 to 6
    pieces[0][kpos].type = KING;

    //The first rook must be on the left side of the king
    rpos = rand()%kpos; //0 to king
    pieces[0][rpos].type = TOWER;

    //The second rook must be on the right side of the king
    rpos = kpos + 1 + rand()%(7 - kpos); //
    pieces[0][rpos].type = TOWER;

    for(i = 0; i < 8; i++){
        srand(time(NULL));
        if(pieces[0][i].type == BLANK){
            position = rand()%remainingPieces.size();
            pieces[0][i].type = remainingPieces[position];
            remainingPieces.erase(remainingPieces.begin() + position);
        }

    }
    for(int i = 0; i < 8; i++){ //Set the position of the black pieces
        pieces[7][i].type = pieces[0][i].type;
    }
}

void Board::Highlight(TYPE t, int i, int j){
    bool stop = false;
    switch(t){
        case PAWN:
            if(this->pieces[i][j].color == 1){
               if(i < 7){ //Do not pass the board!
                    if(this->pieces[i + 1][j].type == BLANK){ //if the square in front of the pawn is blank
                        //this->pieces[i + 1][j].highlighted = true; //highlight it in green
                        this->pieces[i + 1][j].highlighted = true;
                        if(i == 1){ //if is the first move of the paw
                            if(this->pieces[i + 2][j].type == BLANK){
                                //this->pieces[i + 2][j].highlighted = true; //highlight the second one too!
                                this->pieces[i + 2][j].highlighted = true;
                            }
                        }
                    }
                    if(i + 1 < 8 && j + 1 < 8){ //test if the sides are inside the board
                        if(this->pieces[i+1][j+1].type != BLANK && this->pieces[i+1][j+1].color != this->pieces[i][j].color){ //if the diagonal squares are from a different color
                            this->pieces[i+1][j+1].attacked = true; //its a enemy piece! highlight it in red
                        }
                        if(j - 1 >= 0){ //same here
                            if(this->pieces[i+1][j-1].type != BLANK && this->pieces[i+1][j-1].color != this->pieces[i][j].color){
                                this->pieces[i+1][j-1].attacked = true;
                            }
                        }
                    }
                    if(j == columns - 1){
                        if(this->pieces[i+1][j-1].type != BLANK && this->pieces[i+1][j-1].color != this->pieces[i][j].color){
                            this->pieces[i+1][j-1].attacked = true;
                        }
                    }
                    if(i == 4){ //en passant
                        if(j > 0){
                            if(this->pieces[i+1][j-1].type == BLANK && this->pieces[i][j-1].color == 0 && this->pieces[i][j-1].type == PAWN && this->pieces[i][j-1].moves == 1){
                                this->pieces[i+1][j-1].attacked = true;
                            }
                        }
                        if(j < columns - 1){
                            if(this->pieces[i+1][j+1].type == BLANK && this->pieces[i][j+1].color == 0 && this->pieces[i][j+1].type == PAWN && this->pieces[i][j+1].moves == 1){
                                this->pieces[i+1][j+1].attacked = true;
                            }
                        }
                    }
                }
            }
            else{
                if(i > 0){ //Do not pass the board!
                    if(this->pieces[i - 1][j].type == BLANK){ //if the square in front of the pawn is blank
                        //this->pieces[i + 1][j].highlighted = true; //highlight it in green
                        this->pieces[i - 1][j].highlighted = true;
                        if(i == 6){ //if is the first move of the paw
                            if(this->pieces[i - 2][j].type == BLANK){
                                //this->pieces[i + 2][j].highlighted = true; //highlight the second one too!
                                this->pieces[i - 2][j].highlighted = true;
                            }
                        }
                    }
                    if(i - 1 > -1 && j + 1 < columns){ //test if the sides are inside the board
                        if(this->pieces[i-1][j+1].type != BLANK && this->pieces[i-1][j+1].color != this->pieces[i][j].color){ //if the diagonal squares are from a different color
                            this->pieces[i-1][j+1].attacked = true; //its a enemy piece! highlight it in red
                        }
                        if(j - 1 >= 0){ //same here
                            if(this->pieces[i-1][j-1].type != BLANK && this->pieces[i-1][j-1].color != this->pieces[i][j].color){
                                //this->pieces[i-1][j-1].attacked = true;
                                this->pieces[i-1][j-1].attacked = true;
                            }
                        }
                    }
                    if(j == columns - 1){
                        if(this->pieces[i-1][j-1].type != BLANK && this->pieces[i-1][j-1].color != this->pieces[i][j].color){
                            this->pieces[i-1][j-1].attacked = true;
                        }
                    }
                    if(i == 3){ //en passant
                        if(j > 0){
                            if(this->pieces[i-1][j-1].type == BLANK && this->pieces[i][j-1].color == 0 && this->pieces[i][j-1].type == PAWN && this->pieces[i][j-1].moves == 1){
                                this->pieces[i-1][j-1].attacked = true;
                            }
                        }
                        if(j < columns - 1){
                            if(this->pieces[i-1][j+1].type == BLANK && this->pieces[i][j+1].color == 0 && this->pieces[i][j+1].type == PAWN && this->pieces[i][j+1].moves == 1){
                                this->pieces[i-1][j+1].attacked = true;
                            }
                        }
                    }
                }
            }

        break;
        case TOWER:
            this->HighlightTower(i, j);
        break;
        case BISHOP:
            this->HighlightBishop(i, j);
        break;
        case QUEEN:
            HighlightTower(i, j);
            HighlightBishop(i, j);
        break;
        case KNIGHT:
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
        case KING:
            HighlightKing(i, j);
        break;
    }

}

void Board::HighlightTower(int i, int j){
    bool stop = false;
    int k;
    if(i < 7){ //front
        for(k = i+1; k <= 7 && !stop; k++){ //while  in the board and we've not found an enemy yet
            if(this->pieces[k][j].type == BLANK){
                this->pieces[k][j].highlighted = true; //blank piece
            }
            else if(this->pieces[k][j].color != this->pieces[i][j].color){ //enemy piece
                this->pieces[k][j].attacked = true;
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
            if(this->pieces[k][j].type == BLANK){
                this->pieces[k][j].highlighted = true; //blank piece
            }
            else if(this->pieces[k][j].color != this->pieces[i][j].color){ //enemy piece
                this->pieces[k][j].attacked = true;
                stop = true;
            }
            else{ //ally piece
                stop = true;
            }
        }
    }
    stop = false;
    if(j < columns - 1){ //Right
        for(k = j + 1; k <= columns - 1 && !stop; k++){
            if(this->pieces[i][k].type == BLANK){
                this->pieces[i][k].highlighted = true; //blank piece
            }
            else if(this->pieces[i][k].color != this->pieces[i][j].color){ //enemy piece
                this->pieces[i][k].attacked = true;
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
            if(this->pieces[i][k].type == BLANK){
                this->pieces[i][k].highlighted = true; //blank piece
            }
            else if(this->pieces[i][k].color != this->pieces[i][j].color){ //enemy piece
                this->pieces[i][k].attacked = true;
                stop = true;
            }
            else{ //ally piece
                stop = true;
            }
        }
    }
}

void Board::HighlightBishop(int i, int j){
    int k, p;
    bool stop = false;
    if(i < 7){ //front
        if(j < columns - 1){ //front-right
            for(k = i + 1, p = j + 1; k <= 7 && p <= columns - 1 && !stop; k++, p++){
                if(this->pieces[k][p].type == BLANK){
                    this->pieces[k][p].highlighted = true; //blank piece
                }
                else if(this->pieces[k][p].color != this->pieces[i][j].color){ //enemy piece
                    this->pieces[k][p].attacked = true;
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
                if(this->pieces[k][p].type == BLANK){
                    this->pieces[k][p].highlighted = true; //blank piece
                }
                else if(this->pieces[k][p].color != this->pieces[i][j].color){ //enemy piece
                    this->pieces[k][p].attacked = true;
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
        if(j < columns - 1){ //back-right
            for(k = i - 1, p = j + 1; k >= 0 && p <= columns - 1 && !stop; k--, p++){
                if(this->pieces[k][p].type == BLANK){
                    this->pieces[k][p].highlighted = true; //blank piece
                }
                else if(this->pieces[k][p].color != this->pieces[i][j].color){ //enemy piece
                    this->pieces[k][p].attacked = true;
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
                if(this->pieces[k][p].type == BLANK){
                    this->pieces[k][p].highlighted = true; //blank piece
                }
                else if(this->pieces[k][p].color != this->pieces[i][j].color){ //enemy piece
                    this->pieces[k][p].attacked = true;
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

void Board::HighlightKnight(int i, int j){
    if(i + 1 < 7){//north squares
        if(j < columns - 1){
            if(this->pieces[i+2][j+1].type == BLANK){ //front square
                this->pieces[i+2][j+1].highlighted = true;
            }
            else if(this->pieces[i+2][j+1].color != this->pieces[i][j].color){
                this->pieces[i+2][j+1].attacked = true;
            }
        }
        if(j > 0){
            if(this->pieces[i+2][j-1].type == BLANK){ //front square
                this->pieces[i+2][j-1].highlighted = true;
            }
            else if(this->pieces[i+2][j-1].color != this->pieces[i][j].color){
                this->pieces[i+2][j-1].attacked = true;
            }
        }
    }
    if(i - 1 > 0){//south squares
        if(j < columns - 1){
            if(this->pieces[i-2][j+1].type == BLANK){ //front square
                this->pieces[i-2][j+1].highlighted = true;
            }
            else if(this->pieces[i-2][j+1].color != this->pieces[i][j].color){
                this->pieces[i-2][j+1].attacked = true;
            }
        }
        if(j > 0){
            if(this->pieces[i-2][j-1].type == BLANK){ //front square
                this->pieces[i-2][j-1].highlighted = true;
            }
            else if(this->pieces[i-2][j-1].color != this->pieces[i][j].color){
                this->pieces[i-2][j-1].attacked = true;
            }
        }
    }
    if(i < 7){
        if(j + 1 < columns - 1){
            if(this->pieces[i+1][j+2].type == BLANK){ //front square
                this->pieces[i+1][j+2].highlighted = true;
            }
            else if(this->pieces[i+1][j+2].color != this->pieces[i][j].color){
                this->pieces[i+1][j+2].attacked = true;
            }
        }
        if(j - 1 > 0){
            if(this->pieces[i+1][j-2].type == BLANK){ //front square
                this->pieces[i+1][j-2].highlighted = true;
            }
            else if(this->pieces[i+1][j-2].color != this->pieces[i][j].color){
                this->pieces[i+1][j-2].attacked = true;
            }
        }
    }
    if(i > 0){
        if(j + 1 < columns - 1){
            if(this->pieces[i-1][j+2].type == BLANK){ //front square
                this->pieces[i-1][j+2].highlighted = true;
            }
            else if(this->pieces[i-1][j+2].color != this->pieces[i][j].color){
                this->pieces[i-1][j+2].attacked = true;
            }
        }
        if(j - 1 > 0){
            if(this->pieces[i-1][j-2].type == BLANK){ //front square
                this->pieces[i-1][j-2].highlighted = true;
            }
            else if(this->pieces[i-1][j-2].color != this->pieces[i][j].color){
                this->pieces[i-1][j-2].attacked = true;
            }
        }
    }
}

void Board::HighlightKing(int i, int j){
    if(i < 7){ //for the king, test individually the 8 possible squares he can go
        if(this->pieces[i+1][j].type == BLANK){ //front square
            this->pieces[i+1][j].highlighted = true;
        }
        else if(this->pieces[i+1][j].color != this->pieces[i][j].color){
            this->pieces[i+1][j].attacked = true;
        }
        if(j < columns - 1){ //front-right square
            if(this->pieces[i+1][j+1].type == BLANK){
                this->pieces[i+1][j+1].highlighted = true;
            }
            else if(this->pieces[i+1][j+1].color != this->pieces[i][j].color){
                this->pieces[i+1][j+1].attacked = true;
            }
        }
        if(j > 0){ //front-left square
            if(this->pieces[i+1][j-1].type == BLANK){
                this->pieces[i+1][j-1].highlighted = true;
            }
            else if(this->pieces[i+1][j-1].color != this->pieces[i][j].color){
                this->pieces[i+1][j-1].attacked = true;
            }
        }
    }
    if(j < columns - 1){ //right square
        if(this->pieces[i][j+1].type == BLANK){
                this->pieces[i][j+1].highlighted = true;
            }
            else if(this->pieces[i][j+1].color != this->pieces[i][j].color){
                this->pieces[i][j+1].attacked = true;
            }
    }
    if(j > 0){ //left square
        if(this->pieces[i][j-1].type == BLANK){
                this->pieces[i][j-1].highlighted = true;
            }
            else if(this->pieces[i][j-1].color != this->pieces[i][j].color){
                this->pieces[i][j-1].attacked = true;
            }
    }
    if(i > 0){
        if(this->pieces[i-1][j].type == BLANK){ //back square
            this->pieces[i-1][j].highlighted = true;
        }
        else if(this->pieces[i-1][j].color != this->pieces[i][j].color){
            this->pieces[i-1][j].attacked = true;
        }
        if(j < columns - 1){ //back-right square
            if(this->pieces[i-1][j+1].type == BLANK){
                this->pieces[i-1][j+1].highlighted = true;
            }
            else if(this->pieces[i-1][j+1].color != this->pieces[i][j].color){
                this->pieces[i-1][j+1].attacked = true;
            }
        }
        if(j > 0){ //back-left square
            if(this->pieces[i-1][j-1].type == BLANK){
                this->pieces[i-1][j-1].highlighted = true;
            }
            else if(this->pieces[i-1][j-1].color != this->pieces[i][j].color){
                this->pieces[i-1][j-1].attacked = true;
            }
        }
    }
    HighlightCastling(i, j); //Also, highlight the castling, if possible
}

void Board::HighlightCastling(int i, int j){
    if(gametype == 0){
       if(!this->pieces[i][j].hasMoved && !this->pieces[i][j+3].hasMoved && this->pieces[i][j+3].type == TOWER){ //Neither of the pieces must have been moved
            if(this->pieces[i][j+1].type == BLANK && this->pieces[i][j+2].type == BLANK){ //the middle pieces must be blanks
                this->pieces[i][j+2].highlighted = true;
            }
        }
        if(!this->pieces[i][j].hasMoved && !this->pieces[i][j-4].hasMoved && this->pieces[i][j-4].type == TOWER){ //Neither of the pieces must have been moved
            if(this->pieces[i][j-1].type == BLANK && this->pieces[i][j-2].type == BLANK && this->pieces[i][j-3].type == BLANK){ //the middle pieces must be blanks
                this->pieces[i][j-2].highlighted = true;
            }
        }
    }
    else if(gametype == 2){
        if(!this->pieces[i][j].hasMoved && !this->pieces[i][j+4].hasMoved && this->pieces[i][j+4].type == TOWER){ //Neither of the pieces must have been moved
            if(this->pieces[i][j+1].type == BLANK && this->pieces[i][j+2].type == BLANK && this->pieces[i][j+3].type == BLANK){ //the middle pieces must be blanks
                this->pieces[i][j+3].square.setFillColor(sf::Color::Green);
            }
        }
        if(!this->pieces[i][j].hasMoved && !this->pieces[i][j-5].hasMoved && this->pieces[i][j-5].type == TOWER){ //Neither of the pieces must have been moved
            if(this->pieces[i][j-1].type == BLANK && this->pieces[i][j-2].type == BLANK && this->pieces[i][j-3].type == BLANK && this->pieces[i][j-4].type == BLANK){ //the middle pieces must be blanks
                this->pieces[i][j-3].square.setFillColor(sf::Color::Green);
            }
        }
    }



}


void Board::setBoard(string newBoard[8][10]){
    int i, j;
    for(i = 0; i < 8; i++){
        for(j = 0; j < 10; j++){
            pieces[i][j].changeType(newBoard[i][j]);
        }
    }
}
