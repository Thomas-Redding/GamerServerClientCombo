//
//  View.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/6/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef View_cpp
#define View_cpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class View {
public:
	View(sf::RenderWindow *myWindow);
	void draw();
private:
	sf::RenderWindow *window;
};

#endif /* View_cpp */
