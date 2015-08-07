//
//  ServerCommunicator.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef ServerCommunicator_cpp
#define ServerCommunicator_cpp

#include <stdio.h>
#include <mutex>
#include <vector>
#include <iostream>
#include <sstream>
#include <queue>
#include <SFML/Network.hpp>

struct ServerCommunicator {
public:
    bool getShouldServersContinue();
    void setShouldServersContinue(bool newValue);
    
    // used by Server
    std::string receiveTcpMessage();
    std::vector<sf::TcpSocket*> getClients();
    
    // used by TcpServer
    void sendTcpMessageToServer(std::string message);
    void setClients(std::vector<sf::TcpSocket*> *vect);
private:
    std::mutex shouldServersContinue_lock;
    bool shouldServersContinue = true;
    
    std::mutex tcpMessagesFromClients_lock;
    std::queue<std::string> tcpMessagesFromClients;
    
    std::mutex clients_lock;
    std::vector<sf::TcpSocket*> clients;
};

#endif /* ServerCommunicator_cpp */
