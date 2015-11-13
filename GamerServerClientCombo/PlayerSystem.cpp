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
	double distanceToNearestHit = INFINITY; // infinity
	for(int i=0; i<entities->map.walls.size(); i++) {
		Wall &wall = entities->map.walls[i];
		util::Pair answer = util::segmentIntersect(me->x, me->y, x, y, wall.x1, wall.y1, wall.x2, wall.y2);
		double dist = (answer.x - me->x)*(answer.x - me->x) + (answer.y - me->y)*(answer.y - me->y);
		if(answer.didIntersect && dist < distanceToNearestHit) {
			distanceToNearestHit = dist;
		}
	}
	
	for(int i=0; i<entities->players.size(); i++) {
		if(&entities->players[i] != me) {
			Player *they = &entities->players[i];
			bool didHit = util::rayCircleIntersect(theta, they->x - me->x, they->y - me->y, they->health);
			if(didHit) {
				double distToThey = (they->x - me->x) * (they->x - me->x) + (they->y - me->y) * (they->y - me->y);
				if(distToThey < distanceToNearestHit) {
					they->health -= 10;
					if(they->health < 0)
						they->health = 0;
				}
			}
		}
	}
}

