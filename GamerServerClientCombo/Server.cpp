//
//  Server.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "Server.hpp"

Server::Server(ServerCommunicator &com): communicator(com) {
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
    
    std::string tcpMessage = readTcp();
    
    std::cout << "s";
    
    std::cout << tcpMessage;
    
    return shouldContinue;
}

void Server::sendTcp(std::string message, sf::TcpSocket *socket) {
    sf::Packet packet;
    packet << message;
    socket->send(packet);
}

std::string Server::readTcp() {
    return communicator.receiveTcpMessage();
}

bool Server::shouldServerContinue() {
    return communicator.getShouldServersContinue();
}
