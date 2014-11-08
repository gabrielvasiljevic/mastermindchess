#include "headers/networkHandler.h"
#include <iostream>

using namespace std;

NetworkHandler& NetworkHandler::getNetwork(){
    static NetworkHandler instance;
    return instance;
}

sf::Packet& operator >>(sf::Packet& packet, char c){
    return packet >> c;
}

bool NetworkHandler::connect (string ip, int port) {
    server.setBlocking (true);
    server.disconnect();

   // if(not connected){
        cout << "Trying to connect..." << endl;
        if (server.connect(ip, port, seconds(2)) == sf::Socket::Done) {
            cout << "Connected to server\n";
            server.setBlocking (false);
            connected = 1;
            return true;
        }
  //  }
    connected = 0;
    server.setBlocking (false);
    return false;
}

packetID NetworkHandler::receive () {
    if (server.receive(packet) != Socket::Done)
        return packetID::None;

    packet >> player_id >> packet_id;
    enemyID = player_id;
    cout << "Received packet: " << static_cast<int> (packet_id) << "\n";
    return static_cast<packetID> (packet_id);
}


void NetworkHandler::receiveConnect(){
    enemyID = player_id;
    cout << "Connection received, estabilished connection with " << enemyID << "...\n";
}

void NetworkHandler::receiveOptions(int* color, int * mode, int* time, bool* ranked){
    packet >> *color >> *mode >> *time >> *ranked;
    cout << "Connection received, estabilished connection with " << enemyID << "...\n";
}

void NetworkHandler::receiveInvite(string& name, int& gameMode, int& gameTime, bool& isPublic){
    packet >> name >> gameMode >> gameTime >> isPublic;
}

vector<userInfo> NetworkHandler::receivePlayerList(){
   int i, listSize;
   vector<userInfo> playerList;
   userInfo player;
   string nick;
    int elo[3][3];
    int status;
   packet >> listSize;
   for(i = 0; i < listSize; i++){
        packet >> player.nickname;
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){
                packet >> player.elo[j][k]
                       >> player.victories[j][k]
                       >> player.defeats[j][k]
                       >> player.draws[j][k];
            }
        }
        packet >> status;
        player.status = static_cast<statusID>(status);
        playerList.emplace_back(player);
   }
   return playerList;
}

void NetworkHandler::receiveMatchList(std::vector<Match>& matchlist){ //The MatchList packet comes in the following way:
    int i, listSize;
    packet >> listSize; //number of matches
    matchlist.clear();
    for(i = 0; i < listSize; i++){
        matchlist.emplace_back();
        packet  >> matchlist[i].ID //ID of the match
                >> matchlist[i].white //White player's nickname
                >> matchlist[i].black //Black player's nickname
                >> matchlist[i].gameMode
                >> matchlist[i].gameTime
                >> matchlist[i].isPublic //if the match is public or private to watch
                >> matchlist[i].ranked //if its a ranked or a casual match
                >> matchlist[i].status; //Status of the match (i.e., ongoing or over)
    }
}

bool NetworkHandler::receiveLoginResponse() {
    bool correct = false;
    string name;
    int elo[3][3];
    packet >> correct >> name;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            packet >> elo[i][j];
        }
    }
    if (correct){
        myID = player_id;
        myName = name;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                myELO[i][j] = elo[i][j];
            }
        }
        myCurrentELO = myELO[0][0];
    }

    return correct;
}

bool NetworkHandler::receiveRegisterResponse() {
    bool correct = false;
    packet >> correct;

    return correct;
}


string NetworkHandler::receiveChat(){
    std::string msg;
    packet >> msg;
    return msg;
}

std::string NetworkHandler::receiveName() {
    std::string eName;
    packet >> eName;
    return eName;
}

int NetworkHandler::receiveElo() {
    int elo;
    packet >> elo;
    return elo;
}



void NetworkHandler::buildHeader (packetID pid) {
    packet.clear();
    packet << enemyID;
    packet << static_cast<int> (pid);
}

void NetworkHandler::sendLogin(std::string name, std::string password, std::string version) {
    buildHeader (packetID::Login);
    packet << name << password << version;
    server.send(packet);
}

void NetworkHandler::sendRegister(string usernameBuffer, string passwordBuffer, string nicknameBuffer, string emailBuffer) {
    buildHeader (packetID::Register);
    packet << usernameBuffer << passwordBuffer << nicknameBuffer << emailBuffer;
    server.send(packet);
}

void NetworkHandler::sendConnect () {
    buildHeader (packetID::Connect);
    enemyID = player_id; //gab
    server.send(packet);
    cout << "[" << myID << "] Estabilishing connection to " << enemyID << "...\n";
}

void NetworkHandler::sendName (string myName) {
    buildHeader (packetID::Name);
    packet << myName;
    server.send(packet);
   // cout << "[" << myID << "] Name sended\n";
}

void NetworkHandler::sendChat(std::string msg, bool spectator){
    if(spectator)
        buildHeader (packetID::SpectatorChat);
    else
        buildHeader (packetID::Chat);
    packet << msg;
    server.send(packet);
    //cout << "[" << myID << "] Chat message sended\n";
}


