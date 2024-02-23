#pragma once

#include "board.hpp"
#include "player.hpp"

#include <vector>

class Game
{
  public:
    Game(Player *white, Player *black);
    void move(Move const &move);

    void show() const { _board.print(); }

    Color turn() const { return _board.turn(); }

    Move const wait_player() const;

  private:
    void quit();
    void cancel();
    void draw(Player *player);
    void resign(Player *player);

  private:
    Board _board;
    Player *_white;
    Player *_black;
    std::vector<Position> _history;
    std::vector<Move> _moves;
};
