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
#include "ClientServerCommunicator.hpp"

/*
 NOTE: If you are a casual user, just focus on the Client and Server classes (i.e. ignore this one).
 
 The NetworkClient class is intended to simplify interactions with the (1) Server class and (2) SFML's events.
 */

class NetworkClient {
public:
	NetworkClient(ServerCommunicator& com, ClientServerCommunicator &comB);
	~NetworkClient();
	void applicationIsClosing();

	void attemptConnectionToServer(sf::IpAddress serverIpAddress, unsigned short serverPort);
	void disconnect();
	
	void networkUpdate();
	
	/*
	 0 = no connection established
	 1 = connection being established
	 2 = connection established
	 3 = received tcp port from server
	 -1 = connection failed
	 */
	int getConnectionState();
	
	void sendTcpMessage(std::string message);
	virtual void tcpMessageReceived(std::string message, long timeStamp) {};
	virtual void udpMessageReceived(std::string message, long timeStamp) {};
	void sendUdpMessage(std::string message);
	
	unsigned short getLocalServerTcpPort();
	
	bool keyPressed(sf::Keyboard::Key keyCode) {return true;};
	bool keyReleased(sf::Keyboard::Key keyCode) {return true;};
	bool mouseMoved(int x, int y) {return true;};
	bool mousePressed(sf::Mouse::Button button, int x, int y) {return true;};
	bool mouseReleased(sf::Mouse::Button button, int x, int y) {return true;};
	bool mouseWheeled(int delta, int x, int y) {return true;};
	bool resized(unsigned int width, unsigned int height) {return true;};
	bool textEntered(sf::Uint32 character) {return true;};
	bool otherEvent(sf::Event event) {return true;};
	bool draw() {return true;};
	bool update() {return true;};
	void closing() {};
	long getTime();
	long getServerTime();
private:
	int connectionState = 0;
	sf::TcpSocket tcpSocket;
	sf::UdpSocket udpSocket;
	unsigned short tcpPortOfServer;
	ServerCommunicator &communicator;
	ClientServerCommunicator &offlineCommunicator;
	sf::IpAddress ipAddressOfServer;
	unsigned short udpPortOfServer = 0;
	void sendOwnTcpServerMessageToQuit();
	long timeLastPingSent = 0;
	std::vector<long> estimatedClockDifferences;
	signed long estimateClockDiff();
	long serverToClientTime(long serverTime);
};

#endif /* NetworkClient_cpp */
