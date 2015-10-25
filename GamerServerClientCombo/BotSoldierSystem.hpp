//
//  BotSoldierSystem.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/17/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef BotSoldierSystem_cpp
#define BotSoldierSystem_cpp

#include <cmath>

#include "Entities.hpp"

class BotSoldierSystem {
public:
	/*
	 * Function called once per frame during which all actions of the given BotSoldier should occur
	 * @param entities - current world state
	 * @param deltaTime - time over which actions take place
	 * @param botSoldierId - id of soldier who is acting
	 */
	void update(Entities *entities, long deltaTime, int botSoldierId);
};

#endif /* BotSoldierSystem_cpp */
