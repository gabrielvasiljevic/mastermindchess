#include <SFML/Graphics.hpp>
#include "headers/pieceholder.h"

#include <iostream>
#include <string>
#include <fstream>

PieceHolder::PieceHolder(sf::RenderWindow &window) : mainWindow(window){
    int i;
    //textures.load_textures();
    posPawn = posKnight = posBishop = posRook = 0;
    posBPawn = posBKnight = posBBishop = posBRook = 0;
    for(i = 0; i < 10; i++){
        this->capt_pawns[i] = false;
        this->capt_bpawns[i] = false;
    }
    for(i = 0; i < 18; i++){
        this->capt_pieces[i] = false;
    }

    this->blank = new sf::Texture();
    this->pawn = new sf::Texture();
    this->bpawn = new sf::Texture();
    this->tower = new sf::Texture();
    this->btower = new sf::Texture();
    this->knight = new sf::Texture();
    this->bknight = new sf::Texture();
    this->bishop = new sf::Texture();
    this->bbishop = new sf::Texture();
    this->queen = new sf::Texture();
    this->bqueen = new sf::Texture();


    this->blank->loadFromFile("media/images/pieces/blank.png");
    this->pawn->loadFromFile("media/images/boxPawn.png");
    this->bpawn->loadFromFile("media/images/boxBlackPawn.png");
    this->tower->loadFromFile("media/images/boxRook.png");
    this->btower->loadFromFile("media/images/boxBlackRook.png");
    this->knight->loadFromFile("media/images/boxKnight.png");
    this->bknight->loadFromFile("media/images/boxBlackKnight.png");
    this->bishop->loadFromFile("media/images/boxBishop.png");
    this->bbishop->loadFromFile("media/images/boxBlackBishop.png");
    this->queen->loadFromFile("media/images/boxQueen.png");
    this->bqueen->loadFromFile("media/images/boxBlackQueen.png");


    for(i = 0; i < 10; i++){
        this->pawns[i].setTexture(*pawn);
        this->bpawns[i].setTexture(*bpawn);
    }
    //set the white pieces textures
    this->bishop1.setTexture(*bishop);
    this->bishop2.setTexture(*bishop);

    this->knight1.setTexture(*knight);
    this->knight2.setTexture(*knight);

    this->rook1.setTexture(*tower);
    this->rook2.setTexture(*tower);

    this->queen1.setTexture(*queen);

//    //set the black pieces textures

    this->bbishop1.setTexture(*bbishop);
    this->bbishop2.setTexture(*bbishop);

    this->bknight1.setTexture(*bknight);
    this->bknight2.setTexture(*bknight);

    this->brook1.setTexture(*btower);
    this->brook2.setTexture(*btower);

    this->bqueen1.setTexture(*bqueen);


    //set the pieces' position
    for(i = 0; i < 10; i++){
        if(i < 4){
            if(i < 2){
                this->pawns[i].setPosition(BOX_X + 17 + i*35, BOX_Y + 17);
                this->bpawns[i].setPosition(BOX_X + 20 + i*35, BOX_Y + 215);
            }

            else{
                this->pawns[i].setPosition(BOX_X + 40 + i*35, BOX_Y + 17);
                this->bpawns[i].setPosition(BOX_X + 40 + i*35, BOX_Y + 215);
            }

        }
        else
            if(i < 6){
                this->pawns[i].setPosition(BOX_X + 17 + (i - 4)*35, BOX_Y + 57);
                this->bpawns[i].setPosition(BOX_X + 20 + (i - 4)*35, BOX_Y + 255);
            }

            else{
                this->pawns[i].setPosition(BOX_X + 40 + (i - 4)*35, BOX_Y + 57);
                this->bpawns[i].setPosition(BOX_X + 40 + (i - 4)*35, BOX_Y + 255);
            }

    }
    this->knight1.setPosition(BOX_X + 17,        BOX_Y + 100);
    this->knight2.setPosition(BOX_X + 17 + 40,   BOX_Y + 100);
    this->bishop1.setPosition(BOX_X + 17 + 100,  BOX_Y + 100);
    this->bishop2.setPosition(BOX_X + 17 + 130,  BOX_Y + 100);
    this->rook1.setPosition(BOX_X + 20,          BOX_Y + 150);
    this->rook2.setPosition(BOX_X + 20 + 160,    BOX_Y + 180);
    this->queen1.setPosition(BOX_X + 17 + 67,    BOX_Y + 110);

    this->bknight1.setPosition(BOX_X + 17,        BOX_Y + 300);
    this->bknight2.setPosition(BOX_X + 17 + 40,   BOX_Y + 300);
    this->bbishop1.setPosition(BOX_X + 17 + 100,  BOX_Y + 300);
    this->bbishop2.setPosition(BOX_X + 17 + 130,  BOX_Y + 300);
    this->brook1.setPosition(BOX_X + 20,          BOX_Y + 350);
    this->brook2.setPosition(BOX_X + 20 + 160,    BOX_Y + 380);
    this->bqueen1.setPosition(BOX_X + 17 + 67,    BOX_Y + 310);

    this->rook2.setRotation(180);
    this->brook2.setRotation(180);

}

