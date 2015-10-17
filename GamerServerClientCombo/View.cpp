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
	
	for(int i=0; i<entities->map.walls.size(); i++) {
		sf::VertexArray lines(sf::LinesStrip, 2);
		lines[0].position = sf::Vector2f(entities->map.walls[i].x1, entities->map.walls[i].y1);
		lines[1].position = sf::Vector2f(entities->map.walls[i].x2, entities->map.walls[i].y2);
		window->draw(lines);
	}
	
	return true;
}

bool View::resized(unsigned int width, unsigned int height) {
	return true;
}
