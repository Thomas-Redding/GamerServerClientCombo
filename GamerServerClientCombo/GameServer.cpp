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
	// put empty InputState and Entities into queues
	inputStates.push_back(std::vector<InputState>(players.size()));
	for(int i=0; i<players.size(); i++) {
		systemsHandler.clearInputState(&inputStates.front()[i], getTime());
	}
	entities.push_front(Entities());
	
	// setup single item in entities at start of game
	systemsHandler.setupEntities(&entities.front());
	timeOfLastFrame = getTime();
}

void GameServer::update() {
	entities.push_front(entities.front());
	inputStates.push_front(std::vector<InputState>(players.size()));
	if(entities.size() > 20) {
		entities.pop_back();
		inputStates.pop_back();
	}
	long deltaTime = getTime() - timeOfLastFrame;
	timeOfLastFrame = getTime();
	systemsHandler.update(&entities.front(), &inputStates.front(), deltaTime);
	for(int i=0; i<players.size(); i++) {
		udpMessagesToSend.push_back("foo");
		udpIp.push_back(players[i]);
	}
}

void GameServer::receivedTcp(std::string message, sf::IpAddress ip, long timeStamp) {
	std::cout << "TCP: " << message << " : " << timeStamp << "\n";
}

void GameServer::receivedUdp(std::string message, sf::IpAddress ip, long timeStamp) {
	for(int i=0; i<players.size(); i++) {
		if(ip == players[i]) {
			systemsHandler.applyInputState(&inputStates.front()[i], message);
			systemsHandler.update(&entities.front(), &inputStates.front(), 50);
		}
	}
	std::cout << "UDP: " << message << " : " << timeStamp << "\n";
}

/*** Private ***/

long GameServer::getTime() {
	return std::chrono::duration_cast< std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
