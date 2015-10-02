//
//  PortTextBox.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/2/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef PortTextBox_cpp
#define PortTextBox_cpp

#include "TextBox.hpp"

class PortTextBox : public TextBox {
public:
	PortTextBox(sf::RenderWindow *w, sf::Font *myFont, std::string label, float x, float y, float width, float height);
	bool textEntered(sf::Uint32 character);
};

#endif /* PortTextBox_cpp */
