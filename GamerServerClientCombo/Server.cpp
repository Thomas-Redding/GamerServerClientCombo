//
//  Server.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "Server.hpp"

Server::Server(ServerCommunicator &com, ClientServerCommunicator &comB): NetworkServer(com, comB) {
}

bool Server::update() {
	// sleep for 25 milliseconds
	std::this_thread::sleep_for(std::chrono::milliseconds(25));
	
	if(gameRunning) {
		gameServer.update();
		for(int i=0; i<gameServer.udpMessagesToSend.size(); i++) {
			sendUdp(gameServer.udpMessagesToSend[i], gameServer.udpIp[i]);
		}
		gameServer.udpMessagesToSend.clear();
		for(int i=0; i<gameServer.tcpMessagesToSend.size(); i++) {
			sendTcp(gameServer.tcpMessagesToSend[i], gameServer.tcpIp[i]);
		}
		gameServer.tcpMessagesToSend.clear();
	}
	
	return true;
}

bool Server::receivedTcp(std::string message, sf::IpAddress ip, long timeStamp) {
	sf::IpAddress myIp = sf::IpAddress::getLocalAddress();
	if(message == "startGame" &&  myIp == ip) {
		std::string startMessage = "alpha;" + std::to_string(clients.size());
		gameServer.start(clients, startMessage);
		gameRunning = true;
		for(int i=0; i<clients.size(); i++) {
			sendTcp("startGame:" + std::to_string(i)+":"+startMessage, clients[i]);
		}
	}
	else if(gameRunning) {
		gameServer.receivedTcp(message, ip, timeStamp);
	}
	return true;
}

void Server::gotNewClient(sf::IpAddress ip) {
	clients.push_back(ip);
}

void Server::lostClient(sf::IpAddress ip) {
}

bool Server::receivedUdp(std::string message, sf::IpAddress ip, long timeStamp) {
	if(gameRunning) {
		gameServer.receivedUdp(message, ip, timeStamp);
	}
	return true;
}
