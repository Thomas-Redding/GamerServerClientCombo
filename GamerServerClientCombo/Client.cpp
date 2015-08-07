//
//  Client.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "Client.hpp"

Client::Client(sf::RenderWindow &myWindow, ServerCommunicator &com) : window(myWindow), networkClient(com) {
    window.setFramerateLimit(50);

    // Create a graphical text to display
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    text = sf::Text("---", font, 50);
    text.setColor(sf::Color::Red);
}

void Client::applicationIsClosing(unsigned short localTcpPort) {
    networkClient.sendOwnTcpServerMessageToQuit(localTcpPort);
}

int Client::keyPressed(sf::Keyboard::Key keyCode) {
    return 0;
}

int Client::keyReleased(sf::Keyboard::Key keyCode) {
    return 0;
}

int Client::mouseMoved(int x, int y) {
    return 0;
}

int Client::mousePressed(sf::Mouse::Button button, int x, int y) {
    if(networkClient.getConnectionStage() == 0 || networkClient.getConnectionStage() == -1) {
        networkClient.attemptConnectionToServer(sf::IpAddress("25.141.132.52"), networkClient.getLocalServerTcpPort(), false);
    }
    else if(networkClient.getConnectionStage() == 2) {
        messageNumber++;
        networkClient.sendTcpMessage("\nQuails" + std::to_string(messageNumber));
    }
    else {
        // connection stage is 1, we have to wait
        // it's possible that sending messages this way will succeeed (assuming a connection is eventually established), but this isn't tested
    }
    return 0;
}

int Client::mouseReleased(sf::Mouse::Button button, int x, int y) {
    return 0;
}

int Client::mouseWheeled(int delta, int x, int y) {
    return 0;
}

int Client::draw() {
    window.draw(text);
}

int Client::update() {
    text.setString(std::to_string(networkClient.getLocalServerTcpPort()));
    int exitValue = networkClient.update();
    return exitValue;
}
