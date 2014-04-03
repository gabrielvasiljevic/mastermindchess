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

        Packet packet;
        TcpSocket server;

        bool connect (string ip, int port);
        bool receiveLoginResponse();
        bool receiveRegisterResponse();
        bool verifyVersion(string version);
        void receiveConnect();
        void receiveMove(int* i, int* j, int* iP, int* jP, bool* check);
        void buildHeader (packetID pid);
        void sendLogin(string name, string password);
        void sendRegister(string name, string password);
        void sendConnect();
        void sendName(string myName);
        void sendChat(string msg);
        void sendMove(int i, int j, int iP, int jP, bool check);
        void sendGameEnd();
        void sendDisconnect();
        void sendNegative();
        void sendGameRequest();
        void sendMoveHistory();
        void sendCheckMate();
        void handleEvents();
        string receiveChat ();
        string receiveName();
        packetID receive();

};
#endif // _NET
