#include "headers/networkHandler.h"
#include <iostream>

using namespace std;

bool NetworkHandler::connect (int port) {
    server.setBlocking (true);
    server.disconnect();

    string ip = "127.0.0.1";

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

bool NetworkHandler::receiveLoginResponse() {
    bool correct = false;
    packet >> correct;

    if (correct)
        myID = player_id;

    return correct;
}

bool NetworkHandler::receiveRegisterResponse() {
    bool correct = false;
    packet >> correct;

    return correct;
}


string NetworkHandler::receiveChat () {
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

void NetworkHandler::sendLogin(std::string name, std::string password) {
    buildHeader (packetID::Login);
    packet << name << password;
    server.send(packet);
}

void NetworkHandler::sendRegister(std::string name, std::string password) {
    buildHeader (packetID::Register);
    packet << name << password;
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
    cout << "[" << myID << "] Name sended\n";
}

void NetworkHandler::sendChat(std::string msg){
    buildHeader (packetID::Chat);
    packet << msg;
    server.send(packet);
    cout << "[" << myID << "] Chat message sended\n";
}

void NetworkHandler::sendMove(int i, int j, int iP, int jP){
    buildHeader (packetID::Move);
    packet << i << j << iP << jP;
    server.send(packet);
    cout << "[" << myID << "] movement sended\n";
}

void NetworkHandler::receiveMove(int* i, int* j, int* iP, int* jP){
    packet >> *i >> *j >> *iP >> *jP;
    cout << "Movement received from" << " [" << enemyID << "]" << endl;
    cout << "Moving piece from [" << *iP << "][" << *jP << "] to [" << *i << "][" << *j << "]." <<endl;

}

void NetworkHandler::sendGameEnd(){
    buildHeader (packetID::GameEnd);
    server.send(packet);
    cout << "[" << myID << "] GameEnd sended\n";
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
    cout << "Negative response sended to " << player_id << endl;
}

void NetworkHandler::sendGameRequest(){
    buildHeader(packetID::GameRequest);
    server.send(packet);
    cout << "Game request sended. Waiting answer..." << endl;
}

void NetworkHandler::handleEvents(){

}
