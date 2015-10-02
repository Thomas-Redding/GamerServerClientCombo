//
//  Page.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/1/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "Page.hpp"

Page::Page(int *currentPageNumber, sf::RenderWindow *w, sf::Font *myFont) {
	font = myFont;
	window = w;
	pageNum = currentPageNumber;
}
