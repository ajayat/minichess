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
    std::string const to_pgn() const;

    bool is_pseudo_legal(Move const &move) const;
    bool is_legal(Move const &move);
    bool is_capture(Move const &move) const;
    bool is_checked(Color color) const;

    Piece *operator()(Square const &square) const;

  private:
    bool is_attacked(Square const &square) const;
    Piece *create_piece(PieceType type, Color color);
    void _move(Square const &from, Square const &to);

  private:
    Piece *_board[NROW][NCOL];
    Position _position;
};
