#ifndef DOLLY_GAME_HPP
#define DOLLY_GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

namespace Dolly {
    class Game {
    public:
	Game();
	int Run(void);
    private:
	void GameLoop(void);
	void processEvents();
	void update(sf::Time elapsedTime);
	void render();

	void updateStatistics(sf::Time elapsedTime);	
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

	sf::Window mWindow;
	static const sf::Time TimePerFrame;
	bool running;

	GLuint shader_programme;
	GLuint vao;
    };
}

#endif /* DOLLY_GAME_HPP */
