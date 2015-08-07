//
//  TcpServer.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef TcpServer_cpp
#define TcpServer_cpp

#include <stdio.h>
#include <iostream>
#include <chrono>
#include <SFML/Network.hpp>
#include "ServerCommunicator.hpp"

class TcpServer {
public:
    TcpServer(ServerCommunicator &com);
    bool update();
private:
    ServerCommunicator &communicator;
    std::vector<sf::TcpSocket*> clients;
    sf::SocketSelector selector;
    sf::TcpListener listener;
    unsigned short tcpPort;
};

#endif /* TcpServer_cpp */
