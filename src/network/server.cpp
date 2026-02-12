#include "server.hpp"
#include "../protocol/parser.hpp"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdint>
#include <stdexcept>
#include <iostream>
#include <vector>

Server::Server(int port, int backlog) 
    : port_(port), backlog_(backlog) {}

Server::~Server() {
    if(server_fd_ > -1){
        close(server_fd_);
    }
}

void Server::Start(){
    SetupSocket();
    AcceptClient();
}

void Server::SetupSocket(){
    server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd_ < 0){
        throw std::runtime_error("Failed to create socket");
    }

    int reuse = 1;
    if(setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        throw std::runtime_error("setsockopt failed!");
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_);

    if(bind(server_fd_, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) < 0) {
        throw std::runtime_error("bind failed!");
    }

    if(listen(server_fd_, backlog_) < 0){
        throw std::runtime_error("listen failed!");
    }

    std::cout << "Server is up and running!" << std::endl;
}

void Server::AcceptClient(){
    sockaddr_in client_addr{};
    socklen_t client_addr_len = sizeof(client_addr);

    int client_fd = accept(server_fd_, reinterpret_cast<sockaddr*>(&client_addr), &client_addr_len);

    if (client_fd < 0){
        throw std::runtime_error("Accept failed!");
    }

    std::cout << "Client connected!" << std::endl;

    HandleClient(client_fd);
}

void Server::HandleClient(int client_fd){
    std::vector<uint8_t> buffer(1024);
    while(true){
        ssize_t bytes_received = recv(client_fd, buffer.data(), buffer.size(), 0);
        if(bytes_received < 0){
            throw std::runtime_error("Client disconnected or error");
        }

        buffer.resize(bytes_received);

        Parser parser;
        Header header = parser.ParseHeader(buffer);

        std::cout << "Message size: " << header.msg_size << std::endl;
        std::cout << "Request API key: " << header.request_api_key << std::endl;
        std::cout << "Request API Version: " << header.request_api_version << std::endl;
        std::cout << "Correlation ID: " << header.correlation_id << std::endl;
    }
}