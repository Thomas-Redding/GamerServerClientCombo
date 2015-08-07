//
//  Client.cpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 8/7/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "Client.hpp"

Client::Client(sf::RenderWindow &myWindow, std::string myName) : window(myWindow), networkClient() {
    window.setFramerateLimit(30);

    // Create a graphical text to display
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    text = sf::Text(myName, font, 50);
    text.setColor(sf::Color::Red);
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
    int exitValue = networkClient.update();
    return exitValue;
}
