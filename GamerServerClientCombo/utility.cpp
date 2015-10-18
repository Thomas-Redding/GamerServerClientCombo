//
//  utility.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/18/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "utility.hpp"

std::vector<std::string> utility::split(std::string str, char delim) {
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

double utility::rayLineIntersect(double theta, double x1, double y1, double x2, double y2) {
	double sin = std::sin(theta);
	double cos = std::cos(theta);
	if((x1 == 0 && y1 == 0) || (x2 == 0 && y2 == 0))
		return 0;
	else if((y2-y1)*cos == (x2-x1)*sin) {
		// line is parallel to ray
		double phi = std::atan2(y2, x2);
		if(phi == theta) {
			if(x1 == 0)
				return std::fmin(y1, y2); // ray and line are both horizontal
			else {
				if(x1 < x2)
					return std::sqrt(x1*x1+y1*y1);
				else
					return std::sqrt(x2*x2+y2*y2);
			}
		}
		else
			return -1;
	}
	else {
		// line is not parallel to ray
		double t = (x1*sin-y1*cos)/((y2-y1)*cos - (x2-x1)*sin);
		double r = ((x2-x1)*t+x1)/cos;
		if(r < 0)
			return -1;
		else
			return r;
	}
}

bool utility::rayCircleIntersect(double theta, double x, double y, double r) {
	double cos = std::cos(theta);
	double sin = std::sin(theta);
	double t = cos*x + sin*y;
	double minDistSquared = (cos*t-x)*(cos*t-x) + (sin*t-y)*(sin*t-y);
	return minDistSquared < r*r;
}


