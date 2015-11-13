//
//  PlayerSystem.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/17/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "PlayerSystem.hpp"

void PlayerSystem::update(Entities *entities, InputState *inputState, long deltaTime, int avatarId) {
	Player *me;
	int i;
	for(i=0; i<entities->players.size(); i++) {
		if(entities->players[i].id == avatarId) {
			me = &entities->players[avatarId];
			break;
		}
	}
	
	me->x += inputState->moveX * deltaTime * 0.4;
	me->y += inputState->moveY * deltaTime * 0.4;
	
	if(inputState->mouseClicked)
		shoot(entities, me, inputState->mouseX, inputState->mouseY);
}

void PlayerSystem::shoot(Entities *entities, Player *me, double x, double y) {
	double theta = atan2(y - me->y, x - me->x);
	for(int i=0; i<entities->players.size(); i++) {
		if(&entities->players[i] != me) {
			Player *they = &entities->players[i];
			bool didHit = util::rayCircleIntersect(theta, they->x - me->x, they->y - me->y, they->health);
			if(didHit)
				they->health -= 10;
			if(they->health < 0)
				they->health = 0;
		}
	}
}

