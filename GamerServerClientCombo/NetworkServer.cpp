//
//  NetworkServer.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/9/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "NetworkServer.hpp"

NetworkServer::NetworkServer(ServerCommunicator &com): communicator(com) {
	udpSocket.bind(sf::Socket::AnyPort);
	udpSocket.setBlocking(false);
}

bool NetworkServer::networkUpdate() {
	bool shouldContinue = true;
	
	checkForNewClients();
	
	// check for TCP messages
	while(true) {
		std::vector<std::string> vect = communicator.receiveTcpMessage();
		if(vect.size() == 0)
			break;
		std::string message = vect[0];
		std::string ip = vect[1];
		long timeStamp = 0;
		for(int i=0; i<message.size(); i++) {
			if(message.at(i) == '@') {
				timeStamp = stol(message.substr(0, i));
				message = message.substr(i+1);
				break;
			}
		}
		if(message.at(0) == '_') {
			message = message.substr(1);
			if(message.substr(0, 7) == "CONNECT") {
				unsigned short newUdpPort = stoi(message.substr(7));
				for(int i=0; i<clients.size(); i++) {
					if(clients[i].ip.toString() == ip)
						clients[i].udpPort = newUdpPort;
				}
			}
		}
		else {
			shouldContinue = shouldContinue && receivedTcp(message, sf::IpAddress(ip), timeStamp);
			if(!shouldContinue)
				return shouldContinue;
		}
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
		long timeStamp = 0;
		for(int i=0; i<message.size(); i++) {
			if(message.at(i) == '@') {
				timeStamp = stol(message.substr(0, i));
				message = message.substr(i+1);
				break;
			}
		}
		if(message != "") {
			if(message.at(0) == '_')
				sendUdp("_PING___" + std::to_string(timeStamp), sender);
			else
				receivedUdp(message, sender, timeStamp);
		}
		else
			break;
	}
	
	return shouldContinue;
}

bool NetworkServer::shouldServerContinue() {
	return communicator.getShouldServersContinue();
}

void NetworkServer::checkForNewClients() {
	std::vector<sf::TcpSocket *> updatedClients = communicator.getClients();
	std::vector<sf::TcpSocket *> newClients;
	std::vector<sf::TcpSocket *> lostClients;
	for(int i=0; i<updatedClients.size(); i++) {
		if(!isInClientList(updatedClients[i]))
			newClients.push_back(updatedClients[i]);
	}
	for(int i=0; i<clients.size(); i++) {
		if(!isClientInUpdatedList(clients[i].tcp, updatedClients))
			lostClients.push_back(clients[i].tcp);
	}
	
	for(int i=0; i<newClients.size(); i++) {
		clients.push_back(ClientInfo());
		clients[clients.size()-1].tcp = newClients[i];
		clients[clients.size()-1].ip = newClients[i]->getRemoteAddress();
		sendTcpBySocket("_CONNECT"+std::to_string(udpSocket.getLocalPort()), clients[clients.size()-1].tcp);
	}
	
	for(int i=0; i<newClients.size(); i++)
		gotNewClient(newClients[i]->getRemoteAddress());
	for(int i=0; i<lostClients.size(); i++)
		lostClient(lostClients[i]->getRemoteAddress());
}

bool NetworkServer::isClientInUpdatedList(sf::TcpSocket *client, std::vector<sf::TcpSocket *>&list) {
	for(int i=0; i<list.size(); i++)
		if(client == list[i])
			return true;
	return false;
}

bool NetworkServer::isInClientList(sf::TcpSocket *ip) {
	for(int i=0; i<clients.size(); i++)
		if(clients[i].tcp == ip)
			return true;
	return false;
}

void NetworkServer::sendUdp(std::string message, sf::IpAddress ipAddressOfClient) {
	message = std::to_string(getTime()) + "@" + message;
	for(int i=0; i<clients.size(); i++) {
		if(clients[i].ip == ipAddressOfClient) {
			udpSocket.send(message.c_str(), message.size(), ipAddressOfClient, clients[i].udpPort);
			break;
		}
	}
}

void NetworkServer::sendTcp(std::string message, sf::IpAddress ip) {
	for(int i=0; i<clients.size(); i++) {
		if(clients[i].ip == ip) {
			sendTcpBySocket(message, clients[i].tcp);
			break;
		}
	}
}

void NetworkServer::sendTcpBySocket(std::string message, sf::TcpSocket *socket) {
	message = std::to_string(getTime()) + "@" + message;
	sf::Packet packet;
	packet << message;
	socket->send(packet);
}

long NetworkServer::getTime() {
	return std::chrono::duration_cast< std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}