#pragma once

#include "board.hpp"
#include "player.hpp"

#include <vector>

class Game
{
  public:
    Game(Player *white = nullptr, Player *black = nullptr);

    void start();
    void move();
    void show() const { _board->print(); }
    Color turn() const { return _turn; }

  private:
    void quit();
    void cancel();
    void draw(Player *player);
    void resign(Player *player);

  private:
    Board *_board;
    Player *_white;
    Player *_black;
    Color _turn;
    std::vector<Position> _history;
    std::vector<Move> _moves;
};
