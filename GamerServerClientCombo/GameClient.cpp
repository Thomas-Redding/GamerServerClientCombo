//
//  GameClient.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/6/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "GameClient.hpp"

GameClient::GameClient(int *currentPageNumber, sf::RenderWindow *w, sf::Font *myFont) : Page(currentPageNumber, w, myFont), view(w), systemsHandler(false) {
	// nothing to do
}

/*** Forward to SystemsHandler ***/

bool GameClient::keyPressed(sf::Keyboard::Key keyCode) {
	return true;
};

bool GameClient::keyReleased(sf::Keyboard::Key keyCode) {
	return true;
}

bool GameClient::mouseMoved(int x, int y) {
	return true;
}

bool GameClient::mousePressed(sf::Mouse::Button button, int x, int y) {
	return true;
}

bool GameClient::mouseReleased(sf::Mouse::Button button, int x, int y) {
	return true;
}

bool GameClient::mouseWheeled(int delta, int x, int y) {
	return true;
}

bool GameClient::textEntered(sf::Uint32 character) {
	return true;
}

bool GameClient::otherEvent(sf::Event event) {
	return true;
}

void GameClient::closing() {
}

bool GameClient::update() {
	if(myAvatarId == -1)
		return true;
	
	// set inputs, because the event methods haven't been written yet
	currentInputState.left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	currentInputState.right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	currentInputState.up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	currentInputState.down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	
	// make time computations
	long deltaTime = getTime() - timeOfLastFrame;
	timeOfLastFrame = getTime();
	
	// push_front() and push_back() copy the value given
	// by the time we get here, all the input events for this frame have been polled
	// thus, currentInputState is up-to-date and we should save it
	// save these back through 1000ms in history
	long historyMaxTime = 1000;
	entities.push_front(entities.front());
	entities.front().timeStamp = timeOfLastFrame;
	currentInputState.timeStamp = timeOfLastFrame;
	inputStates[0].push_front(currentInputState);
	
	while(entities.back().timeStamp < timeOfLastFrame - historyMaxTime) {
		entities.pop_back();
		inputStates[0].pop_back();
	}
	
	systemsHandler.update(&entities.front(), &inputStates[0], timeOfLastFrame-deltaTime, timeOfLastFrame, myAvatarId);
	
    sendMessageToClient(systemsHandler.inputStateToString(&inputStates[0].front()));
	systemsHandler.clearInputState(&currentInputState);
	
	return true;
}

void GameClient::tcpMessageReceived(std::string message, long timeStamp) {
	std::vector<std::string> vect = split(message, ':');
	if(vect[0] == "startGame") {
		// set up game
		inputStates.push_back(std::deque<InputState>());
		timeOfLastFrame = getTime();
		systemsHandler.clearInputState(&currentInputState);
		currentInputState.timeStamp = timeOfLastFrame;
		
		// put empty InputState and Entities into queues
		inputStates[0].push_back(currentInputState);
		entities.push_front(Entities());
		
		// setup single item in entities at start of game
		systemsHandler.setupEntities(&entities.front());
		myAvatarId = stoi(vect[1]);
	}
};

void GameClient::udpMessageReceived(std::string message, long timeStamp) {
	// insert server's world state into queue (store back up to 1 second)
	Entities newEntities;
	std::vector<std::string> vect = split(message, '$');
	systemsHandler.entitiesFromString(&newEntities, vect[1]);
	int i;
	for(i=0; i<serverEntities.size(); i++) {
		if(newEntities.timeStamp > serverEntities[i].timeStamp) {
			serverEntities.insert(serverEntities.begin()+i, newEntities);
			serverEntitiesTimes.insert(serverEntitiesTimes.begin()+i, stol(vect[0]));
			break;
		}
	}
	
	if(i == 0 || i == serverEntities.size()) {
		serverEntities.push_back(newEntities);
		serverEntitiesTimes.push_back(stol(vect[0]));
	}
	
	long t = getTime();
	while(serverEntities.size() > 1 && serverEntities.back().timeStamp < t - 1000) {
		serverEntities.pop_back();
	}
};

/*** Forward to View ***/

bool GameClient::resized(unsigned int width, unsigned int height) {
	return view.resized(width, height);
}

bool GameClient::draw() {
	if(entities.size() > 0)
		return view.draw(&entities.front());
	return true;
}


/*** Private ***/

long GameClient::getTime() {
	return std::chrono::duration_cast< std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
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
