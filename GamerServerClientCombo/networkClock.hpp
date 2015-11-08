//
//  networkClock.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 11/8/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef networkClock_cpp
#define networkClock_cpp

#include <stdio.h>
#include <chrono>
#include <vector>

namespace networkClock {
	long getLocalTime();
	signed long estimateClockDiff();
	long getServerTime();
	long serverToClientTime(long serverTime);
};


#endif /* networkClock_cpp */
