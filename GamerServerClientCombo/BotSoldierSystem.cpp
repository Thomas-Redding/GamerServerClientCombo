//
//  BotSoldierSystem.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/17/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "BotSoldierSystem.hpp"

void BotSoldierSystem::update(Entities *entities, long deltaTime, int botSoldierId) {
	BotSoldier *me = &entities->botSoldiers[botSoldierId];
	double deltaX = me->goalX - me->x;
	double deltaY = me->goalY - me->y;
	double len = std::sqrt(deltaX*deltaX + deltaY*deltaY);
	if(len < deltaTime) {
		me->x = me->goalX;
		me->y = me->goalY;
	}
	else {
		deltaX /= len;
		deltaY /= len;
		me->x += deltaX * deltaTime;
		me->y += deltaY * deltaTime;
	}
}
