//
//  NetworkServer.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/9/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "NetworkServer.hpp"

NetworkServer::NetworkServer(ServerCommunicator &com): communicator(com) {
    udpSocket.bind(sf::Socket::AnyPort);
    udpSocket.setBlocking(false);
}

bool NetworkServer::networkUpdate() {
    bool shouldContinue = true;
    
    checkForNewClients();
    
    // check for TCP messages
    while(true) {
        std::string message = communicator.receiveTcpMessage();
        if(message == "") {
            break;
        }
        else {
            if(message.at(0) == '_') {
                message = message.substr(1);
                std::vector<std::string> arr = split(message, '\n');
                std::string ip = arr[0];
                unsigned short newUdpPort = stoi(arr[1]);
                for(int i=0; i<clients.size(); i++) {
                    if(clients[i].ip.toString() == ip) {
                        clients[i].udpPort = newUdpPort;
                    }
                }
            }
            else {
                for(int i=0; i<message.size(); i++) {
                    if(message.at(i) == '\n') {
                        shouldContinue = shouldContinue && receivedTcp(message.substr(i+1), sf::IpAddress(message.substr(0, i)));
                        break;
                    }
                }
                if(!shouldContinue) {
                    return shouldContinue;
                }
            }
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
            receivedUdp(message, sender);
        }
        else {
            break;
        }
    }
    
    return shouldContinue;
}

bool NetworkServer::shouldServerContinue() {
    return communicator.getShouldServersContinue();
}

void NetworkServer::checkForNewClients() {
    std::vector<sf::TcpSocket *> updatedClients = communicator.getClients();
    std::vector<sf::TcpSocket *> newClients;
    std::vector<sf::TcpSocket *> lostClients;
    for(int i=0; i<updatedClients.size(); i++) {
        if(!isInClientList(updatedClients[i])) {
            newClients.push_back(updatedClients[i]);
        }
    }
    for(int i=0; i<clients.size(); i++) {
        if(!isClientInUpdatedList(clients[i].tcp, updatedClients)) {
            lostClients.push_back(clients[i].tcp);
        }
    }
    
    for(int i=0; i<newClients.size(); i++) {
        clients.push_back(ClientInfo());
        clients[clients.size()-1].tcp = newClients[i];
        clients[clients.size()-1].ip = newClients[i]->getRemoteAddress();
        sendTcpBySocket("_"+std::to_string(udpSocket.getLocalPort()), clients[clients.size()-1].tcp);
    }
    
    for(int i=0; i<newClients.size(); i++) {
        gotNewClient(newClients[i]->getRemoteAddress());
    }
    for(int i=0; i<lostClients.size(); i++) {
        lostClient(lostClients[i]->getRemoteAddress());
    }
}

bool NetworkServer::isClientInUpdatedList(sf::TcpSocket *client, std::vector<sf::TcpSocket *>&list) {
    for(int i=0; i<list.size(); i++) {
        if(client == list[i]) {
            return true;
        }
    }
    return false;
}

bool NetworkServer::isInClientList(sf::TcpSocket *ip) {
    for(int i=0; i<clients.size(); i++) {
        if(clients[i].tcp == ip) {
            return true;
        }
    }
    return false;
}

void NetworkServer::sendUdp(std::string message, sf::IpAddress ipAddressOfClient) {
    for(int i=0; i<clients.size(); i++) {
        if(clients[i].ip == ipAddressOfClient) {
            udpSocket.send(message.c_str(), message.size(), ipAddressOfClient, clients[i].udpPort);
            break;
        }
    }
}

void NetworkServer::sendTcp(std::string message, sf::IpAddress ip) {
    for(int i=0; i<clients.size(); i++) {
        if(clients[i].ip == ip) {
            sendTcpBySocket(message, clients[i].tcp);
            break;
        }
    }
}

void NetworkServer::sendTcpBySocket(std::string message, sf::TcpSocket *socket) {
    sf::Packet packet;
    packet << message;
    socket->send(packet);
}

std::vector<std::string> NetworkServer::split(const std::string s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    if(s[s.length()-1] == delim) {
        elems.push_back("");
    }
    return elems;
}
