//
//  NetworkClient.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "NetworkClient.hpp"

NetworkClient::NetworkClient(ServerCommunicator& com) : communicator(com) {
    tcpSocket.setBlocking(false);
}

NetworkClient::~NetworkClient() {
    tcpSocket.disconnect();
}


int NetworkClient::update() {
    if(connectionStage == 1) {
        if(tcpSocket.getRemoteAddress() != sf::IpAddress::None) {
            std::cout << "[connected]";
            connectionStage = 2;
        }
    }
    else if(connectionStage == 2) {
        if(tcpSocket.getRemoteAddress() == sf::IpAddress::None) {
            connectionStage = -1;
        }
    }
    return 0;
}

void NetworkClient::attemptConnectionToServer(sf::IpAddress serverIpAddress, unsigned short serverPort, bool waitForCompletion) {
    tcpSocket.disconnect();
    sf::Time waitTime = sf::milliseconds(3000);
    if(waitForCompletion) {
        tcpSocket.setBlocking(true);
        sf::Socket::Status status = tcpSocket.connect(serverIpAddress, serverPort, waitTime);
        tcpSocket.setBlocking(false);
        if(status == sf::Socket::Status::Done) {
            connectionStage = 2;
        }
        else {
            connectionStage = -1;
        }
    }
    else {
        tcpSocket.setBlocking(false);
        sf::Socket::Status status = tcpSocket.connect(serverIpAddress, serverPort, waitTime);
        connectionStage = 1;
    }
}

void NetworkClient::sendOwnTcpServerMessageToQuit(unsigned short localTcpPort) {
    if(sf::IpAddress::getLocalAddress() == tcpSocket.getRemoteAddress()) {
        sendTcpMessage("Quit Server");
    }
    else {
        attemptConnectionToServer(sf::IpAddress::getLocalAddress(), localTcpPort, true);
        if(connectionStage == -1) {
            attemptConnectionToServer(sf::IpAddress::getLocalAddress(), localTcpPort, true);
        }
        sendTcpMessage("Quit Server");
    }
}

unsigned short NetworkClient::getLocalServerTcpPort() {
    return communicator.getLocalTcpPort();
}

int NetworkClient::getConnectionStage() {
    return connectionStage;
}

sf::IpAddress NetworkClient::getMyIpAddress() {
    return sf::IpAddress::getPublicAddress();
}

void NetworkClient::sendTcpMessage(std::string message) {
    std::cout << "Client Sent: " << message << "\n";
    sf::Packet packet;
    packet << message;
    tcpSocket.send(packet);
}
