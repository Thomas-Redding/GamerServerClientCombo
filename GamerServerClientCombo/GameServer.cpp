//
//  GameServer.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "GameServer.hpp"

/*** Public ***/

GameServer::GameServer() : systemsHandler(true) {
	//
}

void GameServer::start(std::vector<sf::IpAddress> myPlayers) {
	players = myPlayers;
	// put empty InputState and Entities into queues
	inputStates = std::vector<std::deque<InputState>>(players.size());
	for(int i=0; i<players.size(); i++) {
		inputStates[i].push_back(InputState());
		systemsHandler.clearInputState(&inputStates[i].front());
	}
	entities.push_front(Entities());
	// setup single item in entities at start of game
	systemsHandler.setupEntities(&entities.front());
	timeOfLastFrame = getTime();
}

void GameServer::update() {
	entities.push_front(entities.front());
	for(int i=0; i<players.size(); i++)
		inputStates[i].push_front(InputState());
	
	
	long deltaTime = getTime() - timeOfLastFrame;
	timeOfLastFrame = getTime();
	entities.front().timeStamp = timeOfLastFrame;
	while(entities.back().timeStamp > timeOfLastFrame - 1000) {
		entities.pop_back();
		for(int i=0; i<inputStates.size(); i++)
			inputStates[i].pop_back();
	}
	
	for(int i=0; i<players.size(); i++) {
		systemsHandler.update(&entities.front(), &inputStates[i], timeOfLastFrame-deltaTime, timeOfLastFrame);
	}
	
	for(int i=0; i<players.size(); i++) {
		std::string str = systemsHandler.entitiesToString(&entities.front(), players[i]);
		udpMessagesToSend.push_back(str);
		udpIp.push_back(players[i]);
	}
}

void GameServer::receivedTcp(std::string message, sf::IpAddress ip, long timeStamp) {
}

void GameServer::receivedUdp(std::string message, sf::IpAddress ip, long timeStamp) {
	InputState newInfo;
	systemsHandler.applyInputState(&newInfo, message);
	for(int i=0; i<players.size(); i++) {
		if(ip == players[i]) {
			// insert in correct place in player's input queue
			long startTime = -1;
			for(int j=0; j<inputStates[i].size(); j++) {
				if(inputStates[i][j].timeStamp < newInfo.timeStamp) {
					startTime = inputStates[i][j].timeStamp;
					inputStates[i].insert(inputStates[i].begin()+j, newInfo);
					break;
				}
			}
			// todo: lag compensation
			if(startTime == -1) {
				inputStates[i].push_back(newInfo);
				// simulate
			}
			else {
				for(int j=0; j<inputStates[i].size(); j++) {
					if(inputStates[i][j].timeStamp < startTime) {
						// simulate from startTime
						break;
					}
				}
			}
		}
	}
}

/*** Private ***/

long GameServer::getTime() {
	return std::chrono::duration_cast< std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
