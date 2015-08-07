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

std::string ServerCommunicator::receiveTcpMessage() {
    std::string message = "";
    tcpMessagesFromClients_lock.lock();
    if(!tcpMessagesFromClients.empty()) {
        message = tcpMessagesFromClients.front();
        tcpMessagesFromClients.pop();
    }
    tcpMessagesFromClients_lock.unlock();
    return message;
}

void ServerCommunicator::sendTcpMessageToServer(std::string message) {
    tcpMessagesFromClients_lock.lock();
    tcpMessagesFromClients.push(message);
    tcpMessagesFromClients_lock.unlock();
}

void ServerCommunicator::setClients(std::vector<sf::TcpSocket*> *vect) {
    clients_lock.lock();
    clients.clear();
    for(int i=0; i<clients.size(); i++) {
        clients.push_back(vect->at(i));
    }
    clients_lock.unlock();
}

std::vector<sf::TcpSocket*> ServerCommunicator::getClients() {
    std::vector<sf::TcpSocket*> rtn;
    clients_lock.lock();
    for(int i=0; i<clients.size(); i++) {
        rtn.push_back(clients[i]);
    }
    clients_lock.unlock();
    return rtn;
}
