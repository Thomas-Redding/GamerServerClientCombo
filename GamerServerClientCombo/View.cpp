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

bool View::draw(Entities *entities) {
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(entities->boxWidth, entities->boxHeight));
	rect.setPosition(entities->boxX, entities->boxY);
	rect.setFillColor(sf::Color::Red);
	window->draw(rect);
	return true;
}

bool View::resized(unsigned int width, unsigned int height) {
	return true;
}
