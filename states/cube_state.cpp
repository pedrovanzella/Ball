#include "../include/states/cube_state.hpp"
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Dolly {
    CubeState::CubeState(Game* game)
    {
	this->game = game;
	
	shaderLoader = new ShaderLoader("shaders/cube/vertex.glsl", "shaders/cube/fragment.glsl");

	mv_location = glGetUniformLocation(shaderLoader->shaderProgram(), "mv_matrix");
	proj_location = glGetUniformLocation(shaderLoader->shaderProgram(), "proj_matrix");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	static const GLushort vertex_indices[] =
	{
            0, 1, 2,
            2, 1, 3,
            2, 3, 4,
            4, 3, 5,
            4, 5, 6,
            6, 5, 7,
            6, 7, 0,
            0, 7, 1,
            6, 0, 2,
            2, 4, 6,
            7, 5, 3,
            7, 3, 1
	};

	static const GLfloat vertex_positions[] =
	{
            -0.25f, -0.25f, -0.25f,
            -0.25f,  0.25f, -0.25f,
             0.25f, -0.25f, -0.25f,
             0.25f,  0.25f, -0.25f,
             0.25f, -0.25f,  0.25f,
             0.25f,  0.25f,  0.25f,
            -0.25f, -0.25f,  0.25f,
            -0.25f,  0.25f,  0.25f,
	};

	glGenBuffers(1, &position_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
	glBufferData(GL_ARRAY_BUFFER,
		     sizeof(vertex_positions),
		     vertex_positions,
		     GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		     sizeof(vertex_indices),
		     vertex_indices,
		     GL_STATIC_DRAW);

	glEnable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
    }

    void CubeState::draw(const float deltaTime)
    {
	glUseProgram(shaderLoader->shaderProgram());

	glm::mat4 proj_matrix = glm::perspective(50.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
	glUniformMatrix4fv(proj_location, 1, GL_FALSE, glm::value_ptr(proj_matrix));

	/* Build mv_matrix here */
	glm::mat4 mv_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f));
	glUniformMatrix4fv(mv_location, 1, GL_FALSE, glm::value_ptr(mv_matrix));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
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
