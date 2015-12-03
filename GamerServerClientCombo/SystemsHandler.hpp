//
//  SystemsHandler.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/6/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef SystemsHandler_cpp
#define SystemsHandler_cpp

#include <fstream>
#include <deque>
#include <string>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "ResourcePath.hpp"

#include "SoldierSystem.hpp"
#include "util.hpp"

/*
 Methods to be implemented:
 - entitiesToString()
 - entitiesFromString()
 - inputStateToString()
 - inputStateFromString()
 - clearInputState()
 */

class SystemsHandler {
public:
	SystemsHandler(bool isServerSide);
	
	/*
	 * Called at beginning of game
	 * @param entities - struct to be edited to have starting conditions
	 */
	void setupEntities(Entities *entities, std::string launchDetails);
	
	/*
	 * Apply the given InputState-history to the world from startTime to endTime
	 * @param entities - struct to be updated with history of InputStates
	 * @param inputStates - queue of inputStates going backwards in time
	 * @param startTime - time at which simulation should start
	 * @param endtime - time at which simulation should end
	 * @param avatarId - id of avatar for whom the inputStates describe
	 */
	void update(Entities *entities, std::deque<InputState> *inputStates, long startTime, long endTime, int avatarId);
	
	/*
	 * Lossless compression of the given entities into a string - indended for the given ip address (see entitiesFromString() ).
	 * @param entities - Entities to be compressed
	 * @param ip - IpAddress that the string is intended for
	 */
	std::string entitiesToString(Entities *entities, sf::IpAddress ip);
	
	/*
	 * Lossless decompression from a string into an Entities object (see entitiesToString() )
	 * The only exception is that the Map can be ignored
	 * @param entities - entities that results should be written to
	 * @param std::string - string to decompress from
	 */
	void entitiesFromString(Entities *entities, std::string str);
	
	/*
	 * Compress given InputState object into string
	 * @param inputStates - InputState object to be compressed
	 */
	std::string inputStateToString(InputState *inputState);
	
	/*
	 * Decompresses the given string into the given InputState object
	 * @param inputState - InputState object to be decompressed
	 * @param str - string to be decompressed
	 */
    void inputStateFromString(InputState *inputState, std::string str);
private:
	bool isServer;
	SoldierSystem soldierSystem;
	
	/*
	 * @inputStates - computes the deltaTime of each inputState
	 * @startTime - time the simulation starts
	 * @endTime - time the simulation ends
	 */
	std::vector<float> inputStateWeights(std::deque<InputState> *inputStates, long startTime, long endTime);
	
	/*
	 * computes the amount of overlap that two 1-dimensional lines have
	 * assumes that a < b and c < d
	 * @param a - starting point of first line
	 * @param b - ending point of first line
	 * @param c - starting point of second line
	 * @param d - ending point of second line
	 */
	long lineIntersect(long a, long b, long c, long d);
};

#endif /* SystemsHandler_cpp */
