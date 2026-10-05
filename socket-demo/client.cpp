#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

int main() {

    int client = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_port = htons(6000);

    inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);

    cout << "Connecting to server..." << endl;

    connect(client, (sockaddr*)&address, sizeof(address));

    cout << "Connected!" << endl;

    send(client, "Hello Server!", 13, 0);

    char buffer[100] = {};

    recv(client, buffer, 100, 0);

    cout << "Server says: " << buffer << endl;

    close(client);
}