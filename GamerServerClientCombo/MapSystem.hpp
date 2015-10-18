//
//  MapSystem.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/17/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef MapSystem_cpp
#define MapSystem_cpp

#include <stdio.h>
#include <sstream>
#include <iostream>

#include "Map.hpp"
#include "Utility.hpp"

class MapSystem {
public:
	/*
	 * Loads a map based on a given string (usually the contents of a map-file).
	 * The format of this string is detailed at the bottom of this file
	 * @param map - the map to be written to
	 * @param str - string to load
	 */
	void loadFromString(Map* map, std::string str);
private:
	void clearMap(Map* map);
	void addWallsToMap(Map* map, std::string str);
	void addWaypointsToMap(Map* map, std::string str);
};

/*
 * The file consists of sections separated by colons.
 * Section I: Walls
 *     - contains a list of walls separated by semicolons
 *     - each wall takes the form {wall1.x1},{wall1.y1},{wall1.x2},{wall1.y2}
 *     - ex: 0,40,20,80;12,31,60,90
 * Section II: Waypoints
 *     - contains a list of waypoints separated by semicolons
 *     - each waypoint takes the form {waypoint.x},{waypoint.y}
 *     - ex: 0,40;20,80;12,31;60,90
 */

#endif /* MapSystem_cpp */
