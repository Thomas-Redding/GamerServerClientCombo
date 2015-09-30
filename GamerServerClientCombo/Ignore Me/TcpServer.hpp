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

/*
 NOTE: If you are a casual user, just focus on the Client and Server classes (i.e. ignore this one).
 
 This class is a singleton and is instantiated in main(). It servers 1 purpose: listen for TCP messages from clients and pass them on to the Server class. The small bit of string manipulations with '_' and ip addresses are explained in NetworkServer.
 */


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
