//
//  NetworkClient.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "NetworkClient.hpp"

extern std::vector<long> estimatedClockDifferences;

NetworkClient::NetworkClient(ServerCommunicator& com, ClientServerCommunicator &comB) : communicator(com), offlineCommunicator(comB) {
	tcpSocket.setBlocking(false);
	udpSocket.setBlocking(false);
	udpSocket.bind(sf::Socket::AnyPort);
}

NetworkClient::~NetworkClient() {
	tcpSocket.disconnect();
}

void NetworkClient::applicationIsClosing() {
	sendOwnTcpServerMessageToQuit();
}

void NetworkClient::networkUpdate() {
	// update "connectionStage"
	if(connectionState == 1) {
		if(tcpSocket.getRemoteAddress() != sf::IpAddress::None) {
			// our TCP sockets just connected
			sendTcpMessage("_CONNECT" + std::to_string(udpSocket.getLocalPort()));
			connectionState = 2;
			// now we wait for the server to send us a TCP message giving us its UDP port number
		}
	}
	else if(connectionState == 2) {
		if(tcpSocket.getRemoteAddress() == sf::IpAddress::None) {
			connectionState = -1;
		}
	}
	
	// check for TCP messages
	while(true) {
		sf::Packet packet;
		tcpSocket.receive(packet);
		std::string message = "";
		packet >> message;
		if(message != "") {
			long timeStamp = 0;
			for(int i=0; i<message.size(); i++) {
				if(message.at(i) == '@') {
					std::cout << message << i << "\n";
					char * pEnd;
					timeStamp = strtoull(message.c_str(), &pEnd, 10);
					message = message.substr(i+1);
					break;
				}
			}
			if(message.at(0) == '_') {
				// message is reserved for NetworkClient (Client shouldn't receive this)
				message = message.substr(1);
				if(message.substr(0, 7) == "CONNECT") {
					if(connectionState != 3) {
						connectionState = 3;
					}
					udpPortOfServer = stoi(message.substr(7));
				}
			}
			else
				tcpMessageReceived(message, networkClock::serverToClientTime(timeStamp));
		}
		else
			break;
	}
	
	while(true) {
		std::string message = offlineCommunicator.getTcpMessagesForClient();
		if(message == "")
			break;
		long timeStamp = 0;
		for(int i=0; i<message.size(); i++) {
			if(message.at(i) == '@') {
				timeStamp = stol(message.substr(0, i));
				message = message.substr(i+1);
				break;
			}
		}
		if(message.at(0) == '_') {
			// message is reserved for NetworkClient (Client shouldn't receive this)
			message = message.substr(1);
			if(message.substr(0, 7) == "CONNECT") {
				if(connectionState != 3) {
					connectionState = 3;
				}
				udpPortOfServer = stoi(message.substr(7));
			}
		}
		else
			tcpMessageReceived(message, networkClock::serverToClientTime(timeStamp));
	}
	
	// check for UDP messages
	while(true) {
		char buffer[1024];
		char *begin = buffer;
		char *end = begin + sizeof(buffer);
		std::fill(begin, end, 0);
		std::size_t received = 0;
		sf::IpAddress sender;
		unsigned short port;
		udpSocket.receive(buffer, sizeof(buffer), received, sender, port);
		std::string message = std::string(buffer);
		if(message != "") {
			long timeStamp = 0;
			for(int i=0; i<message.size(); i++) {
				if(message.at(i) == '@') {
					timeStamp = stol(message.substr(0, i));
					message = message.substr(i+1);
					break;
				}
			}
			if(message.at(0) == '_') {
				long currentTime = networkClock::getLocalTime();
				long timeSent = stol(message.substr(8));
				/*
				 So, I sent a PING at time "timeSent" according to my clock. A little later, the server received it and gave it "timeStamp" using its clock. Now, I have received that PING back.
				*/
				estimatedClockDifferences.push_back(timeStamp - (timeSent + currentTime)/2);
				if(estimatedClockDifferences.size() > 40)
					estimatedClockDifferences.erase(estimatedClockDifferences.begin(), estimatedClockDifferences.begin()+1);
			}
			else
				udpMessageReceived(message, networkClock::serverToClientTime(timeStamp));
		}
		else {
			break;
		}
	}
	
	while(true) {
		std::string message = offlineCommunicator.getUdpMessagesForClient();
		if(message == "")
			break;
		long timeStamp = 0;
		for(int i=0; i<message.size(); i++) {
			if(message.at(i) == '@') {
				timeStamp = stol(message.substr(0, i));
				message = message.substr(i+1);
				break;
			}
		}
		if(message.at(0) == '_') {
			long currentTime = networkClock::getLocalTime();
			long timeSent = stol(message.substr(8));
			/*
			 So, I sent a PING at time "timeSent" according to my clock. A little later, the server received it and gave it "timeStamp" using its clock. Now, I have received that PING back.
				*/
			estimatedClockDifferences.push_back(timeStamp - (timeSent + currentTime)/2);
			if(estimatedClockDifferences.size() > 40)
				estimatedClockDifferences.erase(estimatedClockDifferences.begin(), estimatedClockDifferences.begin()+1);
		}
		else
			udpMessageReceived(message, networkClock::serverToClientTime(timeStamp));
	}
	
	// handle PINGS
	if(connectionState >= 3) {
		long currentTime = networkClock::getLocalTime();
		// send ping every 200 ms (unless we've just connected, then we want a large sample quickly)
		if(currentTime - timeLastPingSent > 200 || (currentTime - timeLastPingSent > 30 && estimatedClockDifferences.size() < 10)) {
			std::string message = std::to_string(networkClock::getLocalTime()) + "@_PING___";
			udpSocket.send(message.c_str(), message.size(), ipAddressOfServer, udpPortOfServer);
			timeLastPingSent = currentTime;
		}
	}
	//return true;
}

