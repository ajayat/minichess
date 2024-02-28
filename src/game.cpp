#include <iostream>

#include "game.hpp"

Game::Game(Player *white, Player *black)
    : _white(white), _black(black), _status(ONGOING)
{
    _history.emplace_back(_board.get_position());
}

void Game::show() const
{
    _board.print();
}

void Game::wait(Player *player)
{
    ResponseStatus response = player->wait(_history);
    _status = apply(response);
}

Player *Game::current() const
{
    return _board.turn() == WHITE ? _white : _black;
}

Player *Game::opponent(Player *player) const
{
    return (player == _white) ? _black : _white;
}

GameStatus Game::status() const
{
    return _status;
}

GameStatus Game::move(Move const &move)
{
    if (!_board.is_legal(move)) {
        std::cout << "Illegal move." << std::endl;
        return ONGOING;
    }
    _board.move(move);
    _history.emplace_back(_board.get_position());

    // TODO fix this
    Player *opponent = this->opponent(current());
    if (fifty_move_rule())
        return FIFTY_MOVE_RULE;
    if (threefold_repetition())
        return THREEFOLD_REPETITION;
    if (is_checkmate(opponent))
        return (opponent == _black) ? WHITE_WIN : BLACK_WIN;
    if (is_stalemate(opponent))
        return STALEMATE;
    return ONGOING;
}

bool Game::threefold_repetition() const
{
    int count = 0;
    for (Position const &position : _history) {
        if (position == _board.get_position())
            count++;
    }
    return count >= 3;
}

bool Game::fifty_move_rule() const
{
    return _board.get_position().fifty_move_rule >= 100;
}

GameStatus Game::cancel()
{
    if (_history.size() > 0) {
        _history.pop_back();
        _board.set_position(_history.back());
    }
    return ONGOING;
}

GameStatus Game::draw()
{
    if (fifty_move_rule() || threefold_repetition())
        return ABORTED;
    std::cout << opponent(current())->name() << ", accept draw ? (y/n): ";

    char answer;
    std::cin >> answer;
    if (answer == 'y') {
        std::cout << "Draw accepted." << std::endl;
        return ABORTED;
    }
    std::cout << "Draw refused." << std::endl;
    return ONGOING;
}

bool Game::has_legal_moves(Player *player)
{
    for (int i = 0; i < 64; i++) {
        Square from{i % 8, i / 8};
        if (!_board(from) || _board(from)->color != player->color())
            continue;
        for (int j = 0; j < 64; j++) {
            Square to{j % 8, j / 8};
            if (_board.is_legal(Move(from, to)))
                return true;
        }
    }
    return false;
}

bool Game::is_stalemate(Player *player)
{
    return !_board.is_checked(player->color()) && !has_legal_moves(player);
}

bool Game::is_checkmate(Player *player)
{
    return _board.is_checked(player->color()) && !has_legal_moves(player);
}

GameStatus Game::apply(ResponseStatus const &response)
{
    switch (response.status) {
    case QUIT:
        return ABORTED;
    case CANCEL:
        return cancel();
    case DRAW:
        return draw();
    case RESIGN:
        return (current()->color() == WHITE) ? BLACK_WIN : WHITE_WIN;
    case MOVE:
        return move(response.move);
    }
    return ONGOING;
}

std::string const Game::get_result() const
{
    switch (_status) {
    case WHITE_WIN:
        return _board.to_pgn() + " 1-0";
    case BLACK_WIN:
        return _board.to_pgn() + " 0-1";
    case FIFTY_MOVE_RULE:
    case THREEFOLD_REPETITION:
    case STALEMATE:
        return _board.to_pgn() + " 1/2-1/2";
    case ABORTED:
        return _board.to_pgn() + " ?-?";
    default:
        return "";
    }
}