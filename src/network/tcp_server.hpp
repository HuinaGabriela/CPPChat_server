#pragma once

class TCPServer
{
public:
    bool start(int port);

private:
    void handleClient(int client_socket);
};