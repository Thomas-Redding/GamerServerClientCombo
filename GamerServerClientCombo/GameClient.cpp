//
//  GameClient.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/6/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "GameClient.hpp"

GameClient::GameClient(int *currentPageNumber, sf::RenderWindow *w, sf::Font *myFont) : Page(currentPageNumber, w, myFont), view(w), systemsHandler(false) {
	inputStates.push_back(std::deque<InputState>());
	timeOfLastFrame = getTime();
	systemsHandler.clearInputState(&currentInputState);
	currentInputState.timeStamp = timeOfLastFrame;
	
	// put empty InputState and Entities into queues
	inputStates[0].push_back(currentInputState);
	entities.push_front(Entities());
	
	// setup single item in entities at start of game
	systemsHandler.setupEntities(&entities.front());
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
	
	// client-side prediction
	bool rtn = systemsHandler.update(&entities.front(), &inputStates[0], timeOfLastFrame-deltaTime, timeOfLastFrame);
    sendMessageToClient(systemsHandler.inputStateToString(&inputStates[0].front()));
	
	systemsHandler.clearInputState(&currentInputState);
	
	debug();
	
	return rtn;
}

void GameClient::tcpMessageReceived(std::string message, long timeStamp) {
	// do nothing
};

void GameClient::udpMessageReceived(std::string message, long timeStamp) {
	return;
	// insert server's world state into queue (store back up to 1 second)
	Entities newEntities;
	systemsHandler.entitiesFromString(&newEntities, message);
	int i;
	for(i=0; i<serverEntities.size(); i++) {
		if(newEntities.timeStamp > serverEntities[i].timeStamp) {
			serverEntities.insert(serverEntities.begin()+i, newEntities);
			break;
		}
	}
	if(i == 0 || i == serverEntities.size())
		serverEntities.push_back(newEntities);
	
	long t = getTime();
	while(serverEntities.size() > 1 && serverEntities.back().timeStamp < t - 1000) {
		serverEntities.pop_back();
	}
	
	// interpolation with lag of 100ms
	int serverEntityIndex = -1;
	long artificialLag = 100;
	for(int i=0; i<serverEntities.size(); i++) {
		if(serverEntities[i].timeStamp < t - artificialLag) {
			serverEntityIndex = i;
			break;
		}
	}
	
	if(serverEntityIndex > 0) {
		for(int i=0; i<entities.size(); i++) {
			if(entities[i].timeStamp < t - artificialLag) {
				entities[i] = serverEntities[serverEntityIndex];
				for (int j=i-1; j>=0; j--) {
					// simulate forward
					entities[j] = entities[j+1];
					systemsHandler.update(&entities[j], &inputStates[0], entities[j+1].timeStamp, entities[j].timeStamp);
				}
				break;
			}
		}
	}
};

/*** Forward to View ***/

bool GameClient::resized(unsigned int width, unsigned int height) {
	return view.resized(width, height);
}

bool GameClient::draw() {
	return view.draw(&entities.front());
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

void GameClient::debug() {
//	std::cout << getTime() << ": ";
//	std::string str = "";
//	for(int i=0; i<inputStates[0].size(); i++) {
//		str += "{";
//		str += std::to_string(inputStates[0][i].timeStamp);
//		str += std::to_string(inputStates[0][i].up);
//		str += "}";
//	}
//	std::cout << str << "\n\n";
}

