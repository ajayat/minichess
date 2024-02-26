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
    void move(Move const &move);
    Color turn() const;
    Position const get_position() const;
    void set_position(Position const &position);

    bool is_pseudo_legal(Move const &move) const;
    bool is_legal(Move const &move);
    bool is_capture(Move const &move) const;
    bool is_checked(Color color) const;

    Piece *operator()(Square const &square) const;

  private:
    Square const find_king(Color color) const;
    Piece *create_piece(PieceType type, Color color);

  private:
    Piece *_board[NROW][NCOL];
    Position _position;
};
