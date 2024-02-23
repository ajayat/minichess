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
    Color turn() const;
    Position const position() const;

    bool is_pseudo_legal(Square const &from, Square const &to) const;
    bool is_legal(Square const &from, Square const &to) const;
    bool is_capture(Square const &from, Square const &to) const;
    bool is_check(Square const &from, Square const &to, Color color) const;

    Piece *operator()(Square const &square) const;

  private:
    Square const find_king(Color color) const;

  private:
    Piece *_board[NROW][NCOL];
    Color _turn;
    int _fifty_move_rule = 0;
    bool _white_castle = true;
    bool _black_castle = true;
    bool _en_passant = false;
};
