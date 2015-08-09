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
    
    // return a boolean indicating whether the server should keep running
    bool networkUpdate();
    void sendTcp(std::string message, sf::IpAddress ip);
    void sendTcpBySocket(std::string message, sf::TcpSocket *socket);
    void sendUdp(std::string message, sf::IpAddress ipAddressOfClient, unsigned short portOfClient);
    virtual bool receivedTcp(std::string message, sf::IpAddress ip) {};
    virtual bool receivedUdp(std::string message, sf::IpAddress ip) {};
    virtual void gotNewClient(sf::TcpSocket *socket) {};
    virtual void lostClient(sf::TcpSocket *socket) {};
    bool shouldServerContinue();
private:
    ServerCommunicator &communicator;
    std::vector<ClientInfo> clients;
    void checkForNewClients();
    bool isClientInUpdatedList(sf::TcpSocket *client, std::vector<sf::TcpSocket *>&list);
    bool isInClientList(sf::TcpSocket *ip);
    sf::UdpSocket udpSocket;
    std::vector<std::string> split(const std::string s, char delim);
};

#endif /* NetworkServer_cpp */
