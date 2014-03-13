#include <SFML/Graphics.hpp>
#include <iostream>
#include "board.h"
#include "checkbox.h"


#define BOARD_X 220 //position of the board
#define BOARD_Y 100

using namespace std;

    sf::Texture pawns;
    sf::Texture bpawns;
    sf::Texture towers;
    sf::Texture btowers;
    sf::Texture knights;
    sf::Texture bknights;
    sf::Texture bishops;
    sf::Texture bbishops;
    sf::Texture queens;
    sf::Texture bqueens;
    sf::Texture kings;
    sf::Texture bkings;
    sf::Texture blanks;


void Highlight(Piece b[8][8], TYPE t, int i, int j);
void HighlightTower(Piece b[8][8], int i, int j);
void HighlightBishop(Piece b[8][8], int i, int j);
void Unhighlight(Piece b[8][8]);
void Initialize_Texture(Piece b[8][8]);

int turn = 1; //1 for whites, 0 for blacks.

int main(){
    //window creation and icon setup
    sf::RenderWindow window(sf::VideoMode(933, 700), "MasterMind Chess", sf::Style::Close);
    sf::Image icon;
    icon.loadFromFile("images/Icon.png");
    window.setIcon(256, 256, icon.getPixelsPtr());
    Board b(BOARD_X, BOARD_Y);
    bool pieceClick = false;
    int iPiece;
    int jPiece;
    Checkbox Hint(750, 100, 15, 15, "Hint");
    /*Pieces' texture initialization*/
    Initialize_Texture(b.pieces);


    /*Load board image and texture*/
    sf::Texture Tabuleiro;
    sf::Sprite board;
    if(!Tabuleiro.loadFromFile("images/board.jpg")) return 1;
    board.setTexture(Tabuleiro);
    board.setPosition(BOARD_X, BOARD_Y);

    /*Main loop*/
    while (window.isOpen()){
        sf::Event event;
        /*Handle the events*/
        while (window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                case sf::Event::MouseButtonPressed: //When the mouse button is clicked, check where it was
                    cout << event.mouseButton.x << " " << event.mouseButton.y << endl;
                    for(int i = 0; i < 8; i++){
                        for(int j = 0; j < 8; j++){
                            if(b.pieces[i][j].rectSquare.contains(event.mouseButton.x, event.mouseButton.y)){ //If the click was in a square...
                                cout << i << " " << j << endl;
                                if(!pieceClick && b.pieces[i][j].type != BLANK){ //If a piece was not clicked and the current click was in one...
                                    pieceClick = true;
                                    iPiece = i;
                                    jPiece = j;
                                    b.pieces[i][j].clicked? b.pieces[i][j].square.setFillColor(sf::Color::Transparent) : //If the piece was already clicked once, turn it back to transparent
                                                            b.pieces[i][j].square.setFillColor(sf::Color::Yellow);; //If not, highlight it in yellow
                                    b.pieces[i][j].clicked = !b.pieces[i][j].clicked;
                                    if(Hint.checked) Highlight(b.pieces, b.pieces[i][j].type, i, j);
                                }
                                else if(pieceClick && b.pieces[i][j].type == BLANK ){ //If a piece square was already clicked and the current click was in a blank square...
                                    b.pieces[i][j].movement(b.pieces, i, j, iPiece, jPiece); //Execute a movement, if possible
                                    Initialize_Texture(b.pieces);
                                    Unhighlight(b.pieces);
                                    pieceClick = false;
                                }

                                else if(pieceClick && b.pieces[i][j].color != b.pieces[iPiece][jPiece].color){
                                    b.pieces[i][j].capture(b.pieces, i, j, iPiece, jPiece); //Capture the piece, if possible
                                    Initialize_Texture(b.pieces);
                                    Unhighlight(b.pieces);
                                    pieceClick = false;
                                }

                                else if(pieceClick){ //If a piece was already clicked, but now another one was clicked too
                                    Unhighlight(b.pieces);
                                    pieceClick = false;
                                }
                            }
                        }
                    }
                    if(Hint.clicked(event.mouseButton.x, event.mouseButton.y)){
                        Hint.action();
                    }
                break;
            }
        }
        /*Draw everything*/
        window.clear(sf::Color(0, 150, 255));
        window.draw(board);
        window.draw(Hint.image);

        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                window.draw(b.pieces[i][j].square ); //Draw the background first
                window.draw(b.pieces[i][j].image ); //Then the piece itself
                if(b.pieces[i][j].highlighted){
                    window.draw(b.pieces[i][j].border);
                }
            }
        }
        window.draw(Hint.text);
        window.display();
    }
    return 0;
}

