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
	
	if(inputState->mouseClicked)
		shoot(entities, avatarId, inputState->mouseX, inputState->mouseY);
	
	if(inputState->mouseDown && me->health > 10)
		me->health -= deltaTime/10;
}

void PlayerSystem::shoot(Entities *entities, int avatarId, double x, double y) {
	
}

double PlayerSystem::lineSegmentIntersect(double a, double b, double c, double d, double e, double f, double g, double h) {
	if((d-b)*(g-e) == (h-f)*(c-a)) {
		// both lines are parallel
		if(a == c && b == d) {
			// first line is a point
		}
		else {
			if(isPointOnLine(e, f, a, b, c, d)) {
				// lines are aligned
			}
			else
				return false;
		}
	}
	else {
		// lines are not parallel
		double s = ((h-f)*(g-e) - (h-f)*(c-a)) / ((d-b)*(g-e) - (h-f)*(c-a));
		if(e == g) {
			// second line is vertical
			if(h == f) {
				// second line is a point
				if((c-a)*s+a == e && (d-b)*s+b == f)
					return true;
				else
					return false;
			}
			else {
				// second line is not a point
				double t = ((d-b)*s+(b-f)) / (h-f);
				if(0 < t < 1)
					return s;
				else
					return -1;
			}
		}
		else {
			// second line is not vertical
			double t = ((c-a)*s+(a-e)) / (g-e);
			if(0 < t < 1)
				return s;
			else
				return -1;
		}
	}
	return 0;
}

inline bool PlayerSystem::isPointOnLine(double x, double y, double a, double b, double c, double d) {
	return (d-b)*(x-a) == (y-b)*(c-a);
}




