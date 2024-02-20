#pragma once

#include <string>

enum PieceType { EMPTY, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

enum Color { WHITE, BLACK };

/**
 * A square describe a location on the board
 */
class Square
{
  public:
    int const x; // file
    int const y; // rank
    std::string const name;

  public:
    Square(int x, int y);
    Square(std::string const name);
    Square(Square const &other) = default;

    bool operator==(Square const &other) const;
};

/**
 * A position is a board state
 */
class Position
{
  public:
    PieceType const board[64];
    Color const turn;
    int const fifty_move_rule;
    bool const white_castle;
    bool const black_castle;
    bool const en_passant;
};
