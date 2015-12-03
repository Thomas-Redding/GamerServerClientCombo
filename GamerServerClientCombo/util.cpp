//
//  utility.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/18/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "util.hpp"

std::vector<std::string> util::split(std::string str, char delim) {
	std::vector<std::string> elems;
	std::string item;
	while(true) {
		size_t index = str.find(delim);
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

double util::rayLineIntersect(double theta, double x1, double y1, double x2, double y2) {
	double sin = std::sin(theta);
	double cos = std::cos(theta);
	if((x1 == 0 && y1 == 0) || (x2 == 0 && y2 == 0)) {
		std::cout << 0;
		return 0;
	}
	else if((y2-y1)*cos == (x2-x1)*sin) {
		// line is parallel to ray
		double phi = std::atan2(y2, x2);
		if(phi == theta) {
			if(x1 == 0) {
				std::cout << std::fmin(y1, y2);
				return std::fmin(y1, y2); // ray and line are both horizontal
			}
			else {
				if(x1 < x2) {
					std::cout << std::sqrt(x1*x1+y1*y1);
					return std::sqrt(x1*x1+y1*y1);
				}
				else {
					std::cout << std::sqrt(x2*x2+y2*y2);
					return std::sqrt(x2*x2+y2*y2);
				}
			}
		}
		else
			return -1;
	}
	else {
		// line is not parallel to ray
		double r = (y1*(x2-x1)-x1*(y2-y1))/((x2-x1)*sin+(y2-y1)*cos);
		if(r < 0)
			return -1;
		else
			return r;
	}
}

bool util::isPointOnLine(double x, double y, double x1, double y1, double x2, double y2) {
	if(x1 == x2) {
		if(y1 == y2)
			return x == x1 && y == y1; // point
		else
			return x == x1; // vertical line
	}
	else if(y1 == y2)
		return y == y1; // horizontal line
	else {
		// non-vertical, non-horizontal line
		double tx = (x-x1)/(x2-x1);
		double ty = (y-y1)/(y2-y1);
		return tx == ty;
	}
}

bool util::isPointOnSegment(double x, double y, double x1, double y1, double x2, double y2) {
	if(isPointOnLine(x, y, x1, y1, x2, y2)) {
		double r1 = x1*x1+y1*y1;
		double r2 = x2*x2+y2*y2;
		double r = x*x+y*y;
		return isBetween(r, r1, r2);
	}
	else
		return false;
}

bool util::rayCircleIntersect(double theta, double x, double y, double r) {
	double cos = std::cos(theta);
	double sin = std::sin(theta);
	double t = cos*x + sin*y;
	double minDistSquared = (cos*t-x)*(cos*t-x) + (sin*t-y)*(sin*t-y);
	return minDistSquared < r*r;
}

inline bool util::isBetween(double x, double a, double b) {
	return (a < x && x < b) || (b < x && x < a);
}

double util::raySegmentIntersect(double theta, double x1, double y1, double x2, double y2) {
	double answer = rayLineIntersect(theta, x1, y1, x2, y2);
	if(answer > -1) {
		double x = std::cos(theta) * answer;
		double y = std::sin(theta) * answer;
		if(isPointOnSegment(x, y, x1, y1, x2, y2))
			return x*x+y*y;
		else
			return -1;
	}
	else
		return -1;
}

// Line Segment Intersect fcn
util::IntersectAnswer util:: segmentIntersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {

    int yslope1 = y2 - y1;
    int xslope1 = x2 - x1;
    int yslope2 = y4 - y3;
    int xslope2 = x4 - x3;
    IntersectAnswer rtn;
    rtn.didIntersect = false;
    
    //if parallel lines, false
    if((xslope1 == xslope2) && (yslope1 == yslope2)){
        return rtn;
    }
    //need case for when segments overlap but don't intersect 
    
    double s = ((((x3-x1)*(y2-y1))+((x2-x1)*(y1-y3)))/(((x2-x1)*(y4-y3))-((x4-x3)*(y2-y1))));
    double t = ((xslope2*s) + x3 - x1)/xslope1;
    
    if((s <= 1 && s >= 0) && (t <= 1 && t >= 0)){
        rtn.x = (xslope2*s) + x3;
        rtn.y = (yslope2*s) + y3;
        rtn.didIntersect = true;
        return rtn;
    } else {
        return rtn;
    }
}
