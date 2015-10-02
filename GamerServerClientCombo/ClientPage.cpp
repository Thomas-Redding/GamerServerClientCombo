//
//  ClientPage.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/2/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "ClientPage.hpp"

ClientPage::ClientPage(int *currentPageNumber, sf::RenderWindow *w, sf::Font *myFont) : Page(currentPageNumber, w, myFont), backButton(window, font, "Back", 0, 0, 200, 50), connectButton(window, font, "Connect", 100, 200, 200, 50), ipTextBox(window, font, "", 100, 300, 200, 50), portTextBox(window, font, "", 100, 400, 200, 50) {
	connectionStageLabel = sf::Text("yolo", *font, 30);
	connectionStageLabel.setPosition(100, 500);
}

bool ClientPage::mousePressed(sf::Mouse::Button button, int x, int y) {
	backButton.mousePressed(button, x, y);
	connectButton.mousePressed(button, x, y);
	ipTextBox.mousePressed(button, x, y);
	portTextBox.mousePressed(button, x, y);
	return true;
}

bool ClientPage::mouseReleased(sf::Mouse::Button button, int x, int y) {
	bool wasClicked = backButton.mouseReleased(button, x, y);
	if(wasClicked)
		*pageNum = 1;
	
	wasClicked = connectButton.mouseReleased(button, x, y);
	if(wasClicked)
		submitForm();
	return true;
}

bool ClientPage::textEntered(sf::Uint32 character) {
	bool didReturn = ipTextBox.textEntered(character);
	didReturn = didReturn || portTextBox.textEntered(character);
	if(didReturn)
		submitForm();
	return true;
}

bool ClientPage::update() {
	if(connectionStage == 3)
		*pageNum = 4;
	return true;
}

bool ClientPage::draw() {
	backButton.draw();
	connectButton.draw();
	ipTextBox.draw();
	portTextBox.draw();
	
	connectionStageLabel.setString(std::to_string(connectionStage));
	window->draw(connectionStageLabel);
	return true;
}

void ClientPage::submitForm() {
	sendMessageToClient(ipTextBox.getString() + ":" + portTextBox.getString());
}
