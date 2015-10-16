//
//  GameClient.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/6/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef GameClient_cpp
#define GameClient_cpp

#include <deque>
#include <iostream>

#include "Page.hpp"
#include "InputState.hpp"
#include "Entities.hpp"
#include "SystemsHandler.hpp"
#include "View.hpp"

/*
 During a frame, the methods are called in the following order:
 1. event methods
 2. update()
 3. draw()
*/

class GameClient : public Page {
public:
	GameClient(int *currentPageNumber, sf::RenderWindow *w, sf::Font *myFont);
	bool keyPressed(sf::Keyboard::Key keyCode);
	bool keyReleased(sf::Keyboard::Key keyCode);
	bool mouseMoved(int x, int y);
	bool mousePressed(sf::Mouse::Button button, int x, int y);
	bool mouseReleased(sf::Mouse::Button button, int x, int y);
	bool mouseWheeled(int delta, int x, int y);
	bool resized(unsigned int width, unsigned int height);
	bool textEntered(sf::Uint32 character);
	bool otherEvent(sf::Event event);
	void closing();
	bool draw();
	bool update();
	void tcpMessageReceived(std::string message, long timeStamp);
	void udpMessageReceived(std::string message, long timeStamp);
private:
	InputState currentInputState;
	std::vector<std::deque<InputState>> inputStates;
	std::deque<Entities> entities;
	std::deque<Entities> serverEntities;
	std::deque<long> serverEntitiesTimes;
	View view;
	int myAvatarId = -1;
	SystemsHandler systemsHandler;
	long timeOfLastFrame;
	//void clearInputState(InputState *InputState, long time);
	long getTime();
	std::vector<std::string> split(const std::string &s, char delim);
};

#endif /* GameClient_cpp */
