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

void GameServer::start(std::vector<sf::IpAddress> myPlayers, std::string startDetails) {
	players = myPlayers;
	// put empty InputState and Entities into queues
	inputStates = std::vector<std::deque<InputState>>(players.size());
	for(int i=0; i<players.size(); i++) {
		inputStates[i].push_back(InputState());
	}
	entities.push_front(Entities());
	// setup single item in entities at start of game
	
	systemsHandler.setupEntities(&entities.front(), startDetails);
	timeOfLastFrame = getTime();
}

void GameServer::update() {
	entities.push_front(entities.front());
	
	long deltaTime = getTime() - timeOfLastFrame;
	timeOfLastFrame = getTime();
	entities.front().timeStamp = timeOfLastFrame;
	
	while(!entities.empty() && entities.back().timeStamp > timeOfLastFrame - 1000)
		entities.pop_back();
	for(int i=0; i<inputStates.size(); i++)
		while(inputStates[i].back().timeStamp > timeOfLastFrame - 1000)
			inputStates[i].pop_back();
	
	for(int i=0; i<players.size(); i++) {
		systemsHandler.update(&entities.front(), &inputStates[i], timeOfLastFrame-deltaTime, timeOfLastFrame, i);
	}
	
	for(int i=0; i<players.size(); i++) {
		std::string str = systemsHandler.entitiesToString(&entities.front(), players[i]);
		str = std::to_string(inputStates[i].front().timeStamp) + "$" + str;
		udpMessagesToSend.push_back(str);
		udpIp.push_back(players[i]);
	}
}

void GameServer::receivedTcp(std::string message, sf::IpAddress ip, long timeStamp) {
}

void GameServer::receivedUdp(std::string message, sf::IpAddress ip, long timeStamp) {
	InputState newInfo;
	systemsHandler.inputStateFromString(&newInfo, message);
	
	for(int i=0; i<players.size(); i++) {
		if(ip == players[i]) {			
			// insert in correct place in player's input queue
			signed long startTime = -1;
			for(int j=0; j<inputStates[i].size(); j++) {
				if(inputStates[i][j].timeStamp < newInfo.timeStamp) {
					startTime = inputStates[i][j].timeStamp;
					inputStates[i].insert(inputStates[i].begin()+j, newInfo);
					break;
				}
			}
			// perform lag compensation
			if(startTime == -1)
				inputStates[i].push_back(newInfo);
			simulateFromTime(startTime);
		}
	}
}

/*** Private ***/

long GameServer::getTime() {
	return std::chrono::duration_cast< std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void GameServer::simulateFromTime(long startTime) {
	if(startTime == -1)
		startTime = entities.back().timeStamp;
	int startEntity = entities.size()-1;
	
	for(int i=0; i<entities.size(); i++) {
		if(entities[i].timeStamp < startTime) {
			startEntity = i;
			break;
		}
	}
	if(startEntity == entities.size()-1)
		startEntity--;
	for(int i=startEntity-1; i>=0; i--) {
		long timeStamp = entities[i].timeStamp;
		entities[i] = entities[i+1];
		entities[i].timeStamp = timeStamp;
		for(int j=0; j<inputStates.size(); j++) {
			systemsHandler.update(&entities[i], &inputStates[j], entities[i+1].timeStamp, entities[i].timeStamp, j);
		}
	}
}
