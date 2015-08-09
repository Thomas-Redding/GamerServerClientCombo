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
#include "NetworkServer.hpp"

class Server : public NetworkServer {
public:
    Server(ServerCommunicator &com);
    
    // return a boolean indicating whether the server should keep running
    bool update();
    bool receivedTcp(std::string message);
};

#endif /* Server_cpp */
