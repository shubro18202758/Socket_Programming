
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 2) {
        cout << "Usage: ./vn ON_IP\n";
        return 1;
    }

    // Create TCP socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        perror("socket");
        return 1;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5000);

    if (inet_pton(AF_INET, argv[1], &addr.sin_addr) != 1) {
        cout << "Invalid IP address\n";
        return 1;
    }

    // Connect to Oracle Node
    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("connect");
        return 1;
    }

    cout << "Connected to Oracle Node successfully!\n";

    close(sock);

    return 0;
}
