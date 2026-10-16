
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>  

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) { cout << "Run: ./oracle config-file\n"; return 1; }

    ifstream file(argv[1]);
    if (!file) { cout << "Cannot open file\n"; return 1; }

    vector<vector<int>> rows;
    string line;

    while (getline(file, line)) {
        while (line.size() > 0 &&
               (line[0] == ' ' || line[0] == '\t'))
            line.erase(0, 1);

        if (line == "" || line[0] == '#') continue;

        vector<int> row;
        int x;
        stringstream cutter(line);

        while (cutter >> x)
            row.push_back(x);

        if (row.size() > 0)
            rows.push_back(row);
    }

    int N = rows[0].size() + 1;
    cout << "Network has " << N << " nodes\n\n";

    int listener = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5000);

    inet_pton(AF_INET, "10.51.29.113", &addr.sin_addr);

    int one = 1;
    setsockopt(listener, SOL_SOCKET, SO_REUSEADDR,
               &one, sizeof(one));

    if (::bind(listener, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        return 1;
    }

    listen(listener, 10);

    cout << "\nWaiting for " << N
         << " nodes on port 5000...\n\n";

    for (int i = 0; i < N; i++) {
        int conn = accept(listener, nullptr, nullptr);

        cout << "  node " << char('A' + i)
             << " connected\n";

        close(conn);  
    }

    close(listener);
    return 0;
}
