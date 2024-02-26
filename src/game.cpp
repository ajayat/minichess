#include <iostream>

#include "game.hpp"

Game::Game(Player *white, Player *black) : _white(white), _black(black)
{
    _history.emplace_back(_board.get_position());
}

void Game::show() const
{
    _board.print();
}

bool Game::move(Move const &move)
{
    if (!_board.is_legal(move)) {
        std::cout << "Invalid move." << std::endl;
        return false;
    }
    _board.move(move);
    _history.emplace_back(_board.get_position());
    return true;
}

ResponseStatus Game::wait(Player *player)
{
    return player->wait(_history);
}

Player *Game::current() const
{
    return _board.turn() == WHITE ? _white : _black;
}

Player *Game::opponent(Player *player) const
{
    return (player == _white) ? _black : _white;
}

void Game::cancel()
{
    _history.pop_back();
    _board.set_position(_history.back());
}

bool Game::is_stalemate(Player *player)
{
    for (int i = 0; i < 64; i++) {
        Square from{i % 8, i / 8};
        if (!_board(from) || _board(from)->color != player->color())
            continue;
        for (int j = 0; j < 64; j++) {
            Square to{j % 8, j / 8};
            if (_board.is_legal(Move(from, to)))
                return false;
        }
    }
    return true;
}

bool Game::is_checkmate(Player *player)
{
    return _board.is_checked(player->color()) && is_stalemate(player);
}
