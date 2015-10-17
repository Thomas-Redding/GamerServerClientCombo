//
//  AvatarSystem.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/17/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef AvatarSystem_cpp
#define AvatarSystem_cpp

#include <stdio.h>

#include "Entities.hpp"
#include "InputState.hpp"

class AvatarSystem {
public:
	/*
	 * applies the given InputState to the given Entities with the given deltaTime
	 * @param entities - Entities object
	 * @param inputState - InputState object to simulate
	 * @param deltaTime - milliseconds to simulate
	 * @param avatarId - which avatar's inputs are being updated?
	 */
	void update(Entities *entities, InputState *inputStates, long deltaTime, int avatarId);
};

#endif /* AvatarSystem_cpp */
