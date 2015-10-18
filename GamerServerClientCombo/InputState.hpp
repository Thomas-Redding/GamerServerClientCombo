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
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	double mouseX = 0;
	double mouseY = 0;
	bool mouseClicked = false;
	bool mouseDown = false;
};

#endif /* InputState_cpp */
