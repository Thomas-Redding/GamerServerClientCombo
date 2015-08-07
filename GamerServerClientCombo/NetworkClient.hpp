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
#include <SFML/Network.hpp>

class NetworkClient {
public:
    NetworkClient();
    void attemptConnectionToServer(sf::IpAddress ipAddress);
    
    // should be called by Client regularly to check ports
    int update();
    
    /*
     0 = no connection established or attempted
     1 = sent inital TCP to server with client's ipAddress and port number
     2 = server responded with a UDP port
     -1 = failed to connect
     */
    int getConnectionStage();
private:
    sf::IpAddress getMyIpAddress();
    
    int connectionStage = 0;
};

#endif /* NetworkClient_cpp */
