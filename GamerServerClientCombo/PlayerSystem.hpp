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
#include <iostream>

#include "Entities.hpp"
#include "InputState.hpp"
#include "util.hpp"

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
	/*
	 * @param entities - current state of the world
	 * @param avatarId - id of the shooter
	 * @param x - x position of crosshairs
	 * @param y - y position of crosshairs
	 */
	void shoot(Entities *entities, Player *me, double x, double y);
};


#endif /* PlayerSystem_cpp */
