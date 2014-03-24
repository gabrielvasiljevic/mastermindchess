#include <string>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
enum class packetID {None, Name, Move, Connect, Login, LoginResponse, GameEnd, Disconnect, Register, RegisterResponse, Chat, GameRequest, Response, Options, Turn};

using namespace std;
using namespace sf;

class NetworkHandler{
    public:
        int player_id, enemyID, myID, packet_id;

        Packet packet;
        TcpSocket server;

        bool connect (int port);
        bool receiveLoginResponse();
        bool receiveRegisterResponse();
        void receiveConnect();
        void receiveMove(int* i, int* j, int* iP, int* jP);
        void buildHeader (packetID pid);
        void sendLogin(string name, string password);
        void sendRegister(string name, string password);
        void sendConnect();
        void sendName(string myName);
        void sendChat(string msg);
        void sendMove(int i, int j, int iP, int jP);
        void sendGameEnd();
        void sendDisconnect();
        void sendNegative();
        void sendGameRequest();
        void handleEvents();
        string receiveChat ();
        string receiveName();
        packetID receive();

};
