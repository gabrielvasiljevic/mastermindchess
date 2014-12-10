#ifndef _DATA
#define _DATA

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "textures.h"

#define BOARD_X 105//250 //position of the board
#define BOARD_Y 90//100

#define CBOARD_X 195 //position of the board
#define CBOARD_Y 90

#define TOPPLAYER_X 9
#define TOPPLAYER_Y 3

#define BOTPLAYER_X 9
#define BOTPLAYER_Y 629

#define BOX_X 730
#define BOX_Y 20

#define PAPER_X 755
#define PAPER_Y 445

#define INVITE_X 350
#define INVITE_Y 250

enum class STATE {Login, Lobby, Register, Game, GameOver, Waiting, CapaGame, RandGame, Watching};

enum class packetID {None, Name, Move, Connect, Login, LoginResponse, GameEnd, Disconnect, Register, RegisterResponse, Chat, GameRequest,
                    Response, Options, Elo, MatchLog, Check, Checkmate, KeepAlive, MoveLog, WrongVersion, PlayerList, GameEndTimeOut, GiveUp,
                    MatchList, WatchRequest, WatchState, ExitQueue, BoardStatus, GameInvite, InviteResponse, FischerPieceOrder, SpectatorChat,
                    MatchHistory, numberWatching, InviteRejection, AlreadyConnected,
                    GesturalMovement = 255};

enum class ButtonStyle {TextAndImage, NoText, NoImage, Null};

enum class ChatStyle {GameChat, LobbyChat, SpectateChat, Null};

enum class statusID {offline = 0, online, playing, watching};

enum class gameType {Classic = 0, Fischer, Capa };

//A piece can be a regular chess piece, or a blank square
enum TYPE {BLANK, PAWN, KNIGHT, BISHOP, TOWER, QUEEN, KING, ARCHBISHOP, CHANCELER};

const std::string VERSION = "0.1.9";

struct userInfo{
    std::string nickname;
    std::string currentVLD;
    bool hasPrize[3][3];
    int currentElo;
    int elo[3][3];
    int victories[3][3];
    int defeats[3][3];
    int draws[3][3];
    statusID status;

    userInfo(std::string _nickname, int _elo, statusID _status){
        nickname     = _nickname;
        currentElo   = _elo;
        status       = _status;
    }

    bool hasElo(int gameMode, int gameTime){
        if(victories[gameMode][gameTime/900] + defeats[gameMode][gameTime/900] + draws[gameMode][gameTime/900] >= 10) return true;
        else return false;
    }
    userInfo(){nickname = "";}
};

inline std::string toClock(double time){
    std::string clock = "";
    clock = clock + ((time/60 < 10) ? "0" : "") + std::to_string(static_cast<int>(time/60)) + ":";
    time = static_cast<int>(time)%60;
    clock += ((time < 10) ? "0" : "") + std::to_string(static_cast<int>(time));
    return clock;
}


#endif // _DATA