void Unhighlight(Piece b[8][8]){
     for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            b[i][j].square.setFillColor(sf::Color::Transparent);
            b[i][j].highlighted = false;
            b[i][j].clicked = false;
        }
    }
}

void Highlight(Piece b[8][8], TYPE t, int i, int j){
    int k, p;
    bool stop = false;
    switch(t){
        case PAWN:
            if(i < 7){ //Do not pass the board!
                if(b[i + 1][j].type == BLANK){ //if the square in front of the pawn is blank
                    //b[i + 1][j].square.setFillColor(sf::Color::Green); //highlight it in green
                    b[i + 1][j].highlighted = true;
                    if(i == 1){ //if is the first move of the paw
                        if(b[i + 2][j].type == BLANK){
                            //b[i + 2][j].square.setFillColor(sf::Color::Green); //highlight the second one too!
                            b[i + 2][j].highlighted = true;
                        }
                    }
                }
                if(i + 1 < 8 && j + 1 < 8){ //test if the sides are inside the board
                    if(b[i+1][j+1].type != BLANK && b[i+1][j+1].color != b[i][j].color){ //if the diagonal squares are from a different color
                        b[i+1][j+1].square.setFillColor(sf::Color::Red); //its a enemy piece! highlight it in red
                    }
                    if(j - 1 >= 0){ //same here
                        if(b[i+1][j-1].type != BLANK && b[i+1][j-1].color != b[i][j].color){
                            b[i+1][j-1].square.setFillColor(sf::Color::Red);
                        }
                    }
                }
                if(j == 7){
                    if(b[i+1][j-1].type != BLANK && b[i+1][j-1].color != b[i][j].color){
                        b[i+1][j-1].square.setFillColor(sf::Color::Red);
                    }
                }
            }
        break;
        case TOWER:
            HighlightTower(b, i, j);
        break;
        case BISHOP:
            HighlightBishop(b, i, j);
        break;
        case QUEEN:
            HighlightTower(b, i, j);
            HighlightBishop(b, i, j);
        break;
        case KNIGHT:
            if(i + 1 < 7){//north squares
                if(j < 7){
                    if(b[i+2][j+1].type == BLANK){ //front square
                        b[i+2][j+1].square.setFillColor(sf::Color::Green);
                    }
                    else if(b[i+2][j+1].color != b[i][j].color){
                        b[i+2][j+1].square.setFillColor(sf::Color::Red);
                    }
                }
                if(j > 0){
                    if(b[i+2][j-1].type == BLANK){ //front square
                        b[i+2][j-1].square.setFillColor(sf::Color::Green);
                    }
                    else if(b[i+2][j-1].color != b[i][j].color){
                        b[i+2][j-1].square.setFillColor(sf::Color::Red);
                    }
                }
            }
            if(i - 1 > 0){//south squares
                if(j < 7){
                    if(b[i-2][j+1].type == BLANK){ //front square
                        b[i-2][j+1].square.setFillColor(sf::Color::Green);
                    }
                    else if(b[i-2][j+1].color != b[i][j].color){
                        b[i-2][j+1].square.setFillColor(sf::Color::Red);
                    }
                }
                if(j > 0){
                    if(b[i-2][j-1].type == BLANK){ //front square
                        b[i-2][j-1].square.setFillColor(sf::Color::Green);
                    }
                    else if(b[i-2][j-1].color != b[i][j].color){
                        b[i-2][j-1].square.setFillColor(sf::Color::Red);
                    }
                }
            }
            if(i < 7){
                if(j + 1 < 7){
                    if(b[i+1][j+2].type == BLANK){ //front square
                        b[i+1][j+2].square.setFillColor(sf::Color::Green);
                    }
                    else if(b[i+1][j+2].color != b[i][j].color){
                        b[i+1][j+2].square.setFillColor(sf::Color::Red);
                    }
                }
                if(j - 1 > 0){
                    if(b[i+1][j-2].type == BLANK){ //front square
                        b[i+1][j-2].square.setFillColor(sf::Color::Green);
                    }
                    else if(b[i+1][j-2].color != b[i][j].color){
                        b[i+1][j-2].square.setFillColor(sf::Color::Red);
                    }
                }
            }
            if(i > 0){
                if(j + 1 < 7){
                    if(b[i-1][j+2].type == BLANK){ //front square
                        b[i-1][j+2].square.setFillColor(sf::Color::Green);
                    }
                    else if(b[i-1][j+2].color != b[i][j].color){
                        b[i-1][j+2].square.setFillColor(sf::Color::Red);
                    }
                }
                if(j - 1 > 0){
                    if(b[i-1][j-2].type == BLANK){ //front square
                        b[i-1][j-2].square.setFillColor(sf::Color::Green);
                    }
                    else if(b[i-1][j-2].color != b[i][j].color){
                        b[i-1][j-2].square.setFillColor(sf::Color::Red);
                    }
                }
            }
        break;

        case KING:
            if(i < 7){ //for the king, test individually the 8 possible squares he can go
                if(b[i+1][j].type == BLANK){ //front square
                    b[i+1][j].square.setFillColor(sf::Color::Green);
                }
                else if(b[i+1][j].color != b[i][j].color){
                    b[i+1][j].square.setFillColor(sf::Color::Red);
                }
                if(j < 7){ //front-right square
                    if(b[i+1][j+1].type == BLANK){
                        b[i+1][j+1].square.setFillColor(sf::Color::Green);
                    }
                    else if(b[i+1][j+1].color != b[i][j].color){
                        b[i+1][j+1].square.setFillColor(sf::Color::Red);
                    }
                }
                if(j > 0){ //front-left square
                    if(b[i+1][j-1].type == BLANK){
                        b[i+1][j-1].square.setFillColor(sf::Color::Green);
                    }
                    else if(b[i+1][j-1].color != b[i][j].color){
                        b[i+1][j-1].square.setFillColor(sf::Color::Red);
                    }
                }
            }
            if(j < 7){ //right square
                if(b[i][j+1].type == BLANK){
                        b[i][j+1].square.setFillColor(sf::Color::Green);
                    }
                    else if(b[i][j+1].color != b[i][j].color){
                        b[i][j+1].square.setFillColor(sf::Color::Red);
                    }
            }
            if(j > 0){ //left square
                if(b[i][j-1].type == BLANK){
                        b[i][j-1].square.setFillColor(sf::Color::Green);
                    }
                    else if(b[i][j-1].color != b[i][j].color){
                        b[i][j-1].square.setFillColor(sf::Color::Red);
                    }
            }
            if(i > 0){
                if(b[i-1][j].type == BLANK){ //back square
                    b[i-1][j].square.setFillColor(sf::Color::Green);
                }
                else if(b[i-1][j].color != b[i][j].color){
                    b[i-1][j].square.setFillColor(sf::Color::Red);
                }
                if(j < 7){ //back-right square
                    if(b[i-1][j+1].type == BLANK){
                        b[i-1][j+1].square.setFillColor(sf::Color::Green);
                    }
                    else if(b[i-1][j+1].color != b[i][j].color){
                        b[i-1][j+1].square.setFillColor(sf::Color::Red);
                    }
                }
                if(j > 0){ //back-left square
                    if(b[i-1][j-1].type == BLANK){
                        b[i-1][j-1].square.setFillColor(sf::Color::Green);
                    }
                    else if(b[i-1][j-1].color != b[i][j].color){
                        b[i-1][j-1].square.setFillColor(sf::Color::Red);
                    }
                }
            }
        break;
    }
}


