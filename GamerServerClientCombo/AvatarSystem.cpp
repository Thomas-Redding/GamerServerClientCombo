//
//  AvatarSystem.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/17/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "AvatarSystem.hpp"

void AvatarSystem::update(Entities *entities, InputState *inputStates, long deltaTime, int avatarId) {
	if(inputStates->up)
		entities->soldiers[avatarId].y -= deltaTime/4;
	if(inputStates->down)
		entities->soldiers[avatarId].y += deltaTime/4;
	if(inputStates->left)
		entities->soldiers[avatarId].x -= deltaTime/4;
	if(inputStates->right)
		entities->soldiers[avatarId].x += deltaTime/4;
}
