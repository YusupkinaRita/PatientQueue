#include <iostream>
#include <thread>
#include <chrono>
#include "ConnectionHandlerClient.h"
#include "ConnectionHandlerServer.h"
#include "Doctor.h"
#include "PatientController.h"

void runServer() {
    PatientController controller;  // Пока что пустой
    ConnectionHandlerServer server(controller);
    server.startServer(8080);
}

void runClient() {
    // Немного подождать, чтобы сервер успел запуститься
    std::this_thread::sleep_for(std::chrono::seconds(1));

    Doctor doc;  // Пусть будет простой доктор
    ConnectionHandlerClient client(doc);

    if (client.connectToServer("127.0.0.1", 8080)) {
        client.handleSession();
        client.disconnect();
    } else {
        std::cerr << "Client: Failed to connect to server.\n";
    }
}

int main() {
    // Запускаем сервер в отдельном потоке
    std::thread serverThread(runServer);

    // Запускаем клиента в основном потоке
    runClient();

    // Ждём завершения сервера (если надо)
    serverThread.join();

    return 0;
}



