#include <iostream>

#include "game.hpp"

Game::Game(Player *white, Player *black) : _white(white), _black(black)
{
    _history.emplace_back(_board.position());
}

void Game::move(Move const &move)
{
    _board.move(move.from(), move.to());
    _history.emplace_back(_board.position());
}

Move const Game::wait_player() const
{
    Player *player = (turn() == WHITE) ? _white : _black;
    return player->wait(_history);
}
