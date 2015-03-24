#include <iostream>
#include "config.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Version " << ball_VERSION_MAJOR << "." << ball_VERSION_MINOR << endl;

    // Create the window
    sf::Window window(sf::VideoMode(800, 600), "Ball", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    // load resources, initialize OpenGL states etc

    // main loop
    bool running = true;
    while (running) {
        // handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false;
            } else if (event.type == sf::Event::Resized) {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }
        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw

        // end the current frame (internally, swaps the front and back buffers)
        window.display();
    }

    // release the resources here

    return 0;
}
