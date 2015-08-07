
#include <thread>
#include "Client.hpp"
#include "Server.hpp"
#include "TcpServer.hpp"

void startMainServer(ServerCommunicator *com) {
    Server server(*com);
    bool shouldContine = true;
    while (shouldContine) {
        shouldContine = server.update();
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
    
    Client client(window, communicator);
    
    bool shouldCloseProgram = false;
    
    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while(window.pollEvent(event)) {
            // Close window: exit
            if(event.type == sf::Event::Closed) {
                shouldCloseProgram = true;
                break;
            }
            else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                // Escape pressed: exit
                shouldCloseProgram = true;
                break;
            }
            else if(event.type == sf::Event::KeyPressed) {
                int exitCode = client.keyPressed(event.key.code);
                if(exitCode != 0) {
                    shouldCloseProgram = true;
                }
            }
            else if(event.type == sf::Event::KeyReleased) {
                int exitCode = client.keyReleased(event.key.code);
                if(exitCode != 0) {
                    shouldCloseProgram = true;
                }
            }
            else if(event.type == sf::Event::MouseMoved) {
                int exitCode = client.mouseMoved(event.mouseMove.x, event.mouseMove.y);
                if(exitCode != 0) {
                    shouldCloseProgram = true;
                }
            }
            else if(event.type == sf::Event::MouseButtonPressed) {
                int exitCode = client.mousePressed(event.mouseButton.button, event.mouseButton.x, event.mouseButton.y);
                if(exitCode != 0) {
                    shouldCloseProgram = true;
                }
            }
            else if(event.type == sf::Event::MouseButtonReleased) {
                int exitCode = client.mouseReleased(event.mouseButton.button, event.mouseButton.x, event.mouseButton.y);
                if(exitCode != 0) {
                    shouldCloseProgram = true;
                }
            }
            else if(event.type == sf::Event::MouseWheelMoved) {
                int exitCode = client.mouseWheeled(event.mouseWheel.delta, event.mouseButton.x, event.mouseButton.y);
                if(exitCode != 0) {
                    shouldCloseProgram = true;
                }
            }
        }
        
        int exitCode = client.update();
        if(exitCode != 0) {
            shouldCloseProgram = true;
        }

        // Clear screen
        window.clear();
        
        client.draw();
        if(exitCode != 0) {
            shouldCloseProgram = true;
        }

        // Update the window
        window.display();
        
        if(shouldCloseProgram) {
            communicator.setShouldServersContinue(false);
            client.applicationIsClosing(communicator.getLocalTcpPort());
            mainServerThread.join();
            tcpServerThread.join();
            window.close();
        }
    }

    return EXIT_SUCCESS;
}
