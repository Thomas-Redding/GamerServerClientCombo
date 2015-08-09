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
    // sleep for 1100 milliseconds
    struct timespec tim, tim2;
    tim.tv_sec = 1;
    tim.tv_nsec = 100;
    tim.tv_nsec *= 1000000;
    nanosleep(&tim , &tim2);
    
    if(clients.size() > 0) {
        sendTcp("Server TCP", clients[0]);
        sendUdp("Server UDP", clients[0]);
    }
    
    bool shouldContinue = shouldServerContinue();
    return shouldContinue;
}

bool Server::receivedTcp(std::string message, sf::IpAddress ip) {
    std::cout << "Server TCP Rec: " << message << "\n";
    return true;
}

void Server::gotNewClient(sf::IpAddress ip) {
    clients.push_back(ip);
    std::cout << "New Client (" << ip.toString() << ")\n";
}

void Server::lostClient(sf::IpAddress ip) {
    std::cout << "Lost Client (" << ip.toString() << ")\n";
}

bool Server::receivedUdp(std::string message, sf::IpAddress ip) {
    std::cout << "Server UDP Rec: " << message << "\n";
}
