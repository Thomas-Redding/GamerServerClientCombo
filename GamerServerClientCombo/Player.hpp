//
//  Player.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/17/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef Player_cpp
#define Player_cpp

#include <stdio.h>

struct Player {
	int id;
	double x;
	double y;
	double health = 100;
	std::vector<int> followerIds;
};

#endif /* Player_cpp */
