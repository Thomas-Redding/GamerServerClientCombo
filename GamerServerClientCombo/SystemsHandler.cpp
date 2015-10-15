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

void SystemsHandler::setupEntities(Entities *entities) {
	entities->soldiers = std::vector<Soldier>(1);
	entities->soldiers[0].id = 0;
	entities->soldiers[0].x = 100;
	entities->soldiers[0].y = 200;
}

bool SystemsHandler::keyPressed(sf::Keyboard::Key keyCode) {
	return true;
}

bool SystemsHandler::keyReleased(sf::Keyboard::Key keyCode) {
	return true;
}

bool SystemsHandler::mouseMoved(int x, int y) {
	return true;
}

bool SystemsHandler::mousePressed(sf::Mouse::Button button, int x, int y) {
	return true;
}

bool SystemsHandler::mouseReleased(sf::Mouse::Button button, int x, int y) {
	return true;
}

bool SystemsHandler::mouseWheeled(int delta, int x, int y) {
	return true;
}

bool SystemsHandler::textEntered(sf::Uint32 character) {
	return true;
}

bool SystemsHandler::otherEvent(sf::Event event) {
	return true;
}

void SystemsHandler::closing() {
	return true;
}

bool SystemsHandler::update(Entities *entities, std::deque<InputState> *inputStates, long startTime, long endTime) {
	std::vector<float> weights = inputStateWeights(inputStates, startTime, endTime);
	for(int i=0; i<weights.size(); i++) {
		if(weights[i] != 0)
			miniUpate(entities, &inputStates->at(i), weights[i]);
	}
	return true;
}

std::string SystemsHandler::entitiesToString(Entities *entities, sf::IpAddress ip) {
	std::string rtn = std::to_string(entities->timeStamp);
	for(int i=0; i<entities->soldiers.size(); i++) {
		rtn += ";";
		rtn += std::to_string(entities->soldiers[i].id);
		rtn += ",";
		rtn += std::to_string(entities->soldiers[i].x);
		rtn += ",";
		rtn += std::to_string(entities->soldiers[i].y);
	}
	return rtn;
}

void SystemsHandler::entitiesFromString(Entities *entities, std::string str) {
    std::vector<std::string> vect = split(str, ';');
	if(vect.size() >= 1)
		entities->timeStamp = stol(vect[0]);
	entities->soldiers = std::vector<Soldier>(vect.size()-1);
	for(int i=1; i<vect.size(); i++) {
		std::vector<std::string> vect2 = split(vect[i], ',');
		if(vect.size() == 3) {
			entities->soldiers[i].id = stoi(vect2[0]);
			entities->soldiers[i].x = stof(vect2[1]);
			entities->soldiers[i].y = stof(vect2[2]);
		}
	}
}

std::string SystemsHandler::inputStateToString(InputState *inputStates) {
    std::string str = std::to_string(inputStates->timeStamp)+":";
	str += std::to_string(inputStates->up);
	str += std::to_string(inputStates->down);
	str += std::to_string(inputStates->left);
	str += std::to_string(inputStates->right);
	return str;
}

void SystemsHandler::applyInputState(InputState *inputState, std::string str) {
    std::vector<std::string> vect = split(str, ':');
	if(vect.size() != 2)
		return;
	inputState->timeStamp = stol(vect[0]);
	if(vect[1].length() == 4) {
		if(vect[1][0] == '1')
			inputState->up = true;
		else
			inputState->up = false;
		if(vect[1][1] == '1')
			inputState->down = true;
		else
			inputState->down = false;
		if(vect[1][2] == '1')
			inputState->left = true;
		else
			inputState->left = false;
		if(vect[1][3] == '1')
			inputState->right = true;
		else
			inputState->right = false;
	}
}

void SystemsHandler::clearInputState(InputState *inputState) {
    inputState->timeStamp = 0;
    inputState->up = false;
    inputState->down = false;
    inputState->left = false;
    inputState->right = false;
}

/*** Private ***/

std::vector<std::string> SystemsHandler::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<float> SystemsHandler::inputStateWeights(std::deque<InputState> *inputStates, long startTime, long endTime) {
	std::vector<float> rtn(inputStates->size());
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
		return c-b; // staggered - cd in front
	else if(c <= a && d <= b)
		return d-a; // staggered - ad in front
	else
		return 0;
}

void SystemsHandler::miniUpate(Entities *entities, InputState *inputStates, long deltaTime) {
	if(inputStates->up)
		entities->soldiers[0].y -= deltaTime;
	if(inputStates->down)
		entities->soldiers[0].y += deltaTime;
	if(inputStates->left)
		entities->soldiers[0].x -= deltaTime;
	if(inputStates->right)
		entities->soldiers[0].x += deltaTime;
}
