//
//  GameClient.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/6/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef GameClient_cpp
#define GameClient_cpp

#include "Page.hpp"
#include "InputState.hpp"
#include "Entities.hpp"
#include "SystemsHandler.hpp"
#include "View.hpp"

class GameClient : public Page {
public:
	GameClient(int *currentPageNumber, sf::RenderWindow *w, sf::Font *myFont);
	bool keyPressed(sf::Keyboard::Key keyCode) {return true;};
	bool keyReleased(sf::Keyboard::Key keyCode) {return true;};
	bool mouseMoved(int x, int y) {return true;};
	bool mousePressed(sf::Mouse::Button button, int x, int y);
	bool mouseReleased(sf::Mouse::Button button, int x, int y);
	bool mouseWheeled(int delta, int x, int y) {return true;};
	bool resized(unsigned int width, unsigned int height) {return true;};
	bool textEntered(sf::Uint32 character);
	bool otherEvent(sf::Event event) {return true;};
	void closing() {};
	bool draw();
	bool update() {return true;};
	void tcpMessageReceived(std::string message, long timeStamp) {};
	void udpMessageReceived(std::string message, long timeStamp) {};
private:
	std::vector<std::vector<InputState>> inputStates;
	std::vector<Entities> entities;
	View view;
	SystemsHandler systemsHandler;
};

#endif /* GameClient_cpp */
