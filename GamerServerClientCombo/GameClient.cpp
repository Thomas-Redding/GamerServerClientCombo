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
	if(keyCode == sf::Keyboard::Up)
		currentInputState.up = true;
	if(keyCode == sf::Keyboard::Down)
		currentInputState.down = true;
	if(keyCode == sf::Keyboard::Left)
		currentInputState.left = true;
	if(keyCode == sf::Keyboard::Right)
		currentInputState.right = true;
	return true;
};

bool GameClient::keyReleased(sf::Keyboard::Key keyCode) {
	if(keyCode == sf::Keyboard::Up)
		currentInputState.up = false;
	if(keyCode == sf::Keyboard::Down)
		currentInputState.down = false;
	if(keyCode == sf::Keyboard::Left)
		currentInputState.left = false;
	if(keyCode == sf::Keyboard::Right)
		currentInputState.right = false;
	return true;
}

bool GameClient::mouseMoved(int x, int y) {
	return true;
}

bool GameClient::mousePressed(sf::Mouse::Button button, int x, int y) {
	currentInputState.mouseClicked = true;
	currentInputState.mouseDown = true;
	return true;
}

bool GameClient::mouseReleased(sf::Mouse::Button button, int x, int y) {
	currentInputState.mouseDown = false;
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
	
	// move view
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		view.screenY -= 10;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		view.screenY += 10;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		view.screenX -= 10;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		view.screenX += 10;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		view.screenScale *= 1.01;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		view.screenScale /= 1.01;
	
	// get mouse position
	sf::Vector2i mousePosition = sf::Mouse::getPosition() - window->getPosition();
	currentInputState.mouseX = (mousePosition.x + view.screenX) / view.screenScale;
	currentInputState.mouseY = (mousePosition.y + view.screenY) / view.screenScale;
	
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
	
	while(entities.back().timeStamp < timeOfLastFrame - historyMaxTime)
		entities.pop_back();
	while(inputStates[0].back().timeStamp < timeOfLastFrame - historyMaxTime)
		inputStates[0].pop_back();
	
	
	if(useSimpleServer)
		systemsHandler.update(&entities.front(), &inputStates[0], timeOfLastFrame-deltaTime, timeOfLastFrame, myAvatarId);
	else if(useSimpleClient) {
		if(serverEntities.size() > 0)
			entities.push_front(serverEntities.front());
	}
	else {
		// interpolate
		long artificialLag = 100; // ms
		int serverEntityIndex = -1;
		for(int i=0; i<serverEntities.size(); i++) {
			if(serverEntities[i].timeStamp > timeOfLastFrame - artificialLag) {
				serverEntityIndex = i;
				break;
			}
		}
		if(serverEntityIndex == -1)
			serverEntityIndex = serverEntities.size()-1;
		if(serverEntityIndex != -1) {
			for(int i=0; i<entities.size(); i++) {
				if(entities[i].timeStamp < serverEntities[serverEntityIndex].timeStamp) {
					entities.insert(entities.begin()+i, serverEntities[serverEntityIndex]);
					for(int j=i-1; j>=0; j--) {
						long timeStamp = entities[j].timeStamp;
						entities[j] = entities[j+1];
						entities[j].timeStamp = timeStamp;
						systemsHandler.update(&entities[j], &inputStates[0], entities[j+1].timeStamp, entities[j].timeStamp, myAvatarId);
					}
					break;
				}
			}
		}
		
		// client-side prediction
		systemsHandler.update(&entities.front(), &inputStates[0], timeOfLastFrame-deltaTime, timeOfLastFrame, myAvatarId);
	}
	
	std::string stringToSendToServer = systemsHandler.inputStateToString(&inputStates[0].front());
    sendMessageToClient(stringToSendToServer);
	currentInputState.mouseClicked = false;
	
	return true;
}

void GameClient::tcpMessageReceived(std::string message, long timeStamp) {
	std::vector<std::string> vect = utility::split(message, ':');
	if(vect[0] == "startGame") {
		// set up game
		inputStates.push_back(std::deque<InputState>());
		timeOfLastFrame = getTime();
		currentInputState.timeStamp = timeOfLastFrame;
		
		// put empty InputState and Entities into queues
		inputStates[0].push_back(currentInputState);
		entities.push_front(Entities());
		
		// setup single item in entities at start of game
		systemsHandler.setupEntities(&entities.front(), vect[2]);
		myAvatarId = stoi(vect[1]);
	}
};

void GameClient::udpMessageReceived(std::string message, long timeStamp) {
	// insert server's world state into queue (store back up to 1 second)
	Entities newEntities;
	std::vector<std::string> vect = utility::split(message, '$');
	systemsHandler.entitiesFromString(&newEntities, vect[1]);
	newEntities.timeStamp = stol(vect[0]);
	newEntities.map = entities.front().map;
	
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
