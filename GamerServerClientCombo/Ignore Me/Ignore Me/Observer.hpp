//
//  Observer.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/2/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef Observer_cpp
#define Observer_cpp

#include <stdio.h>
#include <sstream>

class Observer {
public:
	virtual std::string giveMeMessage(std::string str);
};

#endif /* Observer_cpp */
