//
//  utility.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/18/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef utility_cpp
#define utility_cpp

#include <vector>
#include <string>
#include <cmath>
#include <iostream>

namespace util {
	/*
	 * splits a string into a vector of substrings based on a character
	 * Ex: split("alpha-beta-gamma", '-') --> ["alpha", "beta", "gamma"]
	 * @param str - string to be split
	 * @param delim - character to split with
	 * @return vector of substrings
	*/
	std::vector<std::string> split(std::string str, char delim);
	
	/*
	 * determines whether a ray intersects with a line segment
	 * if no intersection, returns -1; else returns distance of intersection point from origin
	 */
	double rayLineIntersect(double theta, double x1, double y1, double x2, double y2);
	
	/*
	 * determines whether a ray intersects a circle
	 * if no intersection, returns -1; else returns distance to intersection
	 */
	bool rayCircleIntersect(double theta, double x, double y, double r);
    
    /*
     * Line Segment Intersect fcn
     */
    bool segmentIntersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
}

#endif /* utility_cpp */
