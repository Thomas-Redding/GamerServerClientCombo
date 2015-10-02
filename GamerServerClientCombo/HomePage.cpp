//
//  HomePage.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/1/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "HomePage.hpp"

HomePage::HomePage(int *currentPageNumber, sf::RenderWindow *w, sf::Font *myFont) : Page(currentPageNumber, w, myFont), fooButton(window, font, "foo", 100, 100, 200, 50) {
	// todo
}

bool HomePage::mousePressed(sf::Mouse::Button button, int x, int y) {
	fooButton.mousePressed(button, x, y);
	return true;
}

bool HomePage::mouseReleased(sf::Mouse::Button button, int x, int y) {
	if(fooButton.mouseReleased(button, x, y))
		*pageNum = 1;
	return true;
}

bool HomePage::draw() {
	fooButton.draw();
	return true;
}