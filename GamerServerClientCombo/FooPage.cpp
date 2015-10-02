//
//  FooPage.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/1/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "FooPage.hpp"

FooPage::FooPage(int *currentPageNumber, sf::RenderWindow *w, sf::Font *myFont) : Page(currentPageNumber, w, myFont), fooButton(window, font, "home", 100, 100, 200, 50) {
	// todo
}

bool FooPage::mousePressed(sf::Mouse::Button button, int x, int y) {
	fooButton.mousePressed(button, x, y);
	return true;
}

bool FooPage::mouseReleased(sf::Mouse::Button button, int x, int y) {
	if(fooButton.mouseReleased(button, x, y))
		*pageNum = 0;
	return true;
}

bool FooPage::draw() {
	fooButton.draw();
	return true;
}