#include "include/game.hpp"
#include <iostream>

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
    }

    int Game::Run(void)
    {
	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version: %s\n", version);
    
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
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
 
	// Define shaders
	/* http://en.wikipedia.org/wiki/OpenGL_Shading_Language */
	const char* vertex_shader =
	    "#version 400\n" /* 400 for OpenGL 4, 150 for OpenGL 3 */
	    "in vec3 vp;"
	    "void main() {"
	    "  gl_Position = vec4(vp, 1.0);"
	    "}";
    
	const char* fragment_shader =
	    "#version 400\n"
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
	while (running) {
	    render();
	}
    }

    void Game::update(double elapsedTime)
    {
    }

    void Game::processEvents()
    {
    }

    void Game::render()
    {
	// Do OpenGL magic? Nah! Delegate!
	// But, for now, do OpenGL magic.
	// wipe the drawing surface
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shader_programme);
	glBindVertexArray(vao);
	// draw points 0-3 from the currently bound VAO with shaders
	glDrawArrays(GL_TRIANGLES, 0, 3);
	// update other events like input handling
	glfwPollEvents();
	// put the stuff we've been drawing on the display
	glfwSwapBuffers(mWindow);
    }

}
