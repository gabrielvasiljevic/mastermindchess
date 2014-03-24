#include <SFML/Graphics.hpp>
#include "headers/game.h"
#include <iostream>

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
    sf::Texture Tabuleiro;
    sf::Sprite board;

    bool pieceClick = false;

Game::Game(sf::RenderWindow &window) : b(BOARD_X, BOARD_Y), Hint(750, 100, 15, 15, "Hint"), mainWindow(window){
    this->texture = new sf::Texture();
    this->texture->loadFromFile("media/images/board.jpg");
    this->board.setTexture(*this->texture);
    this->board.setPosition(BOARD_X, BOARD_Y);
    this->turn = 1;
    this->myColor = 1;
}

void Game::draw(){
    mainWindow.draw(board);
    mainWindow.draw(Hint.image);
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            mainWindow.draw(b.pieces[i][j].square ); //Draw the background first
            mainWindow.draw(b.pieces[i][j].image ); //Then the piece itself
            if(b.pieces[i][j].highlighted){
                mainWindow.draw(b.pieces[i][j].border);
            }
        }
    }
    mainWindow.draw(Hint.text);
}

int Game::Run(){
    /*Pieces' texture initialization*/
    Initialize_Texture(b.pieces);

    /*Load board image and texture*/
   // if(!Tabuleiro.loadFromFile("media/images/board.jpg")) return 1;
   // board.setTexture(Tabuleiro);

    draw();
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

void Game::Initialize_Texture(Piece pieces[8][8]){

    blanks.loadFromFile("media/images/blank.png");
    pawns.loadFromFile("media/images/pawn.png");
    bpawns.loadFromFile("media/images/bpawn.png");
    towers.loadFromFile("media/images/tower.png");
    btowers.loadFromFile("media/images/btower.png");
    knights.loadFromFile("media/images/knight.png");
    bknights.loadFromFile("media/images/bknight.png");
    bishops.loadFromFile("media/images/bishop.png");
    bbishops.loadFromFile("media/images/bbishop.png");
    queens.loadFromFile("media/images/queen.png");
    bqueens.loadFromFile("media/images/bqueen.png");
    kings.loadFromFile("media/images/king.png");
    bkings.loadFromFile("media/images/bking.png");

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


bool Game::HandleInput(int x, int y){
    cout << x << " " << y << " " << turn << endl;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(b.pieces[i][j].rectSquare.contains(x, y)){ //If the click was in a square...
                cout << i << " " << j << (turn? " White turn" : " Black turn") << endl;
                cout << "I am " << (myColor? " White " : " Black ") << endl;
                if(myColor == turn){
                    if(b.pieces[i][j].color == myColor){ //I clicked one of my pieces.
                        if(!pieceClick){ //I have not clicked in one of my pieces yet.
                            pieceClick = true;
                            iPiece = i;
                            jPiece = j;
                            b.pieces[i][j].clicked? b.pieces[i][j].square.setFillColor(sf::Color::Transparent) : //If the piece was already clicked once, turn it back to transparent
                                                    b.pieces[i][j].square.setFillColor(sf::Color::Yellow); //If not, highlight it in yellow
                            b.pieces[i][j].clicked = !b.pieces[i][j].clicked;
                            if(Hint.checked) b.Highlight(b.pieces[i][j].type, i, j);
                        }
                        else if(pieceClick && i == iPiece && j == jPiece){ //Clicking again in the same piece
                            Unhighlight(b.pieces);
                            pieceClick = false;
                        }
                    }//I have already clicked on a piece, and now I am clicking on an enemy's piece.
                    else if(pieceClick && b.pieces[i][j].color == !myColor){
                        if(b.pieces[i][j].capture(b.pieces, i, j, iPiece, jPiece)){ //Capture the piece, if possible
                            Initialize_Texture(b.pieces);
                            Unhighlight(b.pieces);
                            pieceClick = false;
                            turn = !turn;
                            this->i = i;
                            this->j = j;
                            return true;
                        }
                    }//I have already clicked on a piece, and now I am clicking on an empty square.
                    else if(pieceClick && b.pieces[i][j].type == BLANK ){
                        //Execute a movement, if possible
                        if(b.pieces[i][j].movement(b.pieces, i, j, iPiece, jPiece)){
                            turn = !turn;
                            Initialize_Texture(b.pieces);
                            Unhighlight(b.pieces);
                            pieceClick = false;
                            this->i = i;
                            this->j = j;
                            return true;
                        }
                    }
                }
                return false;
            }
        }
    }
    if(Hint.clicked(x, y)){
        Hint.action();
    }
}
