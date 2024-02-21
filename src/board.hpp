#pragma once

#include <string>
#include <vector>

#include "piece.hpp"
#include "position.hpp"

class Board
{
  public:
    Board();
    Board(Board const &other) = delete;
    ~Board();

    void print() const;
    void move(Square const &from, Square const &to);
    Position const position() const;

    bool is_pseudo_legal(Move const &move) const;
    bool is_legal(Move const &move) const;
    bool is_capture(Move const &move) const;
    bool is_check(Move const &move, Color color) const;

    Piece *operator()(Square const &square) const;

  private:
    Color _turn;
    Piece *_board[NROW][NCOL];
};
