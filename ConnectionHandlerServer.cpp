#include "ConnectionHandlerServer.h"
#include <iostream>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

ConnectionHandlerServer::ConnectionHandlerServer(PatientController controller): _listenSock(INVALID_SOCKET), _clientSock(INVALID_SOCKET) {
    _patController=controller;
    
}

ConnectionHandlerServer::~ConnectionHandlerServer() {
    stopServer();
}



bool ConnectionHandlerServer::startServer(int port) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) return false;

    _listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_listenSock == INVALID_SOCKET) return false;

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(_listenSock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR){
        std::cerr << "Bind failed.\n";
        return false;
    }

    if (listen(_listenSock, SOMAXCONN) == SOCKET_ERROR){
        std::cerr << "Listen failed.\n";
        return false;
    }

    std::cout << "Server: Waiting for client...\n";
    _clientSock = accept(_listenSock, nullptr, nullptr);
    if (_clientSock == INVALID_SOCKET) {
        std::cerr << "Accept failed.\n";
        return false;
        }
    

    std::cout << "Server: Client connected.\n";
    return true;
}



void ConnectionHandlerServer::handleConnection() {
    char buffer[1024] = {0};
    int received = recv(_clientSock, buffer, sizeof(buffer), 0);
    if (received <= 0) return;

    std::string request(buffer, received);

    if (request == "NEXT PATIENT") {
        Patient p = _patController.Next(); 
        std::string data = p.ToString();
        send(_clientSock, data.c_str(), data.size(), 0);
    }

    // Получаем обновление пациента
    received = recv(_clientSock, buffer, sizeof(buffer), 0);
    if (received <= 0) return;

    request = std::string(buffer, received);
    if (request.rfind("UPDATE_PATIENT:", 0) == 0) {
        std::string data = request.substr(15);
        Patient updated = Patient::Deserialize(data);
        _patController.UpdatePatient(updated);  
    }
}

void ConnectionHandlerServer::stopServer() {
    if (_clientSock != INVALID_SOCKET) {
        closesocket(_clientSock);
        _clientSock = INVALID_SOCKET;
    }
    if (_listenSock != INVALID_SOCKET) {
        closesocket(_listenSock);
        _listenSock = INVALID_SOCKET;
    }
    WSACleanup();
}
