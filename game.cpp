#include "include/game.hpp"
#include <iostream>

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
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);

	std::cout << "Renderer: " << renderer << std::endl;
	std::cout << "OpenGL Version: " << version << std::endl;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	/* OTHER STUFF GOES HERE NEXT */
	float points[] = {
	    0.0f,  0.5f, 0.0f,
	    0.5f, -0.5f, 0.0f,
	    -0.5f, -0.5f, 0.0f
	};
    
	// Vertex Buffer Object
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);
    
	// Vertex Attribute Object
	vao = 0;
	glGenVertexArraysAPPLE(1, &vao);
	glBindVertexArrayAPPLE(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
 
	// Define shaders
	/* http://en.wikipedia.org/wiki/OpenGL_Shading_Language */
	const char* vertex_shader =
	    "#version 110\n" /* 400 for OpenGL 4, 150 for OpenGL 3 */
	    "in vec3 vp;"
	    "void main() {"
	    "  gl_Position = vec4(vp, 1.0);"
	    "}";
    
	const char* fragment_shader =
	    "#version 110\n"
	    "out vec4 frag_colour;"
	    "void main() {"
	    "  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
	    "}";
    
	// Compile shaders
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
    
	// Create Shader Program
	shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

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

	glUseProgram(shader_programme);
	glBindVertexArrayAPPLE(vao);
	// draw points 0-3 from the currently bound VAO with shaders
	glDrawArrays(GL_TRIANGLES, 0, 3);
	// update other events like input handling

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
