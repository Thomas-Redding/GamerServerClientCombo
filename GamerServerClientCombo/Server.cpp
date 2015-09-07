//
//  Server.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "Server.hpp"

Server::Server(ServerCommunicator &com): NetworkServer(com) {
}

bool Server::update() {
    // sleep for 30 milliseconds
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 300;
    tim.tv_nsec *= 1000000;
    nanosleep(&tim , &tim2);
    
    bool shouldContinue = shouldServerContinue();
    return shouldContinue;
}

bool Server::receivedTcp(std::string message, sf::IpAddress ip, long timeStamp) {
    return true;
}

void Server::gotNewClient(sf::IpAddress ip) {
    clients.push_back(ip);
}

void Server::lostClient(sf::IpAddress ip) {
}

bool Server::receivedUdp(std::string message, sf::IpAddress ip, long timeStamp) {
}
