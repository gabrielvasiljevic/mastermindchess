#include "headers/networkHandler.h"
#include <iostream>

using namespace std;



bool NetworkHandler::connect (string ip, int port) {
    server.setBlocking (true);
    server.disconnect();

    if (server.connect(ip, port, seconds(2)) == sf::Socket::Done) {
        cout << "Connected to server\n";
        server.setBlocking (false);
        return true;
    }
    server.setBlocking (false);
    return false;
}

packetID NetworkHandler::receive () {
    if (server.receive(packet) != Socket::Done)
        return packetID::None;

    packet >> player_id >> packet_id;

    cout << "Received packet: " << static_cast<int> (packet_id) << "\n";
    return static_cast<packetID> (packet_id);
}

void NetworkHandler::receiveConnect(){
    enemyID = player_id;
    cout << "Connection received, estabilished connection with " << enemyID << "...\n";
}

vector<userInfo> NetworkHandler::receivePlayerList(){
   int i, listSize;
   vector<userInfo> playerList;
   userInfo player;
   string nick;
   int status;
   packet >> listSize;
   for(i = 0; i < listSize; i++){
        packet >> player.nickname;
        packet >> status;
        player.status = static_cast<statusID>(status);
        playerList.emplace_back(player);
   }
   return playerList;
}

bool NetworkHandler::receiveLoginResponse() {
    bool correct = false;
    string name;
    packet >> correct >> name;

    if (correct){
        myID = player_id;
        myName = name;
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

void NetworkHandler::sendChat(std::string msg){
    buildHeader (packetID::Chat);
    packet << msg;
    server.send(packet);
    //cout << "[" << myID << "] Chat message sended\n";
}

void NetworkHandler::sendMove(int i, int j, int iP, int jP, bool check){
    buildHeader (packetID::Move);
    packet << i << j << iP << jP << check;
    server.send(packet);
   // cout << "[" << myID << "] movement sended\n";
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
    server.send(packet);
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

void NetworkHandler::sendGameEnd(){
    buildHeader (packetID::GameEnd);
    server.send(packet);
    cout << "[" << myID << "] GameEnd sended\n";
    enemyID = -1;
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

void NetworkHandler::sendGameRequest(){
    buildHeader(packetID::GameRequest);
    server.send(packet);
    cout << "Game request sended. Waiting answer..." << endl;
}

void NetworkHandler::sendCapaGameRequest(){
    buildHeader(packetID::CapaGameRequest);
    server.send(packet);
    cout << "Game request sended. Waiting answer..." << endl;
}

void NetworkHandler::handleEvents(){

}
