//
//  Map.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/17/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef Map_cpp
#define Map_cpp

#include <stdio.h>
#include <vector>

#include "Wall.hpp"

struct Map {
	std::vector<Wall> walls;
};

#endif /* Map_cpp */
