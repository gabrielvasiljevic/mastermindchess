#ifndef _DATA
#define _DATA

enum class STATE {Login, Lobby, Register, Game, GameOver, Waiting, CapaGame};

enum class packetID {None, Name, Move, Connect, Login, LoginResponse, GameEnd, Disconnect, Register, RegisterResponse, Chat, GameRequest,
                    Response, Options, Turn, MatchLog, Check, Checkmate, KeepAlive, MoveLog, WrongVersion, PlayerList, CapaGameRequest, CapaConnect, CapaOptions,
                    GameEndTimeOut};

enum class ButtonStyle {Dark, smallAdd, smallProfile, smallInvite, smallUp, smallDown, smallWatch};

enum class ChatStyle {GameChat, LobbyChat, PlayerChat};

enum class statusID {offline, online, playing};

struct userInfo{
    std::string nickname;
    statusID status;

    userInfo(std::string _nickname, statusID _status){
        nickname     = _nickname;
        status       = _status;
    }
    userInfo(){}
};

#endif // _DATA
