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
    
    attemptConnectionToServer(sf::IpAddress::getLocalAddress(), getLocalServerTcpPort());
}

bool Client::keyPressed(sf::Keyboard::Key keyCode) {
    if(keyCode == 0) {
        // if "A" pressed
        std::cout << "Client UDP Sent: 'A' pressed\n";
        if(getConnectionState() == 3) {
            sendUdpMessage("'A' pressed");
        }
        else {
            // haven't connected UDP socket to server yet
        }
    }
    return true;
}

bool Client::keyReleased(sf::Keyboard::Key keyCode) {
    return true;
}

bool Client::mouseMoved(int x, int y) {
    return true;
}

bool Client::mousePressed(sf::Mouse::Button button, int x, int y) {
    if(getConnectionState() >= 2) {
        std::cout << "Client TCP Sent: Mouse Clicked\n";
        sendTcpMessage("Mouse Clicked");
    }
    else {
        // haven't connected TCP socket to server yet
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

void Client::tcpMessageReceived(std::string message) {
    std::cout << "Client TCP Rec: " << message << "\n";
}

void Client::udpMessageReceived(std::string message) {
    std::cout << "Client UDP Rec: " << message << "\n";
}
