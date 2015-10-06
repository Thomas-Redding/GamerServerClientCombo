//
//  View.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/6/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "View.hpp"

View::View(sf::RenderWindow *myWindow) {
	window = myWindow;
}

void View::draw() {
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(100, 100));
	rect.setPosition(0, 0);
	rect.setFillColor(sf::Color::Red);
	window->draw(rect);
}