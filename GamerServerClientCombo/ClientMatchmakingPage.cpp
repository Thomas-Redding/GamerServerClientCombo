//
//  ClientMatchmakingPage.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/2/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "ClientMatchmakingPage.hpp"

ClientMatchmakingPage::ClientMatchmakingPage(int *currentPageNumber, sf::RenderWindow *w, sf::Font *myFont) : Page(currentPageNumber, w, myFont), backButton(window, font, "Log Out", 0, 0, 200, 50) {
}

bool ClientMatchmakingPage::mousePressed(sf::Mouse::Button button, int x, int y) {
	backButton.mousePressed(button, x, y);
	return true;
}

bool ClientMatchmakingPage::mouseReleased(sf::Mouse::Button button, int x, int y) {
	bool wasClicked = backButton.mouseReleased(button, x, y);
	if(wasClicked) {
		*pageNum = 1;
		sendMessageToClient("logout");
	}
	return true;
}

bool ClientMatchmakingPage::textEntered(sf::Uint32 character) {
	return true;
}

bool ClientMatchmakingPage::draw() {
	backButton.draw();
	return true;
}

