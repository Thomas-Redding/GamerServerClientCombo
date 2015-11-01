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
	
	/*
	 * Called once per frame to draw to the screen.
	 * @param entities - current state of the world for us to draw
	 * @return boolean indicating whether the application should quit or not
	 */
	bool draw(Entities *entities);
	
	/*
	 * Called whenever the window is resized.
	 * @param width - the window's new width
	 * @param height - the window's new height
	 * @return boolean indicating whether the application should quit or not
	 */
	bool resized(unsigned int width, unsigned int height);
	double screenX = 0;
	double screenY = 0;
	double screenScale = 1;
private:
	sf::RenderWindow *window;
};

#endif /* View_cpp */
