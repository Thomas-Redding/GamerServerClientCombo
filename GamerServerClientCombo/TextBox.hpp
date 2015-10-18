//
//  TextBox.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/2/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef TextBox_cpp
#define TextBox_cpp

#include <stdio.h>
#include <sstream>
#include <SFML/Graphics.hpp>

class TextBox {
public:
	TextBox(sf::RenderWindow *w, sf::Font *myFont, std::string label, float x, float y, float width, float height);
	void mousePressed(sf::Mouse::Button button, int x, int y);
	void draw();
	void setBounds(float x, float y, float w, float h);
	bool textEntered(sf::Uint32 character);
	void setFocus(bool newFocus);
	bool getFocus();
	std::string getString();
protected:
	bool isInFocus = false;
	sf::Text text;
	std::string str;
private:
	sf::RenderWindow *window;
	sf::Font *font;
	sf::RectangleShape background;
};

#endif /* TextBox_cpp */
