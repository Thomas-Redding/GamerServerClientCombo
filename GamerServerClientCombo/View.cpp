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
	for(int i=0; i<entities->soldiers.size(); i++) {
		sf::RectangleShape rect;
		rect.setSize(sf::Vector2f(100, 100));
		rect.setPosition(entities->soldiers[i].x, entities->soldiers[i].y);
		rect.setFillColor(sf::Color::Red);
		window->draw(rect);
	}
	return true;
}

bool View::resized(unsigned int width, unsigned int height) {
	return true;
}
