//
//  ServerCommunicator.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "ServerCommunicator.hpp"

bool ServerCommunicator::getShouldServersContinue() {
	shouldServersContinue_lock.lock();
	bool rtn = shouldServersContinue;
	shouldServersContinue_lock.unlock();
	return rtn;
}

void ServerCommunicator::setShouldServersContinue(bool newValue) {
	shouldServersContinue_lock.lock();
	shouldServersContinue = newValue;
	shouldServersContinue_lock.unlock();
}

std::vector<std::string> ServerCommunicator::receiveTcpMessage() {
	std::vector<std::string> message;
	tcpMessagesFromClients_lock.lock();
	if(!tcpMessagesFromClients.empty()) {
		message.push_back(tcpMessagesFromClients.front());
		tcpMessagesFromClients.pop();
		message.push_back(tcpIpsFromClients.front());
		tcpIpsFromClients.pop();
	}
	tcpMessagesFromClients_lock.unlock();
	return message;
}

void ServerCommunicator::sendTcpMessageToServer(std::string message, std::string ip) {
	tcpMessagesFromClients_lock.lock();
	tcpMessagesFromClients.push(message);
	tcpIpsFromClients.push(ip);
	tcpMessagesFromClients_lock.unlock();
}

void ServerCommunicator::setClients(std::vector<sf::TcpSocket*> *vect) {
	clients_lock.lock();
	clients.clear();
	for(int i=0; i<vect->size(); i++)
		clients.push_back(vect->at(i));
	clients_lock.unlock();
}

std::vector<sf::TcpSocket*> ServerCommunicator::getClients() {
	std::vector<sf::TcpSocket*> rtn;
	clients_lock.lock();
	for(int i=0; i<clients.size(); i++)
		rtn.push_back(clients[i]);
	clients_lock.unlock();
	return rtn;
}

void ServerCommunicator::setLocalTcpPort(unsigned short newValue) {
	localTcpPort_lock.lock();
	localTcpPort = newValue;
	localTcpPort_lock.unlock();
}

unsigned short ServerCommunicator::getLocalTcpPort() {
	localTcpPort_lock.lock();
	unsigned short rtn = localTcpPort;
	localTcpPort_lock.unlock();
	return rtn;
}
