//
//  Client.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "Client.hpp"

Client::Client(sf::RenderWindow &myWindow, ServerCommunicator &com) : window(myWindow), NetworkClient(com) {
    // use this to alter the default framerate limit from its default value (60fps)
    window.setFramerateLimit(40);
    
    // connect to the server on your computer
    attemptConnectionToServer(sf::IpAddress::getLocalAddress(), getLocalServerTcpPort());
}

bool Client::start() {
    // Load and Set the App's Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return false; // failed to load icon - quit app
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    // Load a font
    if(!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return false; // failed to load font - quit app
    }
    
    // Create a Text to Later Be Rendered
    serverTcpPortText = sf::Text("", font, 50);
    serverTcpPortText.setColor(sf::Color::Red);
    serverTcpPortText.setPosition(0, 0);
    
    return true;
}

bool Client::mousePressed(sf::Mouse::Button button, int x, int y) {
    mouseX = x;
    mouseY = y;
    if(getConnectionState() >= 2) {
        sendTcpMessage("(" + std::to_string(mouseX) + "," + std::to_string(mouseY) + ")");
    }
    else {
        // If getConnectionState is less than 2, we won't be able to send TCP messages. If it is less than 3, we can't send UDP messages
    }
    return true;
}

bool Client::draw() {
    window.draw(serverTcpPortText);
    return true;
}

bool Client::update() {
    serverTcpPortText.setString("Local Server Tcp Port: " + std::to_string(getLocalServerTcpPort()) + "\n(" + std::to_string(mouseX) + "," + std::to_string(mouseY) + ")");
    return true;
}

void Client::connectionStateChanged(int oldState, int newState) {
}

void Client::tcpMessageReceived(std::string message, long timeStamp) {
}

void Client::udpMessageReceived(std::string message, long timeStamp) {
}