void NetworkClient::attemptConnectionToServer(sf::IpAddress serverIpAddress, unsigned short serverPort) {
	ipAddressOfServer = serverIpAddress;
	// connect to remote server
	if(serverIpAddress.toString() == sf::IpAddress::getLocalAddress().toString()) {
		connectionState = 3;
		return;
	}
	
	if(connectionState != 0) {
		connectionState = 0;
	}
	else
		connectionState = 0;
	tcpSocket.setBlocking(false);
	tcpSocket.connect(serverIpAddress, serverPort);
	connectionState = 1;
}

void NetworkClient::disconnect() {
	tcpSocket.disconnect();
	connectionState = 0;
}

void NetworkClient::sendOwnTcpServerMessageToQuit() {
	if(sf::IpAddress::getLocalAddress() == tcpSocket.getRemoteAddress())
		sendTcpMessage("Quit Server");
	else {
		// connect to local server
		tcpSocket.disconnect();
		sf::Time waitTime = sf::milliseconds(3000);
		tcpSocket.setBlocking(true);
		sf::Socket::Status status = tcpSocket.connect(sf::IpAddress::getLocalAddress(), getLocalServerTcpPort(), waitTime);
		tcpSocket.setBlocking(false);
		if(status == sf::Socket::Status::Done)
			sendTcpMessage("Quit Server");
		else {
			// try again
			tcpSocket.disconnect();
			sf::Time waitTime = sf::milliseconds(3000);
			tcpSocket.setBlocking(true);
			sf::Socket::Status status = tcpSocket.connect(sf::IpAddress::getLocalAddress(), getLocalServerTcpPort(), waitTime);
			tcpSocket.setBlocking(false);
			if(status == sf::Socket::Status::Done)
				sendTcpMessage("Quit Server");
			else
				sendTcpMessage("Quit Server"); // give up and just try sending a message to whatever server we may be connected to
		}
	}
}

unsigned short NetworkClient::getLocalServerTcpPort() {
	return communicator.getLocalTcpPort();
}

int NetworkClient::getConnectionState() {
	return connectionState;
}

void NetworkClient::sendTcpMessage(std::string message) {
	if(connectionState >= 1) {
		if(message == "Quit Server") {
			sf::Packet packet;
			packet << message;
			tcpSocket.send(packet);
		}
		else {
			message = std::to_string(networkClock::getServerTime()) + "@" + message;
			if(ipAddressOfServer == sf::IpAddress::getLocalAddress()) {
				offlineCommunicator.sendTcpMessageToServer(message);
			}
			else {
				sf::Packet packet;
				packet << message;
				tcpSocket.send(packet);
			}
		}
	}
}

void NetworkClient::sendUdpMessage(std::string message) {
	if(connectionState >= 3) {
		message = std::to_string(networkClock::getServerTime()) + "@" + message;
		if(ipAddressOfServer == sf::IpAddress::getLocalAddress())
			offlineCommunicator.sendUdpMessageToServer(message);
		else
			udpSocket.send(message.c_str(), message.size(), ipAddressOfServer, udpPortOfServer);
	}
}
