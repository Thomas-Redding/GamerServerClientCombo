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
    udpSocket.setBlocking(false);
    udpSocket.bind(sf::Socket::AnyPort);
}

NetworkClient::~NetworkClient() {
    tcpSocket.disconnect();
}

void NetworkClient::applicationIsClosing() {
    sendOwnTcpServerMessageToQuit();
}

void NetworkClient::networkUpdate() {
    // update "connectionStage"
    if(connectionState == 1) {
        if(tcpSocket.getRemoteAddress() != sf::IpAddress::None) {
            // out TCP sockets just connected
            sendTcpMessage("_" + std::to_string(udpSocket.getLocalPort()));
            int oldState = connectionState;
            connectionState = 2;
            connectionStateChanged(oldState, 2);
            // now we wait for the server to send us a TCP message giving us its UDP port number
        }
    }
    else if(connectionState == 2) {
        if(tcpSocket.getRemoteAddress() == sf::IpAddress::None) {
            int oldState = connectionState;
            connectionState = -1;
            connectionStateChanged(oldState, -1);
        }
    }
    
    // check for TCP messages
    while(true) {
        sf::Packet packet;
        tcpSocket.receive(packet);
        std::string message = "";
        packet >> message;
        if(message != "") {
            if(message.at(0) == '_') {
                // message is reserved for NetworkClient (Client shouldn't receive this)
                udpPortOfServer = stoi(message.substr(1));
                if(connectionState != 3) {
                    int oldState = connectionState;
                    connectionState = 3;
                    connectionStateChanged(oldState, connectionState);
                }
            }
            else {
                tcpMessageReceived(message);
            }
        }
        else {
            break;
        }
    }
    
    // check for UDP messages
    while(true) {
        char buffer[1024];
        char *begin = buffer;
        char *end = begin + sizeof(buffer);
        std::fill(begin, end, 0);
        std::size_t received = 0;
        sf::IpAddress sender;
        unsigned short port;
        udpSocket.receive(buffer, sizeof(buffer), received, sender, port);
        std::string message = std::string(buffer);
        if(message != "") {
            udpMessageReceived(message);
        }
        else {
            break;
        }
    }

    return true;
}

void NetworkClient::attemptConnectionToServer(sf::IpAddress serverIpAddress, unsigned short serverPort) {
    ipAddressOfServer = serverIpAddress;
    if(connectionState != 0) {
        int oldState = connectionState;
        connectionState = 0;
        connectionStateChanged(oldState, 0);
    }
    else {
        connectionState = 0;
    }
    tcpSocket.setBlocking(false);
    sf::Socket::Status status = tcpSocket.connect(serverIpAddress, serverPort);
    connectionState = 1;
    connectionStateChanged(0, 1);
}

void NetworkClient::sendOwnTcpServerMessageToQuit() {
    unsigned short localTcpPort = getLocalServerTcpPort();
    if(sf::IpAddress::getLocalAddress() == tcpSocket.getRemoteAddress()) {
        sendTcpMessage("Quit Server");
    }
    else {
        // connect to local server
        tcpSocket.disconnect();
        sf::Time waitTime = sf::milliseconds(3000);
        tcpSocket.setBlocking(true);
        sf::Socket::Status status = tcpSocket.connect(sf::IpAddress::getLocalAddress(), getLocalServerTcpPort(), waitTime);
        tcpSocket.setBlocking(false);
        if(status == sf::Socket::Status::Done) {
            sendTcpMessage("Quit Server");
        }
        else {
            // try again
            tcpSocket.disconnect();
            sf::Time waitTime = sf::milliseconds(3000);
            tcpSocket.setBlocking(true);
            sf::Socket::Status status = tcpSocket.connect(sf::IpAddress::getLocalAddress(), getLocalServerTcpPort(), waitTime);
            tcpSocket.setBlocking(false);
            if(status == sf::Socket::Status::Done) {
                sendTcpMessage("Quit Server");
            }
            else {
                // give up and just try sending a message to whatever server we may be connected to
                sendTcpMessage("Quit Server");
            }
        }
    }
}

unsigned short NetworkClient::getLocalServerTcpPort() {
    return communicator.getLocalTcpPort();
}

int NetworkClient::getConnectionState() {
    return connectionState;
}

void NetworkClient::sendTcpMessage(std::string message) {
    sf::Packet packet;
    packet << message;
    tcpSocket.send(packet);
}

void NetworkClient::sendUdpMessage(std::string message) {
    udpSocket.send(message.c_str(), message.size(), ipAddressOfServer, udpPortOfServer);
}
