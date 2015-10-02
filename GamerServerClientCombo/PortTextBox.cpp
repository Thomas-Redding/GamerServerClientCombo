//
//  PortTextBox.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/2/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "PortTextBox.hpp"

PortTextBox::PortTextBox(sf::RenderWindow *w, sf::Font *myFont, std::string label, float x, float y, float width, float height) : TextBox(w, myFont, label, x, y, width, height) {
}

bool PortTextBox::textEntered(sf::Uint32 character) {
	if(!isInFocus)
		return false;
	if(character == 10)
		return true;
	else if(character == 8)
		str = str.substr(0, str.length()-1);
	else if(48 <= character && character <= 57 && str.length() < 5)
		str += character;
	text.setString(str);
	return false;
}
