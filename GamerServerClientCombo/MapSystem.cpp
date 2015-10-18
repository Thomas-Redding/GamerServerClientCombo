//
//  MapSystem.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/17/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "MapSystem.hpp"

void MapSystem::loadFromString(Map* map, std::string str) {
	clearMap(map);
	
	std::vector<std::string> sections = util::split(str, ':');
	if(sections.size() >= 2) {
		addWallsToMap(map, sections[0]);
		addWaypointsToMap(map, sections[1]);
	}
	else {
		std::cout << "Poorly Formatted Map File";
	}
}

void MapSystem::clearMap(Map* map) {
	map->walls.clear();
}

void MapSystem::addWallsToMap(Map* map, std::string str) {
	std::vector<std::string> walls = util::split(str, ';');
	for(int i=0; i<walls.size(); i++) {
		std::vector<std::string> wall = util::split(walls[i], ',');
		if(wall.size() >= 4) {
			map->walls.push_back(Wall());
			map->walls[map->walls.size()-1].x1 = stof(wall[0]);
			map->walls[map->walls.size()-1].y1 = stof(wall[1]);
			map->walls[map->walls.size()-1].x2 = stof(wall[2]);
			map->walls[map->walls.size()-1].y2 = stof(wall[3]);
		}
	}
}

void MapSystem::addWaypointsToMap(Map* map, std::string str) {
	std::vector<std::string> waypoints = util::split(str, ';');
	for(int i=0; i<waypoints.size(); i++) {
		std::vector<std::string> waypoint = util::split(waypoints[i], ',');
		if(waypoint.size() >= 2) {
			map->waypoints.push_back(Waypoint());
			map->waypoints[map->waypoints.size()-1].x = stof(waypoint[0]);
			map->waypoints[map->waypoints.size()-1].y = stof(waypoint[1]);
		}
	}
}
