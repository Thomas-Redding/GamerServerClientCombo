//
//  ClientServerCommunicator.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 11/1/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef ClientServerCommunicator_cpp
#define ClientServerCommunicator_cpp

#include <stdio.h>
#include <sstream>
#include <queue>
#include <mutex>
#include <iostream>

class ClientServerCommunicator {
public:
	void sendTcpMessageToClient(std::string message);
	void sendUdpMessageToClient(std::string message);
	void sendTcpMessageToServer(std::string message);
	void sendUdpMessageToServer(std::string message);
	std::string getTcpMessagesForClient();
	std::string getUdpMessagesForClient();
	std::string getTcpMessagesForServer();
	std::string getUdpMessagesForServer();
private:
	std::queue<std::string> tcpMessagesToClient;
	std::queue<std::string> udpMessagesToClient;
	std::queue<std::string> tcpMessagesToServer;
	std::queue<std::string> udpMessagesToServer;
	std::mutex lockTcpToClient;
	std::mutex lockUdpToClient;
	std::mutex lockTcpToServer;
	std::mutex lockUdpToServer;
};

#endif /* ClientServerCommunicator_cpp */