void PieceHolder::add(TYPE piece, int color){
    switch(piece){
        case PAWN:
            if (color)
                capt_pawns[posPawn++] = true;
            else
                capt_bpawns[posBPawn++] = true;
        break;
        case KNIGHT:
            if (color)
                capt_pieces[KNIGHT1 + posKnight++] = true;
            else
                capt_pieces[BKNIGHT1 + posBKnight++] = true;
        break;
        case BISHOP:
            if (color)
                capt_pieces[BISHOP1 + posBishop++] = true;
            else
                capt_pieces[BBISHOP1 + posBBishop++] = true;
        break;
        case TOWER:
            if (color)
                capt_pieces[ROOK1 + posRook++] = true;
            else
                capt_pieces[BROOK1 + posBRook++] = true;
        break;
        case QUEEN:
            if (color)
                capt_pieces[QUEEN1] = true;
            else
                capt_pieces[BQUEEN1] = true;
        break;
    }
}

void PieceHolder::reset(){
    int i;
    for(i = 0; i < 10; i++){
        capt_pawns[i] = false;
        capt_bpawns[i] = false;
    }
    for(i = 0; i < 18; i++){
        capt_pieces[i] = false;
    }
}

void PieceHolder::draw(){
    int i;
    for(i = 0; i < 10; i++){
        if(this->capt_pawns[i])
            mainWindow.draw(pawns[i]);
        if(this->capt_bpawns[i])
            mainWindow.draw(bpawns[i]);
    }
    if(this->capt_pieces[KNIGHT1])
        mainWindow.draw(knight1);
    if(this->capt_pieces[KNIGHT2])
        mainWindow.draw(knight2);
    if(this->capt_pieces[BISHOP1])
        mainWindow.draw(bishop1);
    if(this->capt_pieces[BISHOP2])
        mainWindow.draw(bishop2);
    if(this->capt_pieces[ROOK1])
        mainWindow.draw(rook1);
    if(this->capt_pieces[ROOK2])
        mainWindow.draw(rook2);
    if(this->capt_pieces[QUEEN1])
        mainWindow.draw(queen1);

    if(this->capt_pieces[BKNIGHT1])
        mainWindow.draw(bknight1);
    if(this->capt_pieces[BKNIGHT2])
        mainWindow.draw(bknight2);
    if(this->capt_pieces[BBISHOP1])
        mainWindow.draw(bbishop1);
    if(this->capt_pieces[BBISHOP2])
        mainWindow.draw(bbishop2);
    if(this->capt_pieces[BROOK1])
        mainWindow.draw(brook1);
    if(this->capt_pieces[BROOK2])
        mainWindow.draw(brook2);
    if(this->capt_pieces[BQUEEN1])
        mainWindow.draw(bqueen1);

}
