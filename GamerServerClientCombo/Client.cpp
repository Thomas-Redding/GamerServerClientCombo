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
    
    // create the text we will be rendering
    serverTcpPortText = sf::Text("", font, 50);
    serverTcpPortText.setColor(sf::Color::Red);
    serverTcpPortText.setPosition(0, 0);
    
    // connect to the server on your computer
    attemptConnectionToServer(sf::IpAddress::getLocalAddress(), getLocalServerTcpPort());
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
    return true;
}

bool Client::mouseReleased(sf::Mouse::Button button, int x, int y) {
    return true;
}

bool Client::mouseWheeled(int delta, int x, int y) {
    return true;
}

bool Client::resized(unsigned int width, unsigned int height) {
    return true;
}

bool Client::draw() {
    window.draw(serverTcpPortText);
    return true;
}

bool Client::update() {
    serverTcpPortText.setString("Local Server Tcp Port: " + std::to_string(getLocalServerTcpPort()));
    return true;
}

void Client::connectionStateChanged(int oldState, int newState) {
}

void Client::tcpMessageReceived(std::string message) {
}

void Client::udpMessageReceived(std::string message) {
}

bool Client::textEntered(sf::Uint32 character) {
    return true;
}
