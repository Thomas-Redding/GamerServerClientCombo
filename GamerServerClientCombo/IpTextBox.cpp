//
//  IpTextBox.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/2/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "IpTextBox.hpp"

IpTextBox::IpTextBox(sf::RenderWindow *w, sf::Font *myFont, std::string label, float x, float y, float width, float height) : TextBox(w, myFont, label, x, y, width, height) {
}

bool IpTextBox::textEntered(sf::Uint32 character) {
	if(!isInFocus)
		return false;
	if(character == 10)
		return true;
	else if(character == 8)
		str = str.substr(0, str.length()-1);
	else if(character == 46) {
		// period
		int numberOfPeriods = 0;
		for(int i=0; i<str.length(); i++) {
			if(str.at(i) == '.')
				numberOfPeriods++;
		}
		if(numberOfPeriods < 3)
			str += character;
	}
	else if(48 <= character && character <= 57) {
		// numeral
		int numeralsInFront = 0;
		for(long i=str.length()-1; i>=0; i--) {
			if(str.at(i) != '.')
				numeralsInFront++;
			else
				break;
		}
		if(numeralsInFront < 3)
			str += character;
	}
	text.setString(str);
	return false;
}
