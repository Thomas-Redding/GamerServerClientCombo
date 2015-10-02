//
//  Button.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/1/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef Button_cpp
#define Button_cpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class Button {
public:
	Button(sf::RenderWindow *w, sf::Font *myFont, std::string label, float x, float y, float width, float height);
	void mousePressed(sf::Mouse::Button button, int x, int y);
	bool mouseReleased(sf::Mouse::Button button, int x, int y); // returns "true" if button was clicked
	void draw();
	void setBounds(float x, float y, float w, float h);
private:
	bool isButtonPressed = false;
	bool wasButtonClickedThisFrame = false;
	sf::RenderWindow *window;
	sf::Font *font;
	sf::RectangleShape background;
	sf::Text text;
};

#endif /* Button_cpp */
