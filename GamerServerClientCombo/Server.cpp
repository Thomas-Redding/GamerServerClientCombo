//
//  Server.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "Server.hpp"

Server::Server(ServerCommunicator &com): NetworkServer(com) {
    // do stuff
}

bool Server::update() {
    // sleep for 100 milliseconds
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 100;
    tim.tv_nsec *= 1000000;
    nanosleep(&tim , &tim2);
    
    bool shouldContinue = shouldServerContinue();
    
    return shouldContinue;
}

bool Server::receivedTcp(std::string message) {
    if(message != "") {
        std::cout << "Server Received: " << message << "\n";
    }
    return true;
}

void Server::gotNewClient(sf::TcpSocket *socket) {
    std::cout << "New Client\n";
}

void Server::lostClient(sf::TcpSocket *socket) {
    std::cout << "Lost Client\n";
}