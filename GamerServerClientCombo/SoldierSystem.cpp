//
//  SoldierSystem.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 12/3/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "SoldierSystem.hpp"

void SoldierSystem::update(Entities *entities, long deltaTime, int id) {
	Soldier *me;
	for(unsigned int i=0; i<entities->soldiers.size(); i++) {
		if(entities->soldiers[i].id == id) {
			me = &entities->soldiers[i];
			break;
		}
	}
	
	if(me == nullptr)
		return;
	
	// todo
}
