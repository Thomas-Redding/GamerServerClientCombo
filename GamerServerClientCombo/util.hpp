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
    struct IntersectAnswer {
        bool didIntersect;
        double x;
        double y;
    };
    
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
	 * @param theta - angle between ray and x-axis
	 * @param x1 - x position of first end of line segment
	 * @param y1 - y position of first end of line segment
	 * @param x2 - x position of second end of line segment
	 * @param y2 - y position of second end of line segment
	 * returns the distance between the origin and the point of intersection; returns -1 if no intersection
	 */
	double rayLineIntersect(double theta, double x1, double y1, double x2, double y2);
	
	/*
	 * @param x - x position of point
	 * @param y - x position of point
	 * @param x1 - x position of first end of line segment
	 * @param y1 - y position of first end of line segment
	 * @param x2 - x position of second end of line segment
	 * @param y2 - y position of second end of line segment
	 */
	bool isPointOnLine(double x, double y, double x1, double y1, double x2, double y2);
	
	/*
	 * @param x - x position of point
	 * @param y - x position of point
	 * @param x1 - x position of first end of line segment
	 * @param y1 - y position of first end of line segment
	 * @param x2 - x position of second end of line segment
	 * @param y2 - y position of second end of line segment
	 */
	bool isPointOnSegment(double x, double y, double x1, double y1, double x2, double y2);
	
	inline bool isBetween(double x, double a, double b);
	
	/*
	 * @param theta - angle between ray and x-axis
	 * @param x1 - x position of first end of line segment
	 * @param y1 - y position of first end of line segment
	 * @param x2 - x position of second end of line segment
	 * @param y2 - y position of second end of line segment
	 * returns the distance between the origin and the point of intersection; returns -1 if no intersection
	 */
	double raySegmentIntersect(double theta, double x1, double y1, double x2, double y2);
	
	/*
	 * determines whether a ray intersects a circle
	 * @param theta - angle between ray and x-axis
	 * @param x - x position of circle
	 * @param y - y position of circlce
	 * @param r - radius of circle
	 * @return distance to intersection, if no intersection return -1
	 */
	bool rayCircleIntersect(double theta, double x, double y, double r);
    
    /*
     * Line Segment Intersect fcn
     * @param x1 - x position of first end of first segment
     * @param y1 - y position of first end of first segment
     * @param x2 - x position of second end of first segment
     * @param y2 - y position of second end of first segment
     * @param x3 - x position of first end of second segment
     * @param y3 - y position of first end of second segment
     * @param x4 - x position of second end of second segment
     * @param y4 - y position of second end of second segment
     * @return struct indicating (1) whether the segments intersect and (2) the position of the intersection
     */
    IntersectAnswer segmentIntersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
}

#endif /* utility_cpp */
