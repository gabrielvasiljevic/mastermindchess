#ifndef _DATA
#define _DATA

enum class STATE {Login, Lobby, Game, GameOver, Waiting};

enum class packetID {None, Name, Move, Connect, Login, LoginResponse, GameEnd, Disconnect, Register, RegisterResponse, Chat, GameRequest,
                    Response, Options, Turn, MatchLog, Check, Checkmate, KeepAlive};

enum class ButtonStyle {Dark };

#endif // _DATA
