//
//  TcpServer.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "TcpServer.hpp"

TcpServer::TcpServer(ServerCommunicator &com): communicator(com) {
	sf::Socket::Status status = listener.listen(sf::TcpSocket::AnyPort);
	selector.add(listener);
	communicator.setLocalTcpPort(listener.getLocalPort());
}

bool TcpServer::update() {
	if(selector.wait()) {
		// Test the listener
		if(selector.isReady(listener)) {
			// The listener is ready: there is a pending connection
			sf::TcpSocket* client = new sf::TcpSocket;
			if(listener.accept(*client) == sf::Socket::Done) {
				// Add the new client to the clients list
				clients.push_back(client);
				// Add the new client to the selector so that we will
				// be notified when he sends something
				selector.add(*client);
			}
			else
				delete client; // Error, we won't get a new connection, delete the socket
		}
		else {
			// The listener socket is not ready, test all other sockets (the clients)
			for(int i=0; i<clients.size(); i++) {
				sf::TcpSocket *client = clients[i];
				if(selector.isReady(*client)) {
					// The client has sent some data, we can receive it
					sf::Packet packet;
					sf::Socket::Status status = client->receive(packet);
					if(status == sf::Socket::Done) {
						std::string str;
						packet >> str;
						communicator.sendTcpMessageToServer(str, client->getRemoteAddress().toString());
					}
					if(status == sf::Socket::Disconnected) {
						selector.remove(*client);
						client->disconnect();
						delete(client);
						clients.erase(clients.begin()+i, clients.begin()+i+1);
						i--;
					}
					client->setBlocking(false);
				}
			}
		}
	}
	
	// sync clients
	communicator.setClients(&clients);
	
	bool shouldContinue = communicator.getShouldServersContinue();
	return shouldContinue;
}
