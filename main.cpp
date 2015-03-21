#include <iostream>
#include "config.h"
#include <SFML/Graphics.hpp>

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Version " << ball_VERSION_MAJOR << "." << ball_VERSION_MINOR << endl;

    sf::Window App(sf::VideoMode(800, 600), "Ball");

    while (App.isOpen()) {
        sf::Event Event;
        while (App.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {
                App.close();
            }
            App.display();
        }
    }
    return 0;
}