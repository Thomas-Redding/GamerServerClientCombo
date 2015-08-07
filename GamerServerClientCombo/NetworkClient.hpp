//
//  NetworkClient.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef NetworkClient_cpp
#define NetworkClient_cpp

#include <stdio.h>
#include <iostream>
#include <SFML/Network.hpp>
#include "ServerCommunicator.hpp"

class NetworkClient {
public:
    NetworkClient(ServerCommunicator& com);
    ~NetworkClient();
    void attemptConnectionToServer(sf::IpAddress serverIpAddress, unsigned short serverPort);
    void sendOwnTcpServerMessageToQuit(unsigned short localTcpPort);
    
    // should be called by Client regularly to check ports
    int update();
    
    /*
     0 = no connection established or attempted
     1 = connection establishe
     -1 = failed to connect
     */
    int getConnectionStage();
    void sendTcpMessage(std::string message);
    unsigned short getLocalServerTcpPort();
    
private:
    sf::IpAddress getMyIpAddress();
    int connectionStage = 0;
    sf::TcpSocket tcpSocket;
    unsigned short tcpPortOfServer;
    ServerCommunicator &communicator;
};

#endif /* NetworkClient_cpp */
