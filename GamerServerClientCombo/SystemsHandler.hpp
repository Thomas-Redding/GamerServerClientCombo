//
//  SystemsHandler.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/6/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef SystemsHandler_cpp
#define SystemsHandler_cpp

#include <iostream>
#include <sstream>
#include <deque>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Entities.hpp"
#include "InputState.hpp"
#include <assert.h>

class SystemsHandler {
public:
	SystemsHandler(bool isServerSide);
	
	/*
	 * Called at beginning of game
	 * @param entities - struct to be edited to have starting conditions
	 */
	void setupEntities(Entities *entities);
	
	/*
	 * Apply the given InputState-history to the world from startTime to endTime
	 * @param entities - struct to be updated with history of InputStates
	 * @param inputStates - queue of inputStates going backwards in time
	 * @param startTime - time at which simulation should start
	 * @param endtime - time at which simulation should end
	 */
	void update(Entities *entities, std::deque<InputState> *inputStates, long startTime, long endTime);
	
	/*
	 * Lossless compression of the given entities into a string - indended for the given ip address (see entitiesFromString() ).
	 * @param entities - Entities to be compressed
	 * @param ip - IpAddress that the string is intended for
	 */
	std::string entitiesToString(Entities *entities, sf::IpAddress ip);
	
	/*
	 * Lossless decompression from a string into an Entities object (see entitiesToString() )
	 * @param entities - entities that results should be written to
	 * @param std::string - string to decompress from
	 */
	void entitiesFromString(Entities *entities, std::string str);
	
	/*
	 * Compress given InputState object into string
	 * @param inputStates - InputState object to be compressed
	 */
	std::string inputStateToString(InputState *inputStates);
	
	/*
	 * Decompresses the given string into the given InputState object
	 * @param inputState - InputState object to be decompressed
	 * @param str - string to be decompressed
	 */
    void applyInputState(InputState *inputState, std::string str);
	
	/*
	 * Sets the given InputState object to default values
	 * @param inputState - InputState object to be cleared
	 */
    void clearInputState(InputState *inputState);
private:
	bool isServer;
	
	/*
	 * splits a string into a vector of strings based on some deliminating character
	 * @param s - string to be split
	 * @param delim - deliminator to split along
	 */
    std::vector<std::string> split(const std::string &s, char delim);
	
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
	
	/*
	 * applies the given InputState to the given Entities with the given deltaTime
	 * @param entities - Entities object
	 * @param inputState - InputState object to simulate
	 * @param deltaTime - milliseconds to simulate
	 */
	void miniUpdate(Entities *entities, InputState *inputStates, long deltaTime);
};

#endif /* SystemsHandler_cpp */
