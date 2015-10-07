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

/*** Private ***/

