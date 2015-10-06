//
//  GameClient.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/6/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "GameClient.hpp"

GameClient::GameClient(int *currentPageNumber, sf::RenderWindow *w, sf::Font *myFont) : Page(currentPageNumber, w, myFont), view(w) {
	entities.push_back(Entities());
}

bool GameClient::mousePressed(sf::Mouse::Button button, int x, int y) {
	return true;
}

bool GameClient::mouseReleased(sf::Mouse::Button button, int x, int y) {
	return true;
}

bool GameClient::textEntered(sf::Uint32 character) {
	return true;
}

bool GameClient::update() {
	systemsHandler.update(&entities[0]);
	return true;
}

bool GameClient::draw() {
	view.draw();
	return true;
}
