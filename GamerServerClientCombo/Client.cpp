//
//  Client.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "Client.hpp"

Client::Client(sf::RenderWindow &myWindow, ServerCommunicator &com) : window(myWindow), NetworkClient(com) {
	// use this to alter the default framerate limit from its default value (60fps)
	window.setFramerateLimit(40);
	
	// connect to the server on your computer
	// attemptConnectionToServer(sf::IpAddress::getLocalAddress(), getLocalServerTcpPort());
}

bool Client::start() {
	// Load and Set the App's Icon
	sf::Image icon;
	if (!icon.loadFromFile(resourcePath() + std::string("icon.png")))
		return false; // failed to load icon - quit app
	else {
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}
	
	
	// Load a font
	if(!font.loadFromFile(resourcePath() + std::string("sansation.ttf")))
		return false; // failed to load font - quit app
	
	pages.push_back(new HomePage(&currentPage, &window, &font));
	pages.push_back(new MultiplayerPage(&currentPage, &window, &font));
	pages.push_back(new ServerPage(&currentPage, &window, &font, getLocalServerTcpPort()));
	pages.push_back(new ClientPage(&currentPage, &window, &font));
	pages.push_back(new ClientMatchmakingPage(&currentPage, &window, &font));
	pages.push_back(new GameClient(&currentPage, &window, &font));
	
	return true;
}

bool Client::keyPressed(sf::Keyboard::Key keyCode) {
	return pages[currentPage]->keyPressed(keyCode);
}
bool Client::keyReleased(sf::Keyboard::Key keyCode) {
	return pages[currentPage]->keyReleased(keyCode);
}
bool Client::mouseMoved(int x, int y) {
	return pages[currentPage]->mouseMoved(x, y);
}
bool Client::mousePressed(sf::Mouse::Button button, int x, int y) {
	return pages[currentPage]->mousePressed(button, x, y);
}
bool Client::mouseReleased(sf::Mouse::Button button, int x, int y) {
	return pages[currentPage]->mouseReleased(button, x, y);
}
bool Client::mouseWheeled(int delta, int x, int y) {
	return pages[currentPage]->mouseWheeled(delta, x, y);
}
bool Client::resized(unsigned int width, unsigned int height) {
	return pages[currentPage]->resized(width, height);
}
bool Client::textEntered(sf::Uint32 character) {
	return pages[currentPage]->textEntered(character);
}
bool Client::otherEvent(sf::Event event) {
	return pages[currentPage]->otherEvent(event);
}
void Client::closing() {
	pages[currentPage]->closing();
	for(int i=0; i<pages.size(); i++) {
		delete pages[i];
	}
}
bool Client::draw() {
	return pages[currentPage]->draw();
}
bool Client::update() {
	std::string str = pages[3]->getMessageForClient();
	if(str.length() > 0) {
		std::vector<std::string> vect = split(str, ':');
		if(vect.size() == 2) {
			attemptConnectionToServer(sf::IpAddress(vect[0]), stoi(vect[1]));
		}
	}
	
	str = pages[1]->getMessageForClient();
	if(str == "loginToOwnServer") {
		attemptConnectionToServer(sf::IpAddress::getLocalAddress(), getLocalServerTcpPort());
	}
	
	str = pages[2]->getMessageForClient();
	if(str == "startGame") {
		sendTcpMessage("startGame");
	}
	else if(str == "logoutOfOwnServer") {
		disconnect();
	}
	
	str = pages[4]->getMessageForClient();
	if(str == "logout") {
		disconnect();
	}
	
	str = pages[5]->getMessageForClient();
	if(str != "") {
		sendUdpMessage(str);
	}

	
	int stage = getConnectionState();
	for(int i=0; i<pages.size(); i++)
		pages[i]->connectionStage = stage;
	return pages[currentPage]->update();
}

void Client::tcpMessageReceived(std::string message, long timeStamp) {
	if(message.length() > 10 && message.substr(0, 10) == "startGame:")
		currentPage = 5;
	return pages[currentPage]->tcpMessageReceived(message, timeStamp);
}

void Client::udpMessageReceived(std::string message, long timeStamp) {
	return pages[currentPage]->udpMessageReceived(message, timeStamp);
}

std::vector<std::string> Client::split(std::string str, char delim) {
	std::vector<std::string> elems;
	std::string item;
	while(true) {
		int index = str.find(delim);
		if(index == -1) {
			elems.push_back(str);
			return elems;
		}
		elems.push_back(str.substr(0, index));
		if(index+1 == str.length())
			return elems;
		str = str.substr(index+1);
	}
}
