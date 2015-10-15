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
#include "Soldier.hpp"

struct Entities {
	long timeStamp;
	std::vector<Soldier> soldiers;
};

#endif /* Entities_cpp */
