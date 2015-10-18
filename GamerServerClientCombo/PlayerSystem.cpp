//
//  PlayerSystem.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/17/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "PlayerSystem.hpp"

void PlayerSystem::update(Entities *entities, InputState *inputState, long deltaTime, int avatarId) {
	Player *me = &entities->players[avatarId];
	double deltaX = inputState->mouseX - me->x;
	double deltaY = inputState->mouseY - me->y;
	double distanceToMouse = std::sqrt(deltaX*deltaX + deltaY*deltaY);
	deltaX *= deltaTime/distanceToMouse/4;
	deltaY *= deltaTime/distanceToMouse/4;
	double distanceToTravel = std::sqrt(deltaX*deltaX + deltaY*deltaY);
	if(distanceToMouse == 0) {
		deltaX = 0;
		deltaY = 0;
	}
	else if(distanceToTravel > distanceToMouse) {
		deltaX *= distanceToMouse/distanceToTravel;
		deltaY *= distanceToMouse/distanceToTravel;
	}
	
	if(inputState->up) {
		me->x += deltaX;
		me->y += deltaY;
	}
	if(inputState->down) {
		me->x -= deltaX;
		me->y -= deltaY;
	}
	if(inputState->left) {
		me->x += deltaY;
		me->y -= deltaX;
	}
	if(inputState->right) {
		me->x -= deltaY;
		me->y += deltaX;
	}
	
	if(inputState->mouseClicked) {
		me->x = inputState->mouseX;
		me->y = inputState->mouseY;
	}
	
	if(inputState->mouseDown && me->health > 10)
		me->health -= deltaTime/10;
}
