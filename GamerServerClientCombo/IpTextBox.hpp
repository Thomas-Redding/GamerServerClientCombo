//
//  IpTextBox.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/2/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef IpTextBox_cpp
#define IpTextBox_cpp

#include "TextBox.hpp"

class IpTextBox : public TextBox {
public:
	IpTextBox(sf::RenderWindow *w, sf::Font *myFont, std::string label, float x, float y, float width, float height);
	bool textEntered(sf::Uint32 character);
};

#endif /* IpTextBox_cpp */
