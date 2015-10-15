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
	void setupEntities(Entities *entities);
	bool keyPressed(sf::Keyboard::Key keyCode);
	bool keyReleased(sf::Keyboard::Key keyCode);
	bool mouseMoved(int x, int y);
	bool mousePressed(sf::Mouse::Button button, int x, int y);
	bool mouseReleased(sf::Mouse::Button button, int x, int y);
	bool mouseWheeled(int delta, int x, int y);
	bool textEntered(sf::Uint32 character);
	bool otherEvent(sf::Event event);
	void closing();
	bool update(Entities *entities, std::deque<InputState> *inputStates, long startTime, long endTime);
	std::string entitiesToString(Entities *entities, sf::IpAddress ip);
	void entitiesFromString(Entities *entities, std::string str);
	std::string inputStateToString(InputState *inputStates);
    void applyInputState(InputState *inputState, std::string str);
    void clearInputState(InputState *inputState);
private:
	bool isServer;
    std::vector<std::string> split(const std::string &s, char delim);
	std::vector<float> inputStateWeights(std::deque<InputState> *inputStates, long startTime, long endTime);
	long lineIntersect(long a, long b, long c, long d);
	void miniUpate(Entities *entities, InputState *inputStates, long deltaTime);
};

#endif /* SystemsHandler_cpp */
