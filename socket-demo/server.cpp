#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

int main() {

    int server = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in address{};
address.sin_family = AF_INET;
address.sin_port = htons(6000);
address.sin_addr.s_addr = INADDR_ANY;

if (::bind(server, (sockaddr*)&address, sizeof(address)) < 0) { 
    cout << "Bind failed!" << endl;
    return 1;
}

if (listen(server, 1) < 0) {
    cout << "Listen failed!" << endl;
    return 1;
}

cout << "Waiting for client..." << endl;

    int client = accept(server, nullptr, nullptr);

    cout << "Client connected!" << endl;

    char buffer[100] = {};

    recv(client, buffer, 100, 0);

    cout << "Client says: " << buffer << endl;

    send(client, "Hello Client!", 13, 0);

    close(client);
    close(server);
}
