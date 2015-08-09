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
    
    // connect to the server on your computer
    attemptConnectionToServer(sf::IpAddress::getLocalAddress(), getLocalServerTcpPort());
}

bool Client::keyPressed(sf::Keyboard::Key keyCode) {
    if(keyCode == 0) {
        if(getConnectionState() == 3) {
            // if "A" is pressed and the UDP port is connected, send a message to the server
            std::cout << "Client UDP Sent: 'A' pressed\n";
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
        // if TCP port is connected, send a message to the server
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

bool Client::resized(unsigned int width, unsigned int height) {
    return true;
}

bool Client::draw() {
    // draw the text
    window.draw(serverTcpPortText);
    window.draw(serverLocalIpAddress);
    window.draw(serverGlobalIpAddress);
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

bool Client::textEntered(sf::Uint32 character) {
    return true;
}
