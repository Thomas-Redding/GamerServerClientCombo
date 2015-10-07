//
//  GameServer.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "GameServer.hpp"

/*** Public ***/

void GameServer::start(std::vector<sf::IpAddress> myPlayers) {
	players = myPlayers;
}

void GameServer::update() {
	udpMessagesToSend.push_back("foo");
	udpIp.push_back(sf::IpAddress::getLocalAddress());
}

void GameServer::receivedTcp(std::string message, long timeStamp) {
	std::cout << "TCP: " << message << " : " << timeStamp << "\n";
}

void GameServer::receivedUdp(std::string message, long timeStamp) {
	std::cout << "UDP: " << message << " : " << timeStamp << "\n";
}

/*** Private ***/

long GameServer::getTime() {
	return std::chrono::duration_cast< std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
