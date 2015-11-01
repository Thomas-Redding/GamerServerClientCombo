//
//  ClientServerCommunicator.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 11/1/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "ClientServerCommunicator.hpp"

void ClientServerCommunicator::sendTcpMessageToClient(std::string message) {
	lockTcpToClient.lock();
	tcpMessagesToClient.push(message);
	lockTcpToClient.unlock();
}

void ClientServerCommunicator::sendUdpMessageToClient(std::string message) {
	lockUdpToClient.lock();
	udpMessagesToClient.push(message);
	lockUdpToClient.unlock();
}

void ClientServerCommunicator::sendTcpMessageToServer(std::string message) {
	lockTcpToServer.lock();
	tcpMessagesToServer.push(message);
	lockTcpToServer.unlock();
}

void ClientServerCommunicator::sendUdpMessageToServer(std::string message) {
	lockUdpToServer.lock();
	udpMessagesToServer.push(message);
	lockUdpToServer.unlock();
}

std::string ClientServerCommunicator::getTcpMessagesForClient() {
	lockTcpToClient.lock();
	std::string message;
	if(tcpMessagesToClient.empty())
		message = "";
	else {
		message = tcpMessagesToClient.front();
		tcpMessagesToClient.pop();
	}
	lockTcpToClient.unlock();
	return message;
}

std::string ClientServerCommunicator::getUdpMessagesForClient() {
	lockUdpToClient.lock();
	std::string message;
	if(udpMessagesToClient.empty())
		message = "";
	else {
		message = udpMessagesToClient.front();
		udpMessagesToClient.pop();
	}
	lockUdpToClient.unlock();
	return message;
}

std::string ClientServerCommunicator::getTcpMessagesForServer() {
	lockTcpToServer.lock();
	std::string message;
	if(tcpMessagesToServer.empty())
		message = "";
	else {
		message = tcpMessagesToServer.front();
		tcpMessagesToServer.pop();
	}
	lockTcpToServer.unlock();
	return message;
}

std::string ClientServerCommunicator::getUdpMessagesForServer() {
	lockUdpToServer.lock();
	std::string message;
	if(udpMessagesToServer.empty())
		message = "";
	else {
		message = udpMessagesToServer.front();
		udpMessagesToServer.pop();
	}
	lockUdpToServer.unlock();
	return message;
}
