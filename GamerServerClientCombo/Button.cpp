//
//  Button.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/1/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "Button.hpp"

Button::Button(sf::RenderWindow *w, sf::Font *myFont, std::string label, float x, float y, float width, float height) {
	window = w;
	font = myFont;
	text = sf::Text(label, *font, 30);
	background = sf::RectangleShape(sf::Vector2f(0, 0));
	setBounds(x, y, width, height);
}

void Button::mousePressed(sf::Mouse::Button button, int x, int y) {
	if(background.getPosition().x < x && x < background.getPosition().x+background.getSize().x && background.getPosition().y < y && y < background.getPosition().y+background.getSize().y)
		isButtonPressed = true;
}

bool Button::mouseReleased(sf::Mouse::Button button, int x, int y) {
	if(isButtonPressed) {
		if(background.getPosition().x < x && x < background.getPosition().x+background.getSize().x && background.getPosition().y < y && y < background.getPosition().y+background.getSize().y) {
			isButtonPressed = false;
			wasButtonClickedThisFrame = true;
			return true;
		}
	}
	isButtonPressed = false;
	return false;
}

void Button::draw() {
	if(isButtonPressed || wasButtonClickedThisFrame) {
		text.setColor(sf::Color::Green);
		background.setFillColor(sf::Color::Red);
	}
	else {
		text.setColor(sf::Color::Red);
		background.setFillColor(sf::Color::Green);
	}
	window->draw(background);
	window->draw(text);
	wasButtonClickedThisFrame = false;
}

void Button::setBounds(float x, float y, float w, float h) {
	background.setPosition(x, y);
	background.setSize(sf::Vector2f(w, h));
	text.setCharacterSize(h/2);
	float textWidth = text.getGlobalBounds().width;
	float textHeight = text.getGlobalBounds().height;
	text.setPosition(x+w/2-textWidth/2, y+h/3-textHeight/2);
}