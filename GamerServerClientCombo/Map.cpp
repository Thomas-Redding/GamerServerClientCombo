//
//  Map.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 12/3/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "Map.hpp"

void Map::loadFromString(std::string str) {
	clearMap();
	std::vector<std::string> sections = util::split(str, ':');
	if(sections.size() >= 2) {
		addWallsToMap(sections[0]);
		addWaypointsToMap(sections[1]);
	}
	else {
		std::cout << "Poorly Formatted Map File";
	}
}

void Map::clearMap() {
	walls.clear();
}

void Map::addWallsToMap(std::string str) {
	std::vector<std::string> wallsString = util::split(str, ';');
	for(int i=0; i<wallsString.size(); i++) {
		std::vector<std::string> wallString = util::split(wallsString[i], ',');
		if(wallString.size() >= 4) {
			walls.push_back(Wall());
			walls[walls.size()-1].x1 = stof(wallString[0]);
			walls[walls.size()-1].y1 = stof(wallString[1]);
			walls[walls.size()-1].x2 = stof(wallString[2]);
			walls[walls.size()-1].y2 = stof(wallString[3]);
		}
	}
}

void Map::addWaypointsToMap(std::string str) {
	std::vector<std::string> waypointsString = util::split(str, ';');
	for(int i=0; i<waypoints.size(); i++) {
		std::vector<std::string> waypointString = util::split(waypointsString[i], ',');
		if(waypointString.size() >= 2) {
			waypoints.push_back(Waypoint());
			waypoints[waypoints.size()-1].x = stof(waypointString[0]);
			waypoints[waypoints.size()-1].y = stof(waypointString[1]);
		}
	}
}
