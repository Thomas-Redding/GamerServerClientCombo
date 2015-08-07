//
//  NetworkClient.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "NetworkClient.hpp"

NetworkClient::NetworkClient() {
    // do nothing
}

int NetworkClient::update() {
    return 0;
}

void NetworkClient::attemptConnectionToServer(sf::IpAddress ipAddress) {
    //
}

int NetworkClient::getConnectionStage() {
    return connectionStage;
}

sf::IpAddress NetworkClient::getMyIpAddress() {
    return sf::IpAddress::getPublicAddress();
}
