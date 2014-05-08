#ifndef _NET
#define _NET


#include <string>
#include "dataTypes.h"
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;

class NetworkHandler{
    public:
        int player_id, enemyID, myID, packet_id;
        string myName, enemyName;
        Packet packet;
        TcpSocket server;

        bool connect (string ip, int port);
        bool receiveLoginResponse();
        bool receiveRegisterResponse();
        bool verifyVersion(string version);
        void receiveConnect();
        vector<userInfo> receivePlayerList();
        void receiveMove(int* i, int* j, int* iP, int* jP, bool* check);
        void receiveMoveLog(string& history);
        void buildHeader (packetID pid);
        void sendLogin(string name, string password, string version);
        void sendRegister(string usernameBuffer, string passwordBuffer, string nicknameBuffer, string emailBuffer);
        void sendConnect();
        void sendName(string myName);
        void sendChat(string msg);
        void sendMove(int i, int j, int iP, int jP, bool check);
        void sendGameEnd();
        void sendEnemyTimeout();
        void sendMyTimeout();
        void sendDisconnect();
        void sendNegative();
        void sendMoveLog(string moveLog);
        void sendCapaGameRequest();
        void sendGameRequest();
        void sendMoveHistory();
        void sendCheckMate();
        void handleEvents();
        string receiveChat ();
        string receiveName();
        packetID receive();

};
#endif // _NET
