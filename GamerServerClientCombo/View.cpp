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
	for(int i=0; i<entities->players.size(); i++) {
		sf::CircleShape circ;
		circ.setRadius(100);
		circ.setPosition(entities->players[i].x-100, entities->players[i].y-100);
		circ.setFillColor(sf::Color::Red);
		window->draw(circ);
	}
	
	for(int i=0; i<entities->followers.size(); i++) {
		sf::CircleShape circ;
		circ.setRadius(100);
		circ.setPosition(entities->followers[i].x-100, entities->followers[i].y-100);
		circ.setFillColor(sf::Color::Blue);
		window->draw(circ);
	}
	
	for(int i=0; i<entities->map.waypoints.size(); i++) {
		sf::CircleShape circ;
		circ.setRadius(10);
		circ.setPosition(entities->map.waypoints[i].x-10, entities->map.waypoints[i].y-10);
		circ.setFillColor(sf::Color::Green);
		window->draw(circ);
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
