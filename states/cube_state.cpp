#include "../include/states/cube_state.hpp"

namespace Dolly {
    CubeState::CubeState(Game* game)
    {
	this->game = game;

	static const GLfloat g_vertex_buffer_data[] = {
	    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
	    -1.0f,-1.0f, 1.0f,
	    -1.0f, 1.0f, 1.0f, // triangle 1 : end
	    1.0f, 1.0f,-1.0f, // triangle 2 : begin
	    -1.0f,-1.0f,-1.0f,
	    -1.0f, 1.0f,-1.0f, // triangle 2 : end
	    1.0f,-1.0f, 1.0f,
	    -1.0f,-1.0f,-1.0f,
	    1.0f,-1.0f,-1.0f,
	    1.0f, 1.0f,-1.0f,
	    1.0f,-1.0f,-1.0f,
	    -1.0f,-1.0f,-1.0f,
	    -1.0f,-1.0f,-1.0f,
	    -1.0f, 1.0f, 1.0f,
	    -1.0f, 1.0f,-1.0f,
	    1.0f,-1.0f, 1.0f,
	    -1.0f,-1.0f, 1.0f,
	    -1.0f,-1.0f,-1.0f,
	    -1.0f, 1.0f, 1.0f,
	    -1.0f,-1.0f, 1.0f,
	    1.0f,-1.0f, 1.0f,
	    1.0f, 1.0f, 1.0f,
	    1.0f,-1.0f,-1.0f,
	    1.0f, 1.0f,-1.0f,
	    1.0f,-1.0f,-1.0f,
	    1.0f, 1.0f, 1.0f,
	    1.0f,-1.0f, 1.0f,
	    1.0f, 1.0f, 1.0f,
	    1.0f, 1.0f,-1.0f,
	    -1.0f, 1.0f,-1.0f,
	    1.0f, 1.0f, 1.0f,
	    -1.0f, 1.0f,-1.0f,
	    -1.0f, 1.0f, 1.0f,
	    1.0f, 1.0f, 1.0f,
	    -1.0f, 1.0f, 1.0f,
	    1.0f,-1.0f, 1.0f
	};

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	static GLfloat g_color_buffer_data[12*3*3];
	for (int v = 0; v < 12*3; v++) {
	    g_color_buffer_data[3*v+0] = 0.5;
	    g_color_buffer_data[3*v+1] = 1.0;
	    g_color_buffer_data[3*v+2] = 0.0;
	}

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(
	    1,         // attribute. No particular reason for 1, but must match the layout in the shader.
	    3,         // size
	    GL_FLOAT,  // type
	    GL_FALSE,  // normalized?
	    0,         // stride
	    (void*)0   // array buffer offset
	    );
	
	shaderLoader = new ShaderLoader("shaders/cube/vertex.glsl", "shaders/cube/fragment.glsl");
    }

    void CubeState::draw(const float deltaTime)
    {
	glUseProgram(shaderLoader->shaderProgram());
	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

    }

    void CubeState::update(const float deltaTime)
    {
    }

    void CubeState::handleInput()
    {
	glfwPollEvents();
	if (glfwGetKey(game->mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
	    game->Stop();
	}
    }
}