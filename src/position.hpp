#pragma once

#include <string>

enum PieceType { NIL, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

enum Color { WHITE, BLACK };

/**
 * A position is a board state
 */
struct Position {
    PieceType const board[64];
    Color const turn;
    int const fifty_move_rule;
    bool const white_castle;
    bool const black_castle;
    bool const en_passant;
};

/**
 * A square describe a location on the board
 */
class Square
{
  public:
    int const x;  // file
    int const y;  // rank
    std::string const name;

  public:
    Square(int x, int y);
    Square(std::string const name);
    Square(Square const &other) = default;

    bool operator==(Square const &other) const;
};

class Move
{
  public:
    Move(Square from, Square to) : _from{from}, _to{to} {};
    Move(std::string const &uci)
        : _from{uci.substr(0, 2)}, _to{uci.substr(2, 2)} {};

    Square const from() const { return _from; }
    Square const to() const { return _to; }
    std::string const to_uci() const { return _from.name + _to.name; }

    bool operator==(Move const &other) const;
    bool operator!=(Move const &other) const;

  private:
    Square _from;
    Square _to;
};
