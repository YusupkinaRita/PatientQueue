#pragma once

#include <winsock2.h>
#include <string>
#include "Patient.h"
#include "Doctor.h"

class ConnectionHandlerClient {
private:
    SOCKET _sock;
    Doctor _doc;  

public:
    ConnectionHandlerClient(const Doctor& doc);  
    ~ConnectionHandlerClient();

    bool connectToServer(const std::string& ip, int port);
    void handleSession();
    void disconnect();
};