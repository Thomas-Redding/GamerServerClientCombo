//
//  GameClient.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/6/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "GameClient.hpp"

GameClient::GameClient(int *currentPageNumber, sf::RenderWindow *w, sf::Font *myFont) : Page(currentPageNumber, w, myFont), view(w) {
	// put empty InputState and Entities into queues
	inputStates.push_back(std::vector<InputState>());
	clearInputState(getTime());
	inputStates.front().push_back(currentInputState);
	entities.push_front(Entities());
	
	// setup single item in entities at start of game
	systemsHandler.setupEntities(&entities.front());
	timeOfLastFrame = getTime();
}

/*** Forward to SystemsHandler ***/

bool GameClient::keyPressed(sf::Keyboard::Key keyCode) {
	return systemsHandler.keyPressed(keyCode);
};

bool GameClient::keyReleased(sf::Keyboard::Key keyCode) {
	return systemsHandler.keyReleased(keyCode);
}

bool GameClient::mouseMoved(int x, int y) {
	return systemsHandler.mouseMoved(x, y);
}

bool GameClient::mousePressed(sf::Mouse::Button button, int x, int y) {
	return systemsHandler.mousePressed(button, x, y);
}

bool GameClient::mouseReleased(sf::Mouse::Button button, int x, int y) {
	return systemsHandler.mouseReleased(button, x, y);
}

bool GameClient::mouseWheeled(int delta, int x, int y) {
	return systemsHandler.mouseWheeled(delta, x, y);
}

bool GameClient::textEntered(sf::Uint32 character) {
	return systemsHandler.textEntered(character);
}

bool GameClient::otherEvent(sf::Event event) {
	return systemsHandler.otherEvent(event);
}

void GameClient::closing() {
	systemsHandler.closing();
}

bool GameClient::update() {
	// push_front() and push_back() copy the value given
	// by the time we get here, all the input events for this frame have been polled
	// thus, currentInputState is up-to-date and we should save it
	currentInputState.left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	currentInputState.right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	currentInputState.up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	currentInputState.down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	entities.push_front(entities.front());
	inputStates.push_front(std::vector<InputState>());
	inputStates.front().push_back(currentInputState);
	if(entities.size() > 20) {
		entities.pop_back();
		inputStates.pop_back();
	}
	long deltaTime = getTime() - timeOfLastFrame;
	timeOfLastFrame = getTime();
	bool rtn = systemsHandler.update(&entities.front(), &inputStates.front(), deltaTime);
	clearInputState(timeOfLastFrame);
	return rtn;
}

void GameClient::tcpMessageReceived(std::string message, long timeStamp) {
	// todo
};

void GameClient::udpMessageReceived(std::string message, long timeStamp) {
	// todo
};

/*** Forward to View ***/

bool GameClient::resized(unsigned int width, unsigned int height) {
	return view.resized(width, height);
}

bool GameClient::draw() {
	return view.draw(&entities.front());
}


/*** Private ***/

void GameClient::clearInputState(long time) {
	currentInputState.timeStamp = time;
	currentInputState.up = false;
	currentInputState.down = false;
	currentInputState.left = false;
	currentInputState.right = false;
}

long GameClient::getTime() {
	return std::chrono::duration_cast< std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

std::string GameClient::entitiesToString(sf::IpAddress ip) {
	return std::to_string(entities.front().boxX) + "," + std::to_string(entities.front().boxY);
}

void GameClient::entitiesFromString(std::string str) {
	std::vector<std::string> vect = split(str, ',');
	if(vect.size() == 2) {
		entities.front().boxX = stof(vect[0]);
		entities.front().boxY = stof(vect[1]);
	}
}

std::string GameClient::inputStateToString() {
	std::string str = "";
	str += std::to_string(inputStates.front()[0].up);
	str += std::to_string(inputStates.front()[0].down);
	str += std::to_string(inputStates.front()[0].left);
	str += std::to_string(inputStates.front()[0].right);
	return str;
}

void GameClient::applyInputState(InputState *inputState) {
	//
}

std::vector<std::string> GameClient::split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
	return elems;
}

