//
//  networkClock.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 11/8/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "networkClock.hpp"

extern std::vector<long> estimatedClockDifferences;

long networkClock::getLocalTime() {
	return std::chrono::duration_cast< std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

signed long networkClock::estimateClockDiff() {
	if(estimatedClockDifferences.size() > 0) {
		std::vector<long> vect = estimatedClockDifferences;
		std::sort(vect.begin(), vect.begin()+vect.size());
		unsigned long middleIndex = vect.size()/2;
		return vect[middleIndex];
	}
	else
		return 0;
}

long networkClock::getServerTime() {
	return getLocalTime() + estimateClockDiff();
}


long networkClock::serverToClientTime(long serverTime) {
	return serverTime - estimateClockDiff();
}
