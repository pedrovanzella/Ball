#ifndef DOLLY_GAME_HPP
#define DOLLY_GAME_HPP

#ifdef __APPLE__
#define glGenVertexArrays glGenVertexArraysAPPLE
#define glBindVertexArray glBindVertexArrayAPPLE
#define glDeleteVertexArray glDeleteVertexArrayAPPLE
#endif /* __APPLE__ */

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Dolly {
    class Game {
    public:
	Game();
	int Run(void);
    private:
	void GameLoop(void);
	void processEvents();
	void update(double elapsedTime);
	void render();

	GLFWwindow* mWindow;
	static const double TimePerFrame;
	bool running;

	GLuint shader_programme;
	GLuint vao;
    };
}

#endif /* DOLLY_GAME_HPP */
