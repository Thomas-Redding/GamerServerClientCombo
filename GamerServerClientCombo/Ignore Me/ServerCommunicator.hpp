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

/*
 NOTE: If you are a casual user, just focus on the Client and Server classes (i.e. ignore this one).
 
 This class is a singleton and is instantiated in main(). It allows the program's 3 threads (Client, Server, and TcpServer) to communicate. The only complexity here is the mutex locks.
 */

struct ServerCommunicator {
public:
	bool getShouldServersContinue();
	void setShouldServersContinue(bool newValue);
	void setLocalTcpPort(unsigned short newValue);
	unsigned short getLocalTcpPort();
	std::vector<std::string> receiveTcpMessage();
	std::vector<sf::TcpSocket*> getClients();
	void sendTcpMessageToServer(std::string message, std::string ip);
	void setClients(std::vector<sf::TcpSocket*> *vect);
private:
	std::mutex shouldServersContinue_lock;
	bool shouldServersContinue = true;
	
	std::mutex tcpMessagesFromClients_lock;
	std::queue<std::string> tcpMessagesFromClients;
	std::queue<std::string> tcpIpsFromClients;
	
	std::mutex clients_lock;
	std::vector<sf::TcpSocket*> clients;
	
	std::mutex localTcpPort_lock;
	unsigned short localTcpPort;
};

#endif /* ServerCommunicator_cpp */
