#include "server.hpp"

#include <iostream>

int main(){
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    Server server{9092, 5};

    server.Start();

    return 0;
}