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
#include <time.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Network.hpp>
#include "NetworkServer.hpp"
#include "GameServer.hpp"

/*
 The casual user of ths Server doesn't have to look at NetworkServer. Instead, you need only know that there are some methods defined within it that may prove useful. Most of them should be self-explanatory.
 
 NEVER start a UDP or TCP message with the underscore character. Messages starting with the underscore character are reserved for the NetworkClient and NetworkServer classes.
 
 void networkUpdate() - don't define or call this method
 bool shouldServerContinue() - check this periodically to see if the server should continue or quit
 
 void sendTcp(std::string message, sf::IpAddress ip)
 void sendUdp(std::string message, sf::IpAddress ipAddressOfClient)
 virtual bool receivedTcp(std::string message, sf::IpAddress ip, long timestamp) - event method for you to define
 virtual bool receivedUdp(std::string message, sf::IpAddress ip, long timestamp) - event method for you to define
 virtual void gotNewClient(sf::IpAddress ip) - event method for you to define
 virtual void lostClient(sf::IpAddress ip) - event method for you to define; do NOT rely on it
 long getTime() - gets the number of milliseconds since the epoch (1970)
*/

class Server : public NetworkServer {
public:
	Server(ServerCommunicator &com, ClientServerCommunicator &comB);
	
	// return a boolean indicating whether the server should keep running
	bool update();
	bool receivedTcp(std::string message, sf::IpAddress ip, long timeStamp);
	bool receivedUdp(std::string message, sf::IpAddress ip, long timeStamp);
	void gotNewClient(sf::IpAddress ip);
	void lostClient(sf::IpAddress ip);
private:
	bool gameRunning = false;
	std::vector<sf::IpAddress> clients;
	GameServer gameServer;
};

#endif /* Server_cpp */
