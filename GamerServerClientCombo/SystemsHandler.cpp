//
//  SystemsHandler.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/6/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "SystemsHandler.hpp"

/*** Public ***/

SystemsHandler::SystemsHandler(bool isServerSide) {
	isServer = isServerSide;
}

void SystemsHandler::setupEntities(Entities *entities, std::string launchDetails) {
	std::vector<std::string> launchDetailsVector = util::split(launchDetails, ';');
	if(launchDetailsVector.size() < 2) {
		std::cout << "Launch Details From Server Ill-Formated\n";
		return;
	}
	int numberOfPlayers = stoi(launchDetailsVector[1]);
	entities->players = std::vector<Player>(numberOfPlayers);
	for(int i=0; i<entities->players.size(); i++) {
		entities->players[i].id = 0;
		entities->players[i].x = 100;
		entities->players[i].y = 200;
	}
	
	std::string line;
	std::string contents;
	std::ifstream myfile (resourcePath() + launchDetailsVector[0] + ".txt");
	if (myfile.is_open()) {
		while(getline(myfile,line)) {
			contents += line;
			contents += '\n';
		}
		myfile.close();
	}
	else {
		std::cout << "Unable to open map file\n";
		return;
	}
	
	MapSystem mapSystem = MapSystem();
	mapSystem.loadFromString(&entities->map, contents);
}

void SystemsHandler::update(Entities *entities, std::deque<InputState> *inputStates, long startTime, long endTime, int avatarId) {
	std::vector<float> weights = inputStateWeights(inputStates, startTime, endTime);
	for(int i=0; i<weights.size(); i++) {
		if(weights[i] != 0)
			playerSystem.update(entities, &inputStates->at(i), weights[i], avatarId);
	}
}

std::string SystemsHandler::entitiesToString(Entities *entities, sf::IpAddress ip) {
	std::string rtn = std::to_string(entities->timeStamp);
	for(int i=0; i<entities->players.size(); i++) {
		rtn += ";";
		rtn += std::to_string(entities->players[i].id);
		rtn += ",";
		rtn += std::to_string(entities->players[i].x);
		rtn += ",";
		rtn += std::to_string(entities->players[i].y);
		rtn += ",";
		rtn += std::to_string(entities->players[i].health);
	}
	return rtn;
}

void SystemsHandler::entitiesFromString(Entities *entities, std::string str) {
    std::vector<std::string> vect = util::split(str, ';');
	if(vect.size() >= 1)
		entities->timeStamp = stol(vect[0]);
	entities->players = std::vector<Player>(vect.size()-1);
	for(int i=1; i<vect.size(); i++) {
		std::vector<std::string> vect2 = util::split(vect[i], ',');
		if(vect2.size() >= 4) {
			entities->players[i-1].id = stoi(vect2[0]);
			entities->players[i-1].x = stof(vect2[1]);
			entities->players[i-1].y = stof(vect2[2]);
			entities->players[i-1].health = stof(vect2[3]);
		}
	}
}

std::string SystemsHandler::inputStateToString(InputState *inputState) {
	// {timeStamp}:{mouseClicked},{mouseDown},{mouseX},{mouseY}:{moveX}{moveY}
    std::string str = std::to_string(inputState->timeStamp) + ":";
	str += std::to_string(inputState->mouseClicked) + ",";
	str += std::to_string(inputState->mouseDown) + ",";
	str += std::to_string(inputState->mouseX) + ",";
	str += std::to_string(inputState->mouseY) + ":";
	str += std::to_string(inputState->moveX) + ",";
	str += std::to_string(inputState->moveY);
	return str;
}

void SystemsHandler::inputStateFromString(InputState *inputState, std::string str) {
	// {timeStamp}:{mouseClicked},{mouseDown},{mouseX},{mouseY}:{moveX}{moveY}
    std::vector<std::string> vect = util::split(str, ':');
	if(vect.size() != 3)
		return;
	inputState->timeStamp = stol(vect[0]);
	
	std::vector<std::string> vect2 = util::split(vect[1], ',');
	if(vect2.size() == 4) {
		if(vect2[0] == "1")
			inputState->mouseClicked = true;
		if(vect2[1] == "1")
			inputState->mouseDown = true;
		inputState->mouseX = stof(vect2[2]);
		inputState->mouseY = stof(vect2[3]);
	}
	
	vect2 = util::split(vect[2], ',');
	if(vect2.size() == 2) {
		inputState->moveX = stof(vect2[0]);
		inputState->moveY = stof(vect2[1]);
	}
}

Entities SystemsHandler::interpolate(Entities *from, Entities *to, double t) {
	Entities rtn;
	
	// interpolate between timeStamps
	rtn.timeStamp = from->timeStamp * (1-t) + to->timeStamp * t;
	
	// interpolate between players
	if(t < 0.5) {
		rtn.players = std::vector<Player>(from->players.size());
		for(int i=0; i<from->players.size(); i++) {
			rtn.players[i].id = from->players[i].id;
			rtn.players[i].followerIds = std::vector<int>(from->players[i].followerIds.size());
			int j;
			for(j=0; j<to->players.size(); j++) {
				if(to->players[j].id == rtn.players[i].id) {
					rtn.players[i].x = from->players[i].x * (1-t) + to->players[i].x * t;
					rtn.players[i].y = from->players[i].y * (1-t) + to->players[i].y * t;
					rtn.players[i].health = from->players[i].health * (1-t) + to->players[i].health * t;
					break;
				}
			}
			if(j == to->players.size()) {
				rtn.players[i].x = from->players[i].x;
				rtn.players[i].y = from->players[i].y;
				rtn.players[i].health = from->players[i].health;
			}
		}
	}
	else {
		rtn.players = std::vector<Player>(to->players.size());
		for(int i=0; i<to->players.size(); i++) {
			rtn.players[i].id = to->players[i].id;
			rtn.players[i].followerIds = std::vector<int>(to->players[i].followerIds.size());
			int j;
			for(j=0; j<from->players.size(); j++) {
				if(from->players[j].id == rtn.players[i].id) {
					rtn.players[i].x = from->players[i].x * (1-t) + to->players[i].x * t;
					rtn.players[i].y = from->players[i].y * (1-t) + to->players[i].y * t;
					rtn.players[i].health = from->players[i].health * (1-t) + to->players[i].health * t;
					break;
				}
			}
			if(j == from->players.size()) {
				rtn.players[i].x = to->players[i].x;
				rtn.players[i].y = to->players[i].y;
				rtn.players[i].health = to->players[i].health;
			}
		}
	}
	return rtn;
}

/*** Private ***/

std::vector<float> SystemsHandler::inputStateWeights(std::deque<InputState> *inputStates, long startTime, long endTime) {
	long len = inputStates->size();
	std::vector<float> rtn(len);
	for(int i=0; i<rtn.size()-1; i++) {
		rtn[i] = lineIntersect(startTime, endTime, inputStates->at(i+1).timeStamp, inputStates->at(i).timeStamp);
	}
	rtn[rtn.size()-1] = 0;
	return rtn;
}

long SystemsHandler::lineIntersect(long a, long b, long c, long d) {
	if(a <= c && d <= b)
		return d-c; // ab contains cd
	else if(c <= a && b <= d)
		return b-a; // cd contains ab
	else if(b <= c || d <= a)
		return 0; // no overlap
	else if(a <= c && b <= d)
		return b-c; // staggered - cd in front
	else if(c <= a && d <= b)
		return d-a; // staggered - ab in front
	else
		return 0;
}
