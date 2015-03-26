#include "include/game.hpp"
#include "include/game_state.hpp"
#include "include/states/triangle_state.hpp"
#include <iostream>
#include <stdexcept>

namespace Dolly {

    void error_callback(int error, const char* description)
    {
	std::cerr << error << ": " << description << std::endl;
    }

    Game::Game():
	running(true)
    {
	// start GL context and OS window using GLFW
	if (!glfwInit()) {
	    throw std::runtime_error("could not start GLFW3\n");
	}

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	mWindow = glfwCreateWindow(800, 600, "Super Dolly Ball", NULL, NULL);
	if (!mWindow) {
	    throw std::runtime_error("could not open window\n");
	    glfwTerminate();
	}
	glfwMakeContextCurrent(mWindow);
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	    throw std::runtime_error("glewInit failed");

	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	std::cout << "Renderer: " << renderer << std::endl;
	std::cout << "OpenGL version: " << version << std::endl;
    
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Start at TriangleState
	this->states.push(new TriangleState(this));
    }

    void Game::pushState(GameState* state)
    {
	this->states.push(state);
    }

    void Game::popState()
    {
	delete this->states.top(); // Free the memory. Would be better to use some new C++11 stuff
	this->states.pop();
    }

    GameState* Game::peekState()
    {
	if (this->states.empty()) {
	    return nullptr;
	}
	return this->states.top();
    }

    void Game::changeState(GameState* state)
    {
	if (!this->states.empty()) {
	    popState();
	}

	pushState(state);
    }

    int Game::Run(void)
    {
	// Run main loop
	GameLoop();
	return 0;
    }

    void Game::Stop(void)
    {
	std::cout << "Finishing up..." << std::endl;
	running = false;
	// Do any cleanup necessary
    }

    void Game::GameLoop(void)
    {
	while (running) {
	    float deltaTime = 0.0f;
	    if (peekState() == nullptr) {
		continue;
	    }
	    peekState()->handleInput();
	    peekState()->update(deltaTime);

	    // wipe the drawing surface
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	    peekState()->draw(deltaTime);

	    // put the stuff we've been drawing on the display
	    glfwSwapBuffers(mWindow);
	}
    }
}
