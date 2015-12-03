//
//  Team.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 12/3/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef Team_hpp
#define Team_hpp

#include <stdio.h>
#include <vector>

#include "Map.hpp"

struct Team;
struct Commander;
struct Soldier;

struct Team {
	unsigned int id;
	std::vector<Commander*> commanders;
	Map map;
	std::vector<Soldier*> seenSoldiers;
};

struct Commander {
	unsigned int id;
	bool isPlayer;
	Team *team;
	std::vector<Soldier*> soldiers;
};

struct Soldier {
	unsigned int id;
	bool isPlayer;
	Commander *commander;
	double x, y, health, goalX, goalY;
};

#endif /* Team_hpp */
