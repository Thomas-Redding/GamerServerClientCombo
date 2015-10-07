//
//  GameServer.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef GameServer_cpp
#define GameServer_cpp

#include <iostream>
#include <deque>
#include "Entities.hpp"
#include "InputState.hpp"
#include "SystemsHandler.hpp"

class GameServer {
public:
	void start(std::vector<sf::IpAddress> myPlayers);
	void update();
	void receivedTcp(std::string message, long timeStamp);
	void receivedUdp(std::string message, long timeStamp);
	std::vector<std::string> udpMessagesToSend;
	std::vector<sf::IpAddress> udpIp;
	std::vector<std::string> tcpMessagesToSend;
	std::vector<std::string> tcpIp;
private:
	std::deque<Entities> entities;
	std::deque<std::vector<InputState>> inputStates;
	SystemsHandler systemsHandler;
	long getTime();
	std::vector<sf::IpAddress> players;
};

#endif /* GameServer_cpp */
