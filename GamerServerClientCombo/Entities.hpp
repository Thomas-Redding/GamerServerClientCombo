//
//  Entities.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/6/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef Entities_cpp
#define Entities_cpp

#include <stdio.h>
#include <vector>
#include "Team.hpp"


struct Entities {
	long timeStamp;
	std::vector<Team> teams;
	std::vector<Commander> commanders;
	std::vector<Soldier> soldiers;
	Map map;
};

#endif /* Entities_cpp */
