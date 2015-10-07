//
//  GameServer.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef GameServer_cpp
#define GameServer_cpp

#include <deque>
#include "Entities.hpp"
#include "InputState.hpp"
#include "SystemsHandler.hpp"

class GameServer {
public:
	void start(std::vector<sf::IpAddress> myPlayers);
	void update();
private:
	std::deque<Entities> entities;
	std::deque<std::vector<InputState>> inputStates;
	SystemsHandler systemsHandler;
	long getTime();
	std::vector<sf::IpAddress> players;
};

#endif /* GameServer_cpp */
