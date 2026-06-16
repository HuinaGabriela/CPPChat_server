#include "../network/tcp_server.hpp"

#include <iostream>

int main()
{
    std::cout << "CPPChat Server Starting...\n";

    TCPServer server;

    server.start(8080);

    return 0;
}