void NetworkHandler::sendMove(int i, int j, int iP, int jP, bool check, string boardStatus[8][10]){
    buildHeader (packetID::Move);
    int k, p;
    packet << i << j << iP << jP << check;
    for(k = 0; k < 8; k++){
        for(p = 0; p < 10; p++){
            packet << boardStatus[k][p];
        }
    }
    server.send(packet);
   // cout << "[" << myID << "] movement sended\n";
}

void NetworkHandler::sendBoardStatus(string boardStatus[8][10]){
    buildHeader (packetID::BoardStatus);
    int k, p;
    for(k = 0; k < 8; k++){
        for(p = 0; p < 10; p++){
            packet << boardStatus[k][p];
        }
    }
    server.send(packet);
}

void NetworkHandler::sendCheckMate(){
   buildHeader (packetID::Checkmate);
   server.send(packet);
   cout << "Checkmate sended" << endl;
   enemyID = -1;
}

void NetworkHandler::receiveMove(int* i, int* j, int* iP, int* jP, bool* check){
    packet >> *i >> *j >> *iP >> *jP >> *check;
    cout << "Movement received from" << " [" << enemyID << "]" << endl;
    cout << "Moving piece from [" << *iP << "][" << *jP << "] to [" << *i << "][" << *j << "]." << endl;
    if(*check == true){
        cout << "Check!" << endl;
    }
}

void NetworkHandler::sendMyTimeout(){
    buildHeader(packetID::GameEndTimeOut);
    packet << myID;
    //server.send(packet);
}

void NetworkHandler::sendEnemyTimeout(){
    buildHeader(packetID::GameEndTimeOut);
    packet << enemyID;
    server.send(packet);
}

void NetworkHandler::receiveMoveLog(string& history){
    string log;
    packet >> log;
    history += log;
}

void NetworkHandler::sendMoveLog(string moveLog){
    buildHeader (packetID::MoveLog);
    packet << moveLog;
    server.send(packet);
}

void NetworkHandler::sendMatchHistory(string history){
    buildHeader (packetID::MatchHistory);
    packet << history;
    server.send(packet);
}

void NetworkHandler::sendGameEnd(){
    buildHeader (packetID::GameEnd);
    server.send(packet);
    cout << "[" << myID << "] GameEnd sended\n";
    enemyID = -1;
}

void NetworkHandler::sendGiveUp(){
    buildHeader (packetID::GiveUp);
    server.send(packet);
    cout << "[" << myID << "] GiveUp sended\n";
    enemyID = -1;
}

void NetworkHandler::sendExitQueue(){
    buildHeader(packetID::ExitQueue);
    server.send(packet);
}

void NetworkHandler::sendDisconnect(){
    buildHeader (packetID::Disconnect);
    server.send(packet);
    cout << "[" << myID << "] Disconnect sended\n";
}

void NetworkHandler::sendNegative(){
    buildHeader(packetID::Response);
    packet << false;
    server.send(packet);
    //cout << "Negative response sended to " << player_id << endl;
}

void NetworkHandler::sendFischerPiecesOrder(string board[8][10]){
    buildHeader(packetID::FischerPieceOrder);

    int k, p;
    for(k = 0; k < 8; k++){
        for(p = 0; p < 10; p++){
            packet << board[k][p];
        }
    }
    server.send(packet);

}

void NetworkHandler::sendMatchInvite(string name, int gameMode, int gameTime, bool isPublic){
    if(name != myName){
        buildHeader(packetID::GameInvite);
        packet << name << gameMode << gameTime << isPublic;
        server.send(packet);
        cout << "Invite sended!" << endl;
    }

}

void NetworkHandler::sendInviteConfirmation(string name, int gameMode, int gameTime, bool isPublic){
    buildHeader(packetID::InviteResponse);
    packet << name << true << gameMode << gameTime << isPublic;
    server.send(packet);
    cout << "Invite confirmation sended!" << endl;
}


void NetworkHandler::sendInviteRejection(string name){
    buildHeader(packetID::InviteResponse);
    packet << name << false;
    server.send(packet);
    cout << "Invite rejection sended!" << endl;
}


void NetworkHandler::sendGameRequest(int gameMode, int gameTime){
    buildHeader(packetID::GameRequest);
    packet << gameMode << gameTime;
    server.send(packet);
    cout << "Game request sended. Waiting answer..." << endl;
}

void NetworkHandler::sendWatchGameRequest(int matchID){
    buildHeader(packetID::WatchRequest);
    packet << matchID;
    server.send(packet);
    cout << "Watch request sended." <<endl;
}


void NetworkHandler::receiveMatchStatus(string* white, string* black, int* whiteElo, int* blackElo, string newBoard[][10], int* gameMode){
    int i, j;
    packet >> *white >> *black >> *whiteElo >> *blackElo;
    for(i = 0; i < 8; i++){
        for(j = 0; j < 10; j++){
            packet >> newBoard[i][j];
        }
    }
    packet >> *gameMode;
}

void NetworkHandler::receiveFischerPiecesOrder(string newBoard[][10]){
    int i, j;
    for(i = 0; i < 8; i++){
        for(j = 0; j < 10; j++){
            packet >> newBoard[i][j];
        }
    }
}

int NetworkHandler::receiveNumberWatching(){
    int number;
    packet >> number;
    return number;
}

void NetworkHandler::receiveRejectedInvite(string* user){
    packet >> *user;
}

void NetworkHandler::handleEvents(){

}
