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
};


#endif /* PlayerSystem_cpp */
