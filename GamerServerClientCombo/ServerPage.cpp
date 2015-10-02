//
//  ServerPage.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/2/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "ServerPage.hpp"

ServerPage::ServerPage(int *currentPageNumber, sf::RenderWindow *w, sf::Font *myFont, unsigned short port) : Page(currentPageNumber, w, myFont), backButton(window, font, "Back", 0, 0, 200, 50) {
	serverPort = port;
	portLabel = sf::Text(std::to_string(port), *font, 30);
	ipLabel = sf::Text(sf::IpAddress::getLocalAddress().toString(), *font, 30);
}

bool ServerPage::mousePressed(sf::Mouse::Button button, int x, int y) {
	backButton.mousePressed(button, x, y);
	return true;
}

bool ServerPage::mouseReleased(sf::Mouse::Button button, int x, int y) {
	if(backButton.mouseReleased(button, x, y))
		*pageNum = 1;
	return true;
}

bool ServerPage::textEntered(sf::Uint32 character) {
	return true;
}

bool ServerPage::draw() {
	sf::Vector2u windowSize = window->getSize();
	
	float textWidth = portLabel.getGlobalBounds().width;
	float textHeight = portLabel.getGlobalBounds().height;
	portLabel.setPosition(windowSize.x/2-textWidth/2, windowSize.y/2-textHeight/2 - 20);
	
	textWidth = ipLabel.getGlobalBounds().width;
	textHeight = ipLabel.getGlobalBounds().height;
	ipLabel.setPosition(windowSize.x/2-textWidth/2, windowSize.y/2-textHeight/2 + 20);
	
	backButton.draw();
	window->draw(portLabel);
	window->draw(ipLabel);
	
	return true;
}
