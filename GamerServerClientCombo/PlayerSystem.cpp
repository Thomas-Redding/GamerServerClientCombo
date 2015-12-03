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
	for(unsigned int i=0; i<entities->players.size(); i++) {
		if(entities->players[i].id == avatarId) {
			me = &entities->players[avatarId];
			break;
		}
	}
	
	move(entities, me, inputState->moveX * deltaTime * 0.4, inputState->moveY * deltaTime * 0.4);
	
	if(inputState->mouseClicked)
		shoot(entities, me, inputState->mouseX, inputState->mouseY);
}

void PlayerSystem::move(Entities *entities, Player *me, double dx, double dy) {
	double theta = atan2(dy, dx);
	double len = dx * dx + dy *dy;
	if(len == 0)
		return;
	double minDist = INFINITY;
	double closestWall = -1;
	for(int i=0; i<entities->map.walls.size(); i++) {
		Wall *wall = &entities->map.walls[i];
		double dist = util::raySegmentIntersect(theta, wall->x1 - me->x, wall->y1 - me->y, wall->x2 - me->x, wall->y2 - me->y);
		if(dist != -1 && dist < minDist) {
			minDist = dist;
			closestWall = i;
		}
	}
	
	if(minDist < me->health) {
		// we are inside a wall
	}
	else if(minDist < me->health + len) {
		// we hit a wall
	}
	else {
		// we don't hit a wall
		me->x += dx;
		me->y += dy;
	}
}

void PlayerSystem::shoot(Entities *entities, Player *me, double x, double y) {
	double theta = atan2(y - me->y, x - me->x);
	double distanceToNearestHit = INFINITY; // infinity
	for(int i=0; i<entities->map.walls.size(); i++) {
		Wall *wall = &entities->map.walls[i];
		util::Pair answer = util::segmentIntersect(me->x, me->y, x, y, wall->x1, wall->y1, wall->x2, wall->y2);
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

