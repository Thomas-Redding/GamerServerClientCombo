//
//  Server.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef Server_cpp
#define Server_cpp

#include <stdio.h>
#include <iostream>
#include <chrono>
#include <SFML/Network.hpp>
#include "ServerCommunicator.hpp"

class Server {
public:
    Server(ServerCommunicator &com);
    
    // return a boolean indicating whether the server should keep running
    bool update();
private:
    void sendTcp(std::string message, sf::TcpSocket *socket);
    std::string readTcp();
    bool shouldServerContinue();
    
    // ignore this
    ServerCommunicator &communicator;
};

#endif /* Server_cpp */
