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
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "NetworkClient.hpp"

class Client {
public:
    // constructor(s)
    Client(sf::RenderWindow &myWindow, ServerCommunicator &com);
    void applicationIsClosing(unsigned short localTcpPort);
    
    // user input events - returning anything but 0 will cause the application to close
    int keyPressed(sf::Keyboard::Key keyCode);
    int keyReleased(sf::Keyboard::Key keyCode);
    int mouseMoved(int x, int y);
    int mousePressed(sf::Mouse::Button button, int x, int y);
    int mouseReleased(sf::Mouse::Button button, int x, int y);
    int mouseWheeled(int delta, int x, int y);
    
    // per-frame cals - returning anything but 0 will cause the application to close
    int draw(); // do all drawing here
    int update(); // do all thinking here - drawing will be ignored
private:
    sf::RenderWindow &window; // all drawing uses this reference to the game window
    sf::Font font;
    sf::Text text;
    NetworkClient networkClient;
    int messageNumber = 0;
};

#endif /* Client_cpp */
