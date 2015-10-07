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

std::string SystemsHandler::entitiesToString(sf::IpAddress ip) {
	return std::to_string(entities.front().boxX) + "," + std::to_string(entities.front().boxY);
}

void SystemsHandler::entitiesFromString(std::string str) {
	std::vector<std::string> vect = split(str, ',');
	if(vect.size() == 2) {
		entities.front().boxX = stof(vect[0]);
		entities.front().boxY = stof(vect[1]);
	}
}

std::string SystemsHandler::inputStateToString() {
	std::string str = "";
	str += std::to_string(inputStates.front()[0].up);
	str += std::to_string(inputStates.front()[0].down);
	str += std::to_string(inputStates.front()[0].left);
	str += std::to_string(inputStates.front()[0].right);
	return str;
}

void SystemsHandler::applyInputState(InputState *inputState) {
	//
}

/*** Private ***/



