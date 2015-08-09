//
//  NetworkServer.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/9/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "NetworkServer.hpp"

NetworkServer::NetworkServer(ServerCommunicator &com): communicator(com) {
    // do stuff
}

bool NetworkServer::networkUpdate() {
    bool shouldContinue = true;
    
    // call the receivedTcp() event in Server
    // note, we will only read the first 100 messages
    for(int i=0; i<100; i++) {
        std::string message = communicator.receiveTcpMessage();
        if(message == "") {
            break;
        }
        else {
            shouldContinue = shouldContinue && receivedTcp(message);
            if(!shouldContinue) {
                return shouldContinue;
            }
        }
    }
    
    checkForNewClients();
    
    return shouldContinue;
}

void NetworkServer::sendTcp(std::string message, sf::TcpSocket *socket) {
    sf::Packet packet;
    packet << message;
    socket->send(packet);
}

bool NetworkServer::shouldServerContinue() {
    return communicator.getShouldServersContinue();
}

void NetworkServer::checkForNewClients() {
    std::vector<sf::TcpSocket *> updatedClients = communicator.getClients();
    std::vector<sf::TcpSocket *> newClients;
    std::vector<sf::TcpSocket *> lostClients;
    for(int i=0; i<updatedClients.size(); i++) {
        if(!isClientInList(updatedClients[i], clients)) {
            newClients.push_back(updatedClients[i]);
        }
    }
    for(int i=0; i<clients.size(); i++) {
        if(!isClientInList(clients[i], updatedClients)) {
            lostClients.push_back(clients[i]);
        }
    }
    clients = updatedClients;
    for(int i=0; i<newClients.size(); i++) {
        gotNewClient(newClients[i]);
    }
    for(int i=0; i<lostClients.size(); i++) {
        lostClient(lostClients[i]);
    }
}

bool NetworkServer::isClientInList(sf::TcpSocket *client, std::vector<sf::TcpSocket *>&list) {
    for(int i=0; i<list.size(); i++) {
        if(client == list[i]) {
            return true;
        }
    }
    return false;
}










