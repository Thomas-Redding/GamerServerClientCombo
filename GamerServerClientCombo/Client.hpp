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

/*
 METHODS TO NEVER CALL OR IMPLEMENT
 void applicationIsClosing()
 void networkUpdate()
 
 NETWORK METHODS
 void attemptConnectionToServer(sf::IpAddress serverIpAddress, unsigned short serverPort)
 
 unsigned short getLocalServerTcpPort() - get the TCP port of the server on your machine; this is useful in conjunction with attemptConnectionToServer()
 
 int getConnectionState() - returns an integer between negative one and positive 3 (inclusive) indicating the state of our connection with the server:
    * 0 = no connection established
    * 1 = connection being established
    * 2 = connection established
    * 3 = received tcp port from server
    * -1 = connection failed

 void sendTcpMessage(std::string message)
 void sendUdpMessage(std::string message)
 
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
 */

class Client : public NetworkClient {
public:
    Client(sf::RenderWindow &myWindow, ServerCommunicator &com);
    
    bool keyPressed(sf::Keyboard::Key keyCode);
    bool keyReleased(sf::Keyboard::Key keyCode);
    bool mouseMoved(int x, int y);
    bool mousePressed(sf::Mouse::Button button, int x, int y);
    bool mouseReleased(sf::Mouse::Button button, int x, int y);
    bool mouseWheeled(int delta, int x, int y);
    bool resized(unsigned int width, unsigned int height);
    bool textEntered(sf::Uint32 character);
    
    bool draw(); // do all drawing here
    bool update(); // do all thinking here - drawing will be ignored
    
    void connectionStateChanged(int oldState, int newState);
    void tcpMessageReceived(std::string message);
    void udpMessageReceived(std::string message);
private:
    sf::RenderWindow &window;
    sf::Font font;
    sf::Text serverTcpPortText;
};

#endif /* Client_cpp */
