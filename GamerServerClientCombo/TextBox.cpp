//
//  TextBox.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/2/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "TextBox.hpp"

TextBox::TextBox(sf::RenderWindow *w, sf::Font *myFont, std::string label, float x, float y, float width, float height) {
	window = w;
	font = myFont;
	str = label;
	text = sf::Text(label, *font, 30);
	background = sf::RectangleShape(sf::Vector2f(0, 0));
	setBounds(x, y, width, height);
	text.setColor(sf::Color::Black);
	background.setFillColor(sf::Color::White);
	background.setOutlineColor(sf::Color::Blue);
}

void TextBox::mousePressed(sf::Mouse::Button button, int x, int y) {
	if(background.getPosition().x < x && x < background.getPosition().x+background.getSize().x && background.getPosition().y < y && y < background.getPosition().y+background.getSize().y) {
		isInFocus = true;
		background.setOutlineThickness(2);
	}
	else {
		isInFocus = false;
		background.setOutlineThickness(0);
	}
}

bool TextBox::textEntered(sf::Uint32 character) {
	if(!isInFocus)
		return false;
	if(character == 10)
		return true;
	else if(character == 8)
		str = str.substr(0, str.length()-1);
	else
		str += character;
	text.setString(str);
	return false;
}

void TextBox::draw() {
	window->draw(background);
	window->draw(text);
}

void TextBox::setBounds(float x, float y, float w, float h) {
	background.setPosition(x, y);
	background.setSize(sf::Vector2f(w, h));
	text.setCharacterSize(h/2);
	float textWidth = text.getGlobalBounds().width;
	float textHeight = text.getGlobalBounds().height;
	text.setPosition(x-textWidth/2+2, y+h/3-textHeight/2);
}
