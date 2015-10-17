//
//  BotSoldier.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/17/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef BotSoldier_cpp
#define BotSoldier_cpp

#include <stdio.h>

struct BotSoldier {
	int id;
	double x;
	double y;
	double goalX = 1000;
	double goalY = 0;
};

#endif /* BotSoldier_cpp */
