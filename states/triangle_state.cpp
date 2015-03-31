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
 
	shaderLoader = new ShaderLoader("shaders/triangle/vertex.glsl", "shaders/triangle/fragment.glsl");
    }

    void TriangleState::draw(const float deltaTime)
    {
	glUseProgram(shaderLoader->shaderProgram());
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
