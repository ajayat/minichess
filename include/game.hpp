#pragma once

#include <vector>

#include "board.hpp"
#include "player.hpp"

enum GameStatus {
    ONGOING,
    WHITE_WIN,
    BLACK_WIN,
    STALEMATE,
    FIFTY_MOVE_RULE,
    THREEFOLD_REPETITION,
    ABORTED
};

class Game
{
  public:
    Game(Player *white, Player *black);

    void show() const;
    void wait(Player *player);
    Player *current() const;
    Player *opponent(Player *player) const;
    GameStatus status() const;
    std::string const get_result() const;

  private:
    GameStatus move(Move const &move);
    GameStatus cancel();
    GameStatus draw();
    GameStatus apply(ResponseStatus const &response);

    bool has_legal_moves(Player *player);
    bool is_stalemate(Player *player);
    bool is_checkmate(Player *player);
    bool threefold_repetition() const;
    bool fifty_move_rule() const;

  private:
    Board _board;
    Player *_white;
    Player *_black;
    std::vector<Position> _history;
    std::vector<Move> _moves;
    GameStatus _status;
};
