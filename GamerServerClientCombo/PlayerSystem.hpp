//
//  PlayerSystem.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/17/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef PlayerSystem_cpp
#define PlayerSystem_cpp

#include <stdio.h>
#include <cmath>
#include <iostream>

#include "Entities.hpp"
#include "InputState.hpp"

class PlayerSystem {
public:
	/*
	 * applies the given InputState to the given Entities with the given deltaTime
	 * @param entities - Entities object
	 * @param inputState - InputState object to simulate
	 * @param deltaTime - milliseconds to simulate
	 * @param avatarId - which avatar's inputs are being updated?
	 */
	void update(Entities *entities, InputState *inputState, long deltaTime, int avatarId);
private:
	void shoot(Entities *entities, int avatarId, double x, double y);
	double lineSegmentIntersect(double a, double b, double c, double d, double e, double f, double g, double h);
	inline bool isPointOnLine(double x, double y, double a, double b, double c, double d);
};


#endif /* PlayerSystem_cpp */
