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
	 * @param me - pointer to the shooter
	 * @param x - x position of crosshairs
	 * @param y - y position of crosshairs
	 */
	void shoot(Entities *entities, Player *me, double x, double y);
	
	/*
	 * @param entities - Entities object
	 * @param me - pointer to the shooter
	 * @param dx - x-component of movement vector
	 * @param dy - y-component of movement vector
	 */
	void move(Entities *entities, Player *me, double dx, double dy);
};


#endif /* PlayerSystem_cpp */
