#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "game.hpp"

namespace Dolly {
    class GameState
    {
    public:
	Game* game;

	virtual ~GameState() {}
	// All GameStates must implement a create constructor
	// where they set this->game to point at game
	virtual GameState * create (Game* game) const = 0;

	virtual void draw(const float deltaTime) = 0;
	virtual void update(const float deltaTime) = 0;
	virtual void handleInput() = 0;
    };
}

#endif /* GAME_STATE_HPP */
