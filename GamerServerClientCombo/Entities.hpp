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
#include "Player.hpp"
#include "Map.hpp"
#include "BotSoldier.hpp"

struct Entities {
	long timeStamp;
	std::vector<Player> players;
	std::vector<BotSoldier> botSoldiers;
	Map map;
};

#endif /* Entities_cpp */
