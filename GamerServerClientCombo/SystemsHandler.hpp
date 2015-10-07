//
//  SystemsHandler.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/6/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef SystemsHandler_cpp
#define SystemsHandler_cpp

#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Entities.hpp"
#include "InputState.hpp"

class SystemsHandler {
public:
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
	bool update(Entities *entities, std::vector<InputState> *inputStates, long deltaTime);
private:
	// todo
};

#endif /* SystemsHandler_cpp */
