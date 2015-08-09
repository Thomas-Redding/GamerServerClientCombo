//
//  NetworkServer.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/9/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef NetworkServer_cpp
#define NetworkServer_cpp

#include <stdio.h>
#include <iostream>
#include <SFML/Network.hpp>
#include "ServerCommunicator.hpp"

class ClientInfo {
public:
    sf::IpAddress ip;
    unsigned short udpPort = 0;
    sf::TcpSocket *tcp = nullptr;
};

class NetworkServer {
public:
    NetworkServer(ServerCommunicator &com);
    bool networkUpdate();
    void sendTcp(std::string message, sf::IpAddress ip);
    void sendUdp(std::string message, sf::IpAddress ipAddressOfClient);
    virtual bool receivedTcp(std::string message, sf::IpAddress ip) {};
    virtual bool receivedUdp(std::string message, sf::IpAddress ip) {};
    virtual void gotNewClient(sf::IpAddress ip) {};
    virtual void lostClient(sf::IpAddress ip) {};
    bool shouldServerContinue();
private:
    ServerCommunicator &communicator;
    std::vector<ClientInfo> clients;
    void checkForNewClients();
    bool isClientInUpdatedList(sf::TcpSocket *client, std::vector<sf::TcpSocket *>&list);
    bool isInClientList(sf::TcpSocket *ip);
    void sendTcpBySocket(std::string message, sf::TcpSocket *socket);
    sf::UdpSocket udpSocket;
    std::vector<std::string> split(const std::string s, char delim);
};

#endif /* NetworkServer_cpp */
