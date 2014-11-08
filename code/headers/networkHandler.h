#ifndef _NET
#define _NET

#ifndef network
#define network NetworkHandler::getNetwork()
#endif

#include <string>
#include "dataTypes.h"
#include "match.h"
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;


class NetworkHandler{
    private:
        //Singleton
        static NetworkHandler* instance;
        NetworkHandler(){connected = 0;};
        NetworkHandler(NetworkHandler const&);
        void operator=(NetworkHandler const&);

    public:
        static NetworkHandler& getNetwork();
        int player_id, enemyID, myID, packet_id;
        int myELO[3][3];
        int myCurrentELO;
        int connected;
        string myName, enemyName;
        Packet packet;
        TcpSocket server;

        bool connect (string ip, int port);
        bool receiveLoginResponse();
        bool receiveRegisterResponse();
        bool verifyVersion(string version);
        void receiveConnect();
        vector<userInfo> receivePlayerList();
        void receiveMatchList(vector<Match>& matchlist);
        void receiveMove(int* i, int* j, int* iP, int* jP, bool* check);
        void receiveMoveLog(string& history);
        void receiveOptions(int* color, int* mode, int* time, bool* ranked);
        void receiveMatchStatus(string* white, string* black, int* whiteElo, int* blackElo, string newBoard[][10], int* gameMode);
        void receiveFischerPiecesOrder(string newBoard[][10]);
        void receiveInvite(string& name, int& gameMode, int& gameTime, bool& isPublic);
        void receiveRejectedInvite(string* user);
        int receiveNumberWatching();

        string receiveChat();
        string receiveName();
        int receiveElo();

        void buildHeader (packetID pid);

        void sendLogin(string name, string password, string version);
        void sendRegister(string usernameBuffer, string passwordBuffer, string nicknameBuffer, string emailBuffer);
        void sendConnect();
        void sendName(string myName);
        void sendChat(string msg, bool spectator);
        void sendMove(int i, int j, int iP, int jP, bool check, string boardStatus[8][10]);
        void sendGameEnd();
        void sendGiveUp();
        void sendExitQueue();
        void sendEnemyTimeout();
        void sendMyTimeout();
        void sendDisconnect();
        void sendNegative();
        void sendMatchInvite(string name, int gameMode, int gameTime, bool isPublic);
        void sendInviteConfirmation(string name, int gameMode, int gameTime, bool isPublic);
        void sendInviteRejection(string name);
        void sendMoveLog(string moveLog);
        void sendMatchHistory(string history);
        void sendRandomGameRequest();
        void sendCapaGameRequest();
        void sendGameRequest(int gameMode, int gameTime);
        void sendWatchGameRequest(int matchID);
        void sendMoveHistory();
        void sendBoardStatus(string boardStatus[8][10]);
        void sendFischerPiecesOrder(string boardStatus[8][10]);
        void sendCheckMate();
        void handleEvents();

        packetID receive();

};



#endif // _NET
