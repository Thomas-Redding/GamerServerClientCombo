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
#include <chrono>
#include "Entities.hpp"
#include "InputState.hpp"
#include "SystemsHandler.hpp"

class GameServer {
public:
	GameServer();
	void start(std::vector<sf::IpAddress> myPlayers, std::string startDetails);
	void update();
	void receivedTcp(std::string message, sf::IpAddress ip, long timeStamp);
	void receivedUdp(std::string message, sf::IpAddress ip, long timeStamp);
	std::vector<std::string> udpMessagesToSend;
	std::vector<sf::IpAddress> udpIp;
	std::vector<std::string> tcpMessagesToSend;
	std::vector<std::string> tcpIp;
private:
	std::deque<Entities> entities;
	std::vector<std::deque<InputState>> inputStates;
	SystemsHandler systemsHandler;
	long timeOfLastFrame;
	long getTime();
	std::vector<sf::IpAddress> players;
	void simulateFromTime(long startTime);
	std::string startDetails;

};

#endif /* GameServer_cpp */
