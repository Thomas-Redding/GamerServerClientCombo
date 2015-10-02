//
//  MultiplayerPage.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/2/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "MultiplayerPage.hpp"

MultiplayerPage::MultiplayerPage(int *currentPageNumber, sf::RenderWindow *w, sf::Font *myFont) : Page(currentPageNumber, w, myFont), fooButton(window, font, "home", 100, 100, 200, 50), textBox(window, font, "home", 100, 300, 200, 50) {
	// todo
}

bool MultiplayerPage::mousePressed(sf::Mouse::Button button, int x, int y) {
	fooButton.mousePressed(button, x, y);
	textBox.mousePressed(button, x, y);
	return true;
}

bool MultiplayerPage::mouseReleased(sf::Mouse::Button button, int x, int y) {
	if(fooButton.mouseReleased(button, x, y))
		*pageNum = 0;
	return true;
}

bool MultiplayerPage::textEntered(sf::Uint32 character) {
	textBox.textEntered(character);
	return true;
}

bool MultiplayerPage::draw() {
	fooButton.draw();
	textBox.draw();
	return true;
}
