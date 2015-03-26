#ifndef DOLLY_GAME_HPP
#define DOLLY_GAME_HPP

#ifdef __APPLE__
#define glGenVertexArrays glGenVertexArraysAPPLE
#define glBindVertexArray glBindVertexArrayAPPLE
#define glDeleteVertexArray glDeleteVertexArrayAPPLE
#endif /* __APPLE__ */

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stack>

namespace Dolly {
    class GameState; // Forward-decl
    
    class Game {
    public:
	Game();
	int Run(void);
	void Stop(void);

	GLFWwindow* mWindow;

	void pushState(GameState* state);
	void popState();
	void changeState(GameState* state);
	GameState* peekState();

	
    private:
	std::stack<GameState*> states;
	
	void GameLoop(void);

	// void processEvents();
	// void update(double elapsedTime);
	// void render();

	static const double TimePerFrame;
	bool running;

	GLuint shader_programme;
	GLuint vao;
    };
}

#endif /* DOLLY_GAME_HPP */
