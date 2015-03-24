#include "include/game.hpp"
#include <SFML/OpenGL.hpp>

namespace Dolly {
    const sf::Time Game::TimePerFrame = sf::seconds(1.0f / 60.0f); // Run at 60fps

    Game::Game():
	mWindow(sf::VideoMode(800, 600), "Super Dollynho Ball", sf::Style::Default, sf::ContextSettings(32)),
	running(true)
    {
	mWindow.setVerticalSyncEnabled(true);
    }

    int Game::Run(void)
    {
	// Set stuff up etc
	// Run main loop
	GameLoop();
	return 0;
    }

    void Game::GameLoop(void)
    {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (running) {
	    sf::Time elapsedTime = clock.restart();
	    timeSinceLastUpdate += elapsedTime;

	    while (timeSinceLastUpdate > TimePerFrame) {
		timeSinceLastUpdate -= TimePerFrame;

		processEvents();

		update(TimePerFrame); // Fixed update
	    }

	    updateStatistics(elapsedTime);
	    render();
	}
    }

    void Game::update(sf::Time elapsedTime)
    {
    }

    void Game::processEvents()
    {
	sf::Event event;
	while (mWindow.pollEvent(event)) {
	    switch (event.type) {
	    case sf::Event::KeyPressed:
		handlePlayerInput(event.key.code, true);
		break;

	    case sf::Event::KeyReleased:
		handlePlayerInput(event.key.code, false);
		break;

	    case sf::Event::Closed:
		running = false;
		break;

	    case sf::Event::Resized:
		glViewport(0, 0, event.size.width, event.size.height);
		break;

	    default:
		break;
	    }
	}
    }

    void Game::render()
    {
	// Do OpenGL magic? Nah! Delegate!
	// But, for now, do OpenGL magic.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mWindow.display();
    }

    void Game::updateStatistics(sf::Time elapsedTime)
    {
	// Update FPS count
    }

    void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
    {

    }
}
