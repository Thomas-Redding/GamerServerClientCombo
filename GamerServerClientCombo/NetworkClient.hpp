//
//  NetworkClient.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef NetworkClient_cpp
#define NetworkClient_cpp

#include <stdio.h>
#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "ServerCommunicator.hpp"

/*
 NOTE: If you are a casual user, just focus on the Client and Server classes (i.e. ignore this one).
 
 The NetworkClient class is intended to simplify interactions with the (1) Server class and (2) SFML's events.
 */

class NetworkClient {
public:
    NetworkClient(ServerCommunicator& com);
    ~NetworkClient();
    void applicationIsClosing();

    void attemptConnectionToServer(sf::IpAddress serverIpAddress, unsigned short serverPort);
    
    void networkUpdate();
    void startFrame();
    void endFrame();
    
    /*
     0 = no connection established
     1 = connection being established
     2 = connection established
     3 = received tcp port from server
     -1 = connection failed
     */
    int getConnectionState();
    
    void sendTcpMessage(std::string message);
    virtual void tcpMessageReceived(std::string message) {};
    virtual void udpMessageReceived(std::string message) {};
    void sendUdpMessage(std::string message);
    
    unsigned short getLocalServerTcpPort();
    
    virtual bool keyPressed(sf::Keyboard::Key keyCode) {};
    virtual bool keyReleased(sf::Keyboard::Key keyCode) {};
    virtual bool mouseMoved(int x, int y) {};
    virtual bool mousePressed(sf::Mouse::Button button, int x, int y) {};
    virtual bool mouseReleased(sf::Mouse::Button button, int x, int y) {};
    virtual bool mouseWheeled(int delta, int x, int y) {};
    virtual bool resized(unsigned int width, unsigned int height) {};
    virtual bool textEntered(sf::Uint32 character) {};
    virtual bool draw() {};
    virtual bool update() {};
    virtual void connectionStateChanged(int oldState, int newState) {};
private:
    int connectionState = 0;
    sf::TcpSocket tcpSocket;
    sf::UdpSocket udpSocket;
    unsigned short tcpPortOfServer;
    ServerCommunicator &communicator;
    sf::IpAddress ipAddressOfServer;
    unsigned short udpPortOfServer = 0;
    void sendOwnTcpServerMessageToQuit();
};

#endif /* NetworkClient_cpp */
