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
		Player *me = &entities->players[i];
		sf::CircleShape circ;
		circ.setRadius(me->health * screenScale);
		circ.setPosition((me->x - screenX - me->health) * screenScale, (me->y - screenY - me->health) * screenScale);
		circ.setFillColor(sf::Color::Red);
		window->draw(circ);
	}
	
	for(int i=0; i<entities->botSoldiers.size(); i++) {
		BotSoldier *me = &entities->botSoldiers[i];
		sf::CircleShape circ;
		circ.setRadius(100 * screenScale);
		circ.setPosition((me->x - screenX - 100) * screenScale, (me->y - screenY - 100) * screenScale);
		circ.setFillColor(sf::Color::Blue);
		window->draw(circ);
	}
	
	for(int i=0; i<entities->map.waypoints.size(); i++) {
		sf::CircleShape circ;
		circ.setRadius(10);
		circ.setPosition((entities->map.waypoints[i].x - screenX)*screenScale - 10, (entities->map.waypoints[i].y - screenY)*screenScale - 10);
		circ.setFillColor(sf::Color::Green);
		window->draw(circ);
	}
	
	for(int i=0; i<entities->map.walls.size(); i++) {
		sf::VertexArray lines(sf::LinesStrip, 2);
		lines[0].position = sf::Vector2f((entities->map.walls[i].x1 - screenX) * screenScale, (entities->map.walls[i].y1 - screenY) * screenScale);
		lines[1].position = sf::Vector2f((entities->map.walls[i].x2 - screenX) * screenScale, (entities->map.walls[i].y2 - screenY) * screenScale);
		window->draw(lines);
	}
	
	return true;
}

bool View::resized(unsigned int width, unsigned int height) {
	return true;
}
