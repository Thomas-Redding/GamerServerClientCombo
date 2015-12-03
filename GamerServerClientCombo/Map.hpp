//
//  Map.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 12/3/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "util.hpp"
#include "Wall.hpp"
#include "Waypoint.hpp"

class Map {
public:
	std::vector<Wall> walls;
	std::vector<Waypoint> waypoints;
	void loadFromString(std::string str);
private:
	void clearMap();
	void addWallsToMap(std::string str);
	void addWaypointsToMap(std::string str);
};


#endif /* Map_hpp */
