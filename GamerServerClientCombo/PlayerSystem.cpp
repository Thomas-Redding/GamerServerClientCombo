//
//  PlayerSystem.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/17/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "PlayerSystem.hpp"

void PlayerSystem::update(Entities *entities, InputState *inputStates, long deltaTime, int avatarId) {
	if(inputStates->up)
		entities->players[avatarId].y -= deltaTime/4;
	if(inputStates->down)
		entities->players[avatarId].y += deltaTime/4;
	if(inputStates->left)
		entities->players[avatarId].x -= deltaTime/4;
	if(inputStates->right)
		entities->players[avatarId].x += deltaTime/4;
}
