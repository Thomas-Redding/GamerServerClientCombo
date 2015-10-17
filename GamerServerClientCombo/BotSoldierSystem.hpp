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
	void update(Entities *entities, long deltaTime, int botSoldierId);
};

#endif /* BotSoldierSystem_cpp */
