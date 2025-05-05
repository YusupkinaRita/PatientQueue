#include "ConnectionHandlerClient.h"
#include <iostream>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

ConnectionHandlerClient::ConnectionHandlerClient(const Doctor& doc)
    : _sock(INVALID_SOCKET), _doc(doc) {}  

ConnectionHandlerClient::~ConnectionHandlerClient() {
    disconnect();
}


bool ConnectionHandlerClient::connectToServer(const std::string& ip, int port) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) return false;

    _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_sock == INVALID_SOCKET) return false;

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr);

    if (connect(_sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
        return false;

    std::cout << "Client: Connected to server.\n";
    return true;
}

void ConnectionHandlerClient::handleSession() { 
    std::string request = "NEXT PATIENT";
    send(_sock, request.c_str(), request.length(), 0);

    char buffer[2048] = {};
    int received = recv(_sock, buffer, sizeof(buffer), 0);
    if (received <= 0) {
        std::cerr << "Client: Failed to receive patient.\n";
        return;
    }

    std::string data(buffer, received);
    Patient p = Patient::Deserialize(data);

    
    _doc.SetPatient(p); 
    _doc.UpdatePatient();

    // Отправка обновлённого пациента
    std::string update = _doc.GetPatient().ToString();
    send(_sock, update.c_str(), update.length(), 0);

    std::cout << "Client: Sent updated patient.\n";
}

void ConnectionHandlerClient::disconnect() {
    if (_sock != INVALID_SOCKET) {
        closesocket(_sock);
        _sock = INVALID_SOCKET;
        WSACleanup();
    }
}