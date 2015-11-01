//
//  InputState.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/6/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef InputState_cpp
#define InputState_cpp

#include <stdio.h>

struct InputState {
	long timeStamp;
	
	// unit-vector indicating direction of motion
	double moveX;
	double moveY;
	
	// mouse's position in world-coordinates, not screen- or window-coordinates
	double mouseX = 0;
	double mouseY = 0;
	
	// mouse states
	bool mouseClicked = false;
	bool mouseDown = false;
};

#endif /* InputState_cpp */
