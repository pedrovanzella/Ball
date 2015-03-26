#include "../include/states/triangle_state.hpp"

namespace Dolly {
    TriangleState::TriangleState(Game* game)
    {
	this->game = game;

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
    }

    void TriangleState::draw(const float deltaTime)
    {
	glUseProgram(shader_programme);
	glBindVertexArray(vao);
	// draw points 0-3 from the currently bound VAO with shaders
	glDrawArrays(GL_TRIANGLES, 0, 3);
	// update other events like input handling
	glfwPollEvents();
    }

    void TriangleState::update(const float deltaTime)
    {
    }

    void TriangleState::handleInput()
    {
	if (glfwGetKey(game->mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
	    game->Stop();
	}
    }
}
