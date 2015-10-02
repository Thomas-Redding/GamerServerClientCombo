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
	attemptConnectionToServer(sf::IpAddress::getLocalAddress(), getLocalServerTcpPort());
}

bool Client::start() {
	// Load and Set the App's Icon
	sf::Image icon;
	if (!icon.loadFromFile(resourcePath() + "icon.png"))
		return false; // failed to load icon - quit app
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	
	// Load a font
	if(!font.loadFromFile(resourcePath() + "sansation.ttf"))
		return false; // failed to load font - quit app
	
	pages.push_back(new HomePage(&currentPage, &window, &font));
	pages.push_back(new MultiplayerPage(&currentPage, &window, &font));
	pages.push_back(new ServerPage(&currentPage, &window, &font, getLocalServerTcpPort()));
	pages.push_back(new ClientPage(&currentPage, &window, &font));
	
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
	return pages[currentPage]->update();
}

void Client::connectionStateChanged(int oldState, int newState) {
}

void Client::tcpMessageReceived(std::string message, long timeStamp) {
	return pages[currentPage]->tcpMessageReceived(message, timeStamp);
}

void Client::udpMessageReceived(std::string message, long timeStamp) {
	return pages[currentPage]->udpMessageReceived(message, timeStamp);
}
