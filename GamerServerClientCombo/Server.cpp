//
//  Server.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "Server.hpp"

Server::Server(ServerCommunicator &com): NetworkServer(com) {
    unsigned numberOfCores = std::thread::hardware_concurrency();
    if(numberOfCores >= 2) {
        // the server and client will each get its own core
        // we don't have to wait much at all
    }
    else if(numberOfCores == 1) {
        // the server and client ahve to share a core
    }
    else {
        // unknown number of cores
    }
}

bool Server::update() {
    // sleep for 1100 milliseconds
    struct timespec tim, tim2;
    tim.tv_sec = 1;
    tim.tv_nsec = 100;
    tim.tv_nsec *= 1000000;
    nanosleep(&tim , &tim2);
    
    bool shouldContinue = shouldServerContinue();
    return shouldContinue;
}

bool Server::receivedTcp(std::string message, sf::IpAddress ip) {
    return true;
}

void Server::gotNewClient(sf::IpAddress ip) {
    clients.push_back(ip);
}

void Server::lostClient(sf::IpAddress ip) {
}

bool Server::receivedUdp(std::string message, sf::IpAddress ip) {
}