void HighlightTower(Piece b[8][8], int i, int j){
    bool stop = false;
    int k;
    if(i < 7){ //front
        for(k = i+1; k <= 7 && !stop; k++){ //while  in the board and we've not found an enemy yet
            if(b[k][j].type == BLANK){
                b[k][j].square.setFillColor(sf::Color::Green); //blank piece
            }
            else if(b[k][j].color != b[i][j].color){ //enemy piece
                b[k][j].square.setFillColor(sf::Color::Red);
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
            if(b[k][j].type == BLANK){
                b[k][j].square.setFillColor(sf::Color::Green); //blank piece
            }
            else if(b[k][j].color != b[i][j].color){ //enemy piece
                b[k][j].square.setFillColor(sf::Color::Red);
                stop = true;
            }
            else{ //ally piece
                stop = true;
            }
        }
    }
    stop = false;
    if(j < 7){ //Right
        for(k = j + 1; k <= 7 && !stop; k++){
            if(b[i][k].type == BLANK){
                b[i][k].square.setFillColor(sf::Color::Green); //blank piece
            }
            else if(b[i][k].color != b[i][j].color){ //enemy piece
                b[i][k].square.setFillColor(sf::Color::Red);
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
            if(b[i][k].type == BLANK){
                b[i][k].square.setFillColor(sf::Color::Green); //blank piece
            }
            else if(b[i][k].color != b[i][j].color){ //enemy piece
                b[i][k].square.setFillColor(sf::Color::Red);
                stop = true;
            }
            else{ //ally piece
                stop = true;
            }
        }
    }
}

void HighlightBishop(Piece b[8][8], int i, int j){
    int k, p;
    bool stop = false;
    if(i < 7){ //front
        if(j < 7){ //front-right
            for(k = i + 1, p = j + 1; k <= 7 && p <= 7 && !stop; k++, p++){
                if(b[k][p].type == BLANK){
                    b[k][p].square.setFillColor(sf::Color::Green); //blank piece
                }
                else if(b[k][p].color != b[i][j].color){ //enemy piece
                    b[k][p].square.setFillColor(sf::Color::Red);
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
                if(b[k][p].type == BLANK){
                    b[k][p].square.setFillColor(sf::Color::Green); //blank piece
                }
                else if(b[k][p].color != b[i][j].color){ //enemy piece
                    b[k][p].square.setFillColor(sf::Color::Red);
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
        if(j < 7){ //back-right
            for(k = i - 1, p = j + 1; k >= 0 && p <= 7 && !stop; k--, p++){
                if(b[k][p].type == BLANK){
                    b[k][p].square.setFillColor(sf::Color::Green); //blank piece
                }
                else if(b[k][p].color != b[i][j].color){ //enemy piece
                    b[k][p].square.setFillColor(sf::Color::Red);
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
                if(b[k][p].type == BLANK){
                    b[k][p].square.setFillColor(sf::Color::Green); //blank piece
                }
                else if(b[k][p].color != b[i][j].color){ //enemy piece
                    b[k][p].square.setFillColor(sf::Color::Red);
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

void Initialize_Texture(Piece pieces[8][8]){

    blanks.loadFromFile("images/blank.png");
    pawns.loadFromFile("images/pawn.png");
    bpawns.loadFromFile("images/bpawn.png");
    towers.loadFromFile("images/tower.png");
    btowers.loadFromFile("images/btower.png");
    knights.loadFromFile("images/knight.png");
    bknights.loadFromFile("images/bknight.png");
    bishops.loadFromFile("images/bishop.png");
    bbishops.loadFromFile("images/bbishop.png");
    queens.loadFromFile("images/queen.png");
    bqueens.loadFromFile("images/bqueen.png");
    kings.loadFromFile("images/king.png");
    bkings.loadFromFile("images/bking.png");

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            pieces[i][j].square.setFillColor(sf::Color::Transparent); //background color, set in the square that defines the position of the piece
            switch (pieces[i][j].type){ //Set the texture of the piece depending of its type and color
                case BLANK:
                    pieces[i][j].image.setTexture(blanks);
                break;
                case PAWN:
                    if(pieces[i][j].color){
                        pieces[i][j].image.setTexture(pawns);
                    }
                    else{
                        pieces[i][j].image.setTexture(bpawns);
                    }
                break;
                case TOWER:
                    if(pieces[i][j].color){
                        pieces[i][j].image.setTexture(towers);
                    }
                    else{
                        pieces[i][j].image.setTexture(btowers);
                    }
                break;
                case BISHOP:
                    if(pieces[i][j].color){
                        pieces[i][j].image.setTexture(bishops);
                    }
                    else{
                        pieces[i][j].image.setTexture(bbishops);
                    }
                break;
                case KNIGHT:
                    if(pieces[i][j].color){
                        pieces[i][j].image.setTexture(knights);
                    }
                    else{
                        pieces[i][j].image.setTexture(bknights);
                    }
                break;
                case QUEEN:
                    if(pieces[i][j].color){
                        pieces[i][j].image.setTexture(queens);
                    }
                    else{
                        pieces[i][j].image.setTexture(bqueens);
                    }
                break;
                case KING:
                    if(pieces[i][j].color){
                        pieces[i][j].image.setTexture(kings);
                    }
                    else{
                        pieces[i][j].image.setTexture(bkings);
                    }
                break;
            }
        }
    }

}

