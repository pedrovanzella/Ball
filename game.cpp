#include "include/game.hpp"

namespace Dolly {
    Game::Game():
	mWindow(sf::VideoMode(800, 600), "Super Dollynho Ball", sf::Style::Default, sf::ContextSettings(32))
    {
	mWindow.setVerticalSyncEnabled(true);
    }

    int Game::Run(void)
    {
	// Set stuff up etc
	// Run main loop
	return 0;
    }

    void Game::GameLoop(void)
    {
	// While I can
	// Process events
	// update states
	// render
    }

    void Game::processEvents()
    {
	// Process events
	// call handlePlayerInput
    }

    void Game::render()
    {
	// Do OpenGL magic? Nah! Delegate!
    }

    void Game::updateStatistics(sf::Time elapsedTime)
    {
	// Update FPS count
    }

    void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
    {

    }
}
