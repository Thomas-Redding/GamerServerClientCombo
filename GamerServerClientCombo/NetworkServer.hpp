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

class NetworkServer {
public:
    NetworkServer(ServerCommunicator &com);
    
    // return a boolean indicating whether the server should keep running
    bool networkUpdate();
    void sendTcp(std::string message, sf::TcpSocket *socket);
    virtual bool receivedTcp(std::string message) {};
    bool shouldServerContinue();
private:
    ServerCommunicator &communicator;
};

#endif /* NetworkServer_cpp */
