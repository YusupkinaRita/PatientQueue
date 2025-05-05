#pragma once
#include "PatientController.h"
#include <winsock2.h>
#include <string>
#include "Patient.h"

class ConnectionHandlerServer {
private:
    SOCKET _listenSock;
    SOCKET _clientSock;
    PatientController _patController; 

public:
    ConnectionHandlerServer(PatientController controller);
    ~ConnectionHandlerServer();

    bool startServer(int port);
    void handleConnection();  
    void stopServer();
};



