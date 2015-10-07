//
//  SystemsHandler.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/6/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "SystemsHandler.hpp"

/*** Public ***/

void SystemsHandler::setupEntities(Entities *entities) {
	// todo
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

bool SystemsHandler::update(Entities *entities, std::vector<InputState> *inputStates, long deltaTime) {
	// apply inputs
	if(inputStates->size() > 1) {
		std::cout << "<" << inputStates->size() << inputStates->at(0).up << inputStates->at(1).up << ">\n";
	}
	for(int i=0; i<inputStates->size(); i++) {
		if(inputStates->at(i).left)
			entities->boxX -= deltaTime;
		if(inputStates->at(i).right)
			entities->boxX += deltaTime;
		if(inputStates->at(i).up)
			entities->boxY -= deltaTime;
		if(inputStates->at(i).down)
			entities->boxY += deltaTime;
	}
	return true;
}

std::string SystemsHandler::entitiesToString(Entities *entities, sf::IpAddress ip) {
	return std::to_string(entities->boxX) + "," + std::to_string(entities->boxY);
}

void SystemsHandler::entitiesFromString(Entities *entities, std::string str) {
    std::vector<std::string> vect = split(str, ',');
	if(vect.size() == 2) {
		entities->boxX = stof(vect[0]);
		entities->boxY = stof(vect[1]);
	}
}

std::string SystemsHandler::inputStateToString(std::vector<InputState> *inputStates) {
    std::string str = std::to_string(inputStates->at(0).timeStamp)+":";
	str += std::to_string(inputStates->at(0).up);
	str += std::to_string(inputStates->at(0).down);
	str += std::to_string(inputStates->at(0).left);
	str += std::to_string(inputStates->at(0).right);
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

void SystemsHandler::clearInputState(InputState *inputState, long time) {
    inputState->timeStamp = time;
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
    return elems;
}


