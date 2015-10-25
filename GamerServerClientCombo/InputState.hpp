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
	
	// key states
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	
	// mouse's position in world-coordinates, not screen- or window-coordinates
	double mouseX = 0;
	double mouseY = 0;
	
	// mouse states
	bool mouseClicked = false;
	bool mouseDown = false;
};

#endif /* InputState_cpp */
