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
#include <iostream>

#include "Entities.hpp"

class View {
public:
	View(sf::RenderWindow *myWindow);
	bool draw(Entities *entities);
	bool resized(unsigned int width, unsigned int height);
	double screenX = 0;
	double screenY = 0;
	double screenScale = 1;
private:
	sf::RenderWindow *window;
};

#endif /* View_cpp */
