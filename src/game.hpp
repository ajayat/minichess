#pragma once

#include <vector>

#include "board.hpp"
#include "player.hpp"

class Game
{
  public:
    Game(Player *white, Player *black);
    bool move(Move const &move);
    void show() const;
    ResponseStatus wait(Player *player);
    bool is_stalemate(Player *player);
    bool is_checkmate(Player *player);
    void cancel();

    Player *current() const;
    Player *opponent(Player *player) const;

  private:
    Board _board;
    Player *_white;
    Player *_black;
    std::vector<Position> _history;
    std::vector<Move> _moves;
};
