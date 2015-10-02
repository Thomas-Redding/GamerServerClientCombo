//
//  Page.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 10/1/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef Page_cpp
#define Page_cpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class Page {
public:
	Page(int *currentPageNumber, sf::RenderWindow *w, sf::Font *myFont);
	virtual bool keyPressed(sf::Keyboard::Key keyCode) {return true;};
	virtual bool keyReleased(sf::Keyboard::Key keyCode) {return true;};
	virtual bool mouseMoved(int x, int y) {return true;};
	virtual bool mousePressed(sf::Mouse::Button button, int x, int y) {return true;};
	virtual bool mouseReleased(sf::Mouse::Button button, int x, int y) {return true;};
	virtual bool mouseWheeled(int delta, int x, int y) {return true;};
	virtual bool resized(unsigned int width, unsigned int height) {return true;};
	virtual bool textEntered(sf::Uint32 character) {return true;};
	virtual bool otherEvent(sf::Event event) {return true;};
	virtual void closing() {};
	virtual bool draw() {return true;};
	virtual bool update() {return true;};
	virtual void tcpMessageReceived(std::string message, long timeStamp) {};
	virtual void udpMessageReceived(std::string message, long timeStamp) {};
protected:
	int *pageNum;
	sf::RenderWindow *window;
	sf::Font *font;
};

#endif /* Page_cpp */
