//
//  Client.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "Client.hpp"

Client::Client(sf::RenderWindow &myWindow, ServerCommunicator &com) : window(myWindow), NetworkClient(com) {
    window.setFramerateLimit(50);

    // Create a graphical text to display
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    serverTcpPortText = sf::Text("---", font, 50);
    serverTcpPortText.setColor(sf::Color::Red);
    serverTcpPortText.setPosition(0, 0);
    serverLocalIpAddress = sf::Text("---", font, 50);
    serverLocalIpAddress.setColor(sf::Color::Red);
    serverLocalIpAddress.setPosition(0, 40);
    serverGlobalIpAddress = sf::Text("---", font, 50);
    serverGlobalIpAddress.setColor(sf::Color::Red);
    serverGlobalIpAddress.setPosition(0, 80);
    messageText = sf::Text("", font, 50);
    messageText.setColor(sf::Color::Red);
    messageText.setPosition(0, 120);
}

bool Client::keyPressed(sf::Keyboard::Key keyCode) {
    return true;
}

bool Client::keyReleased(sf::Keyboard::Key keyCode) {
    return true;
}

bool Client::mouseMoved(int x, int y) {
    return true;
}

bool Client::mousePressed(sf::Mouse::Button button, int x, int y) {
    if(getConnectionState() == 0 || getConnectionState() == -1) {
        // connect to specific ipAddress
        // networkClient.attemptConnectionToServer(sf::IpAddress("192.168.1.79"), networkClient.getMyLocalIpAddress(), true);
        
        // connect to own server
        attemptConnectionToServer(sf::IpAddress::getLocalAddress(), getLocalServerTcpPort());
    }
    else if(getConnectionState() == 2) {
        messageNumber++;
        sendTcpMessage("Quails" + std::to_string(messageNumber));
    }
    else {
        // connection stage is 1, we have to wait
        // it's possible that sending messages this way will succeeed (assuming a connection is eventually established), but this isn't tested
    }
    return true;
}

bool Client::mouseReleased(sf::Mouse::Button button, int x, int y) {
    return true;
}

bool Client::mouseWheeled(int delta, int x, int y) {
    return true;
}

bool Client::draw() {
    window.draw(serverTcpPortText);
    window.draw(serverLocalIpAddress);
    window.draw(serverGlobalIpAddress);
    window.draw(messageText);
    return true;
}

bool Client::update() {
    serverTcpPortText.setString("Server Tcp Port" + std::to_string(getLocalServerTcpPort()));
    serverLocalIpAddress.setString("Server Local IP" + sf::IpAddress::getLocalAddress().toString());
    serverGlobalIpAddress.setString("Server Global IP" + sf::IpAddress::getPublicAddress().toString());
    return true;
}

void Client::connectionStateChanged(int oldState, int newState) {
    std::cout << "State Change: " << oldState << "->" << newState << "\n";
}

void Client::receivedTcpMessage(std::string message) {
    std::cout << "Client Received: " << message << "\n";
}
