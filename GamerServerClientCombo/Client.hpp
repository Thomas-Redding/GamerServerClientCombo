//
//  Client.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef Client_cpp
#define Client_cpp

#include <stdio.h>
#include <iostream>
#include "ResourcePath.hpp"
#include "NetworkClient.hpp"
#include "HomePage.hpp"
#include "FooPage.hpp"

/*
 NEVER start a UDP or TCP message with the underscore character. Messages starting with the underscore character are reserved for the NetworkClient and NetworkServer classes.
 
 METHODS TO NEVER CALL OR IMPLEMENT
 void applicationIsClosing()
 void networkUpdate()
 
 NETWORK METHODS
 void attemptConnectionToServer(sf::IpAddress serverIpAddress, unsigned short serverPort)
 
 unsigned short getLocalServerTcpPort() - get the TCP port of the server on your machine; this is useful in conjunction with attemptConnectionToServer()
 
 int getConnectionState() - returns an integer between negative one and positive 3 indicating the state of our connection with the server:
	* 0 = no connection established
	* 1 = connection being established
	* 2 = can send TCP messages
	* 3 = can send UDP messages
	* -1 = connection failed

 void sendTcpMessage(std::string message)
 void sendUdpMessage(std::string message)
 long getTime() - get the current time according to this machine's internal clock
 long getServerTime() - get the current time according to the server's internal clock (this doesn't make a network call but is estimated based on previous messages between the client and server)
 
 EVENT METHODS FOR YOU TO IMPLEMENT - returning "false" causes the application to quit
 void tcpMessageReceived(std::string message)
 void udpMessageReceived(std::string message)
 bool keyPressed(sf::Keyboard::Key keyCode)
 bool keyReleased(sf::Keyboard::Key keyCode)
 bool mouseMoved(int x, int y)
 bool mousePressed(sf::Mouse::Button button, int x, int y)
 bool mouseReleased(sf::Mouse::Button button, int x, int y)
 bool mouseWheeled(int delta, int x, int y)
 bool resized(unsigned int width, unsigned int height)
 bool textEntered(sf::Uint32 character)
 bool draw()
 bool update() - called once per frame prior to draw()
 void connectionStateChanged(int oldState, int newState)
 
 OTHER
bool start() - called at the beginning immediately after the constructor; returning "false" causes the application to quit
 */

class Client : public NetworkClient {
public:
	Client(sf::RenderWindow &myWindow, ServerCommunicator &com);
	bool start();
	/*
	 These methods are triggered by events. It's worth noting that many of these could be emluated in update():
	 * sf::Mouse::getPosition()
	 * sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
	 * window.getSize()
	 * sf::Mouse::isButtonPressed(sf::Mouse::Left)
	*/
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
	
	bool draw(); // do all drawing here
	bool update(); // do all thinking here - drawing will be ignored
	
	void connectionStateChanged(int oldState, int newState);
	void tcpMessageReceived(std::string message, long timeStamp);
	void udpMessageReceived(std::string message, long timeStamp);
private:
	sf::RenderWindow &window;
	sf::Font font;
	
	int currentPage = 0;
	std::vector <Page*> pages;
};

#endif /* Client_cpp */
