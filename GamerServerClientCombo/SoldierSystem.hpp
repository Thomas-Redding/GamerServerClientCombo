//
//  SoldierSystem.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 12/3/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef SoldierSystem_hpp
#define SoldierSystem_hpp

#include <stdio.h>
#include <iostream>

#include "Entities.hpp"
#include "InputState.hpp"
#include "util.hpp"

class SoldierSystem {
public:
	/*
	 * applies the given InputState to the given Entities with the given deltaTime
	 * @param entities - Entities object
	 * @param inputState - InputState object to simulate
	 * @param deltaTime - milliseconds to simulate
	 * @param avatarId - which avatar's inputs are being updated?
	 */
	void update(Entities *entities, long deltaTime, int id);
};

#endif /* SoldierSystem_hpp */
