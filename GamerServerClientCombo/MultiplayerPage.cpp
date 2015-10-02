//
//  MultiplayerPage.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/2/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "MultiplayerPage.hpp"

MultiplayerPage::MultiplayerPage(int *currentPageNumber, sf::RenderWindow *w, sf::Font *myFont) : Page(currentPageNumber, w, myFont), backButton(window, font, "Back", 0, 0, 200, 50), serverButton(window, font, "Server", 100, 100, 200, 50), clientButton(window, font, "Client", 100, 200, 200, 50) {
	// todo
}

bool MultiplayerPage::mousePressed(sf::Mouse::Button button, int x, int y) {
	backButton.mousePressed(button, x, y);
	serverButton.mousePressed(button, x, y);
	clientButton.mousePressed(button, x, y);
	return true;
}

bool MultiplayerPage::mouseReleased(sf::Mouse::Button button, int x, int y) {
	if(backButton.mouseReleased(button, x, y))
		*pageNum = 0;
	if(serverButton.mouseReleased(button, x, y))
		*pageNum = 2;
	if(clientButton.mouseReleased(button, x, y))
		*pageNum = 3;
	return true;
}

bool MultiplayerPage::textEntered(sf::Uint32 character) {
	return true;
}

bool MultiplayerPage::draw() {
	backButton.draw();
	serverButton.draw();
	clientButton.draw();
	return true;
}
