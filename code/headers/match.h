#ifndef _MATCH
#define _MATCH
#include "dataTypes.h"

#include <SFML/Network.hpp>
#include <SFML/System.hpp>

struct Match{
    std::string white, black;
    double whiteTime, blackTime;
    int ranked, isPublic;
    int gameTime, gameMode;
    int ID;
    int status;
    int numberWatching;
    std::string board[8][10];
    std::string match_history;

};

#endif // _MATCH
