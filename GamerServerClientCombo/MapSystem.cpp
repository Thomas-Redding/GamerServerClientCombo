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
	
	std::vector<std::string> sections = split(str, ':');
	std::vector<std::string> walls = split(sections[0], ';');
	for(int i=0; i<walls.size(); i++) {
		std::vector<std::string> wall = split(walls[i], ',');
		if(wall.size() >= 4) {
			map->walls.push_back(Wall());
			map->walls[map->walls.size()-1].x1 = stof(wall[0]);
			map->walls[map->walls.size()-1].y1 = stof(wall[1]);
			map->walls[map->walls.size()-1].x2 = stof(wall[2]);
			map->walls[map->walls.size()-1].y2 = stof(wall[3]);
		}
	}
}

void MapSystem::clearMap(Map* map) {
	map->walls.clear();
}

std::vector<std::string> MapSystem::split(std::string str, char delim) {
	std::vector<std::string> elems;
	std::string item;
	while(true) {
		int index = str.find(delim);
		if(index == -1) {
			elems.push_back(str);
			return elems;
		}
		elems.push_back(str.substr(0, index));
		if(index+1 == str.length())
			return elems;
		str = str.substr(index+1);
	}
}
