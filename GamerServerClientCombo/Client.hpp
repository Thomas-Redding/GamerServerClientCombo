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

class Client : public NetworkClient {
public:
    // constructor(s)
    Client(sf::RenderWindow &myWindow, ServerCommunicator &com);
    
    // user input events - returning anything but 0 will cause the application to close
    bool keyPressed(sf::Keyboard::Key keyCode);
    bool keyReleased(sf::Keyboard::Key keyCode);
    bool mouseMoved(int x, int y);
    bool mousePressed(sf::Mouse::Button button, int x, int y);
    bool mouseReleased(sf::Mouse::Button button, int x, int y);
    bool mouseWheeled(int delta, int x, int y);
    
    // per-frame cals - returning anything but 0 will cause the application to close
    bool draw(); // do all drawing here
    bool update(); // do all thinking here - drawing will be ignored
    
    void connectionStateChanged(int oldState, int newState);
private:
    sf::RenderWindow &window; // all drawing uses this reference to the game window
    sf::Font font;
    
    sf::Text serverTcpPortText;
    sf::Text serverLocalIpAddress;
    sf::Text serverGlobalIpAddress;
    sf::Text messageText;
    
    int messageNumber = 0;
};

#endif /* Client_cpp */
