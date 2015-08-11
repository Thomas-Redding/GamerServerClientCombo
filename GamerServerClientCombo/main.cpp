
#include <thread>
#include "Client.hpp"
#include "Server.hpp"
#include "TcpServer.hpp"

void startMainServer(ServerCommunicator *com) {
    Server server(*com);
    bool shouldContine = true;
    while (shouldContine) {
        server.networkUpdate();
        shouldContine = shouldContine && server.update();
    }
}

void startTcpServer(ServerCommunicator *com) {
    TcpServer tcpServer(*com);
    bool shouldContine = true;
    while (shouldContine) {
        shouldContine = tcpServer.update();
    }
}

int main(int, char const**) {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    ServerCommunicator communicator;
    std::thread mainServerThread(startMainServer, &communicator);
    std::thread tcpServerThread(startTcpServer, &communicator);
    
    // sleep for 100 ms to give the server time to set up
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 100;
    tim.tv_nsec *= 1000000;
    nanosleep(&tim , &tim2);
    
    Client client(window, communicator);
    
    bool shouldProgramContinue = true;
    
    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while(window.pollEvent(event)) {
            // Close window: exit
            if(event.type == sf::Event::Closed) {
                shouldProgramContinue = false;
                break;
            }
            else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                // Escape pressed: exit
                shouldProgramContinue = false;
                break;
            }
            else if(event.type == sf::Event::KeyPressed) {
                shouldProgramContinue = shouldProgramContinue && client.keyPressed(event.key.code);
            }
            else if(event.type == sf::Event::KeyReleased) {
                shouldProgramContinue = shouldProgramContinue && client.keyReleased(event.key.code);
            }
            else if(event.type == sf::Event::TextEntered) {
                shouldProgramContinue = shouldProgramContinue && client.textEntered(event.text.unicode);
            }
            else if(event.type == sf::Event::MouseMoved) {
                shouldProgramContinue = shouldProgramContinue && client.mouseMoved(event.mouseMove.x, event.mouseMove.y);
            }
            else if(event.type == sf::Event::MouseButtonPressed) {
                shouldProgramContinue = shouldProgramContinue && client.mousePressed(event.mouseButton.button, event.mouseButton.x, event.mouseButton.y);
            }
            else if(event.type == sf::Event::MouseButtonReleased) {
                shouldProgramContinue = shouldProgramContinue && client.mouseReleased(event.mouseButton.button, event.mouseButton.x, event.mouseButton.y);
            }
            else if(event.type == sf::Event::MouseWheelMoved) {
                shouldProgramContinue = shouldProgramContinue && client.mouseWheeled(event.mouseWheel.delta, event.mouseButton.x, event.mouseButton.y);
            }
            else if(event.type == sf::Event::Resized) {
                shouldProgramContinue = shouldProgramContinue && client.resized(event.size.width, event.size.height);
            }
        }
        
        client.startFrame();
        
        shouldProgramContinue = shouldProgramContinue && client.update();
        
        client.networkUpdate();

        // Clear screen
        window.clear();
        
        shouldProgramContinue = shouldProgramContinue && client.draw();

        // Update the window
        window.display();
        
        client.endFrame();
        
        if(!shouldProgramContinue) {
            communicator.setShouldServersContinue(false);
            client.applicationIsClosing();
            mainServerThread.join();
            tcpServerThread.join();
            window.close();
        }
    }

    return EXIT_SUCCESS;
}
