#ifndef STATES_TRIANGLE_STATE_HPP
#define STATES_TRIANGLE_STATE_HPP

#include "../game_state.hpp"
#include "../game.hpp"
#include "../util/shader_loader.hpp"

namespace Dolly {
    class TriangleState: public GameState {
    public:
	TriangleState * create(Game* game) const { return new TriangleState(game); } // Virtual Constructor
	TriangleState(Game* game);
	
	void draw(const float deltaTime);
	void update(const float deltaTime);
	void handleInput();
    private:
	ShaderLoader* shaderLoader;
	GLuint vao;
    };
}

#endif /* STATES_TRIANGLE_STATE_HPP */
