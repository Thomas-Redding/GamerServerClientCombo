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
	double len = std::sqrt(deltaX*deltaX + deltaY*deltaY);
	deltaX *= deltaTime/len/4;
	deltaY *= deltaTime/len/4;
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
}
