#pragma once

class Server{
public:
    explicit Server(int port, int backlog);
    ~Server();

    void Start();
private:
    int server_fd_{-1};
    int port_;
    int backlog_;

    void SetupSocket();
    void AcceptClient();
};