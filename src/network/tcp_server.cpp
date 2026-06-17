#include "tcp_server.hpp"

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include <chrono>

bool TCPServer::start(int port)
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0)
    {
        std::cerr << "Failed to create socket\n";
        return false;
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd,
             reinterpret_cast<sockaddr*>(&address),
             sizeof(address)) < 0)
    {
        std::cerr << "Bind failed\n";
        close(server_fd);
        return false;
    }

    if (listen(server_fd, 5) < 0)
    {
        std::cerr << "Listen failed\n";
        close(server_fd);
        return false;
    }
    std::cout << "Server listening on port "
              << port
              << '\n';

    std::cout << "Waiting for a client...\n"; //deletar depois
    // loop infinito de accept assim servidor fica sempre rodando, esperando por conexões
    while (true)
    {
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);

        int client_socket =
            accept(server_fd,
                reinterpret_cast<sockaddr*>(&client_addr),
                &client_len);

        if (client_socket >= 0)
        {
            std::cout << "Creating thread..." << std::endl; // remover depois
            std::thread client_thread(&TCPServer::handleClient, this, client_socket);
            client_thread.detach();
        }
        else
        {
            std::cerr << "accept() failed\n";
        }
    }

    close(server_fd);

    return true;
}


void TCPServer::handleClient(int clientSocket)
{
    std::cout << "Thread ID: "
              << std::this_thread::get_id()
              << std::endl;

    char buffer[1024];

    ssize_t bytesReceived =
        recv(clientSocket, // Aguarda receber dados do cliente
             buffer,
             sizeof(buffer) - 1,
             0);

    if (bytesReceived > 0)
    {
        buffer[bytesReceived] = '\0';

        std::cout << "Received: "
                  << buffer
                  << std::endl;
    }

    close(clientSocket);
}
