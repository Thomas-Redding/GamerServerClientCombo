//
//  GameClient.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/6/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "GameClient.hpp"

GameClient::GameClient(int *currentPageNumber, sf::RenderWindow *w, sf::Font *myFont) : Page(currentPageNumber, w, myFont) {
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

bool GameClient::draw() {
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(100, 100));
	rect.setPosition(0, 0);
	rect.setFillColor(sf::Color::Red);
	window->draw(rect);
	return true;
}
