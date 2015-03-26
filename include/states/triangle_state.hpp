#ifndef STATES_TRIANGLE_STATE_HPP
#define STATES_TRIANGLE_STATE_HPP

#include "../game_state.hpp"

namespace Dolly {
    class TriangleState: public GameState {
    public:
	TriangleState();
	
	void draw(const float deltaTime);
	void update(const float deltaTime);
	void handleInput();
    private:
	GLuint shader_programme;
	GLuint vao;
    };
}

#endif /* STATES_TRIANGLE_STATE_HPP */
