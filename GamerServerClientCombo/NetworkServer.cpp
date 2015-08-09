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
    std::string message = communicator.receiveTcpMessage();
    if(message == "") {
        return true;
    }
    else {
        return receivedTcp(message);
    }
}

void NetworkServer::sendTcp(std::string message, sf::TcpSocket *socket) {
    sf::Packet packet;
    packet << message;
    socket->send(packet);
}

bool NetworkServer::shouldServerContinue() {
    return communicator.getShouldServersContinue();
}
