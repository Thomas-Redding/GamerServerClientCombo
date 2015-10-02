//
//  ClientPage.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/2/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "ClientPage.hpp"

ClientPage::ClientPage(int *currentPageNumber, sf::RenderWindow *w, sf::Font *myFont) : Page(currentPageNumber, w, myFont), backButton(window, font, "back", 0, 0, 200, 50), connectButton(window, font, "Connect", 100, 200, 200, 50), ipTextBox(window, font, "", 100, 300, 200, 50), portTextBox(window, font, "", 100, 400, 200, 50) {
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
	connectButton.mouseReleased(button, x, y);
	return true;
}

bool ClientPage::textEntered(sf::Uint32 character) {
	ipTextBox.textEntered(character);
	portTextBox.textEntered(character);
	return true;
}

bool ClientPage::draw() {
	backButton.draw();
	connectButton.draw();
	ipTextBox.draw();
	portTextBox.draw();
	return true;
}